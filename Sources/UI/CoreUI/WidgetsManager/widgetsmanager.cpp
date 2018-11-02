/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017-2018 Grégoire BOST

This file is part of MiniClipBoard.

MiniClipBoard is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MiniClipBoard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MiniClipBoard.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "widgetsmanager.h"

WidgetsManager::WidgetsManager(DataWidgetContainer *container, DataWidgetContainer *containerBookmarks, QObject *parent) :
    QObject(parent), mw_container(container), mw_containerBookmarks(containerBookmarks)
{

}

void WidgetsManager::createWidget(const Core::ClipboardData &data)
{
    DataWidget *w = new DataWidget(mw_container);
    w->generateUuid();
    w->setData(data);
    w->setDateTime(QDateTime::currentDateTime());
    if(m_p_settingsManager) {
        w->setShowThumbnails(m_p_settingsManager->settings()->showThumbnails);
    }
    connect(w, &DataWidget::ignoreNextCopy, this, &WidgetsManager::ignoreNextCopy);
    connect(w, &DataWidget::bookmarkChanged, this, &WidgetsManager::simpleWidgetBookmarkedChanged);
    connect(w, &DataWidget::seeContent, [=]() {
        emit seeContent(w);
    });

    mw_container->getContainer()->addWidget(w);
}

void WidgetsManager::createBookmarkWidget(const Core::ClipboardData &data, const Core::Bookmark &bookmark)
{
    DataWidget *w = new DataWidget(mw_containerBookmarks);

    w->setUuid(bookmark.uuid);
    w->setData(data);
    w->setDateTime(bookmark.dt);
    w->setBookmarked(true);
    if(m_p_settingsManager) {
        w->setShowThumbnails(m_p_settingsManager->settings()->showThumbnails);
    }
    connect(w, &DataWidget::ignoreNextCopy, this, &WidgetsManager::ignoreNextCopy);
    connect(w, &DataWidget::bookmarkChanged, this, &WidgetsManager::bookmarkWidgetBookmarkedChanged);
    connect(w, &DataWidget::removed, [=](AbstractListedWidget *widget) {
        bookmarkWidgetRemoved(qobject_cast<DataWidget*>(widget));
    });
    connect(w, &DataWidget::seeContent, [=]() {
        emit seeContent(w);
    });

    mw_containerBookmarks->getContainer()->addWidget(w);
}

void WidgetsManager::simpleWidgetBookmarkedChanged(bool bookmarked)
{
    DataWidget* senderWidget = qobject_cast<DataWidget*>(sender());

    if(bookmarked) {
        Core::Bookmark bookmark;
        bookmark.uuid = senderWidget->Uuid();
        bookmark.dt   = senderWidget->dateTime();
        createBookmarkWidget(senderWidget->data(), bookmark);

        if(m_p_bookmarkManager) {
            m_p_bookmarkManager->saveDataToFile(Core::clipboardDataToByteArray(senderWidget->data()), senderWidget->Uuid());
        }
    } else {
        DataWidget *widget = qobject_cast<DataWidget*>(CoreUI::getWidgetFromUUID(mw_containerBookmarks->getContainer()->widgets(), senderWidget->Uuid()));
        if(!widget->beingRemoved()) {
            widget->removeWidget();
        }
    }
}

void WidgetsManager::bookmarkWidgetBookmarkedChanged(bool bookmarked)
{
    DataWidget* senderWidget = qobject_cast<DataWidget*>(sender());

    if(!bookmarked) {
        bookmarkWidgetRemoved(senderWidget);
    }
}

void WidgetsManager::bookmarkWidgetRemoved(DataWidget *widget)
{
    m_p_bookmarkManager->removeFile(widget->Uuid());

    DataWidget* original = qobject_cast<DataWidget*>(
                CoreUI::getWidgetFromUUID(mw_container->getContainer()->widgets(), widget->Uuid()));
    if(original) {
        if(original->bookmarked()) {
            widget->removeWidget();

            original->setBookmarked(false);
        }
    }
}

void WidgetsManager::setBookmarkManager(BookmarkManager *p_bookmarkManager)
{
    m_p_bookmarkManager = p_bookmarkManager;
}

void WidgetsManager::setSettingsManager(SettingsManager *p_settingsManager)
{
    m_p_settingsManager = p_settingsManager;
}
