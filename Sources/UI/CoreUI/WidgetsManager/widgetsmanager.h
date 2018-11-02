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

#ifndef WIDGETSMANAGER_H
#define WIDGETSMANAGER_H

#include <QObject>

#include "../../../Core/Core/core.h"
#include "../../../Core/SettingsManager/settingsmanager.h"
#include "../../../Core/BookmarkManager/bookmarkmanager.h"
#include "../../DataWidget/datawidget.h"
#include "../../DataWidgetContainer/datawidgetcontainer.h"

class WidgetsManager : public QObject
{
    Q_OBJECT

public:
    explicit WidgetsManager(DataWidgetContainer *container , DataWidgetContainer *containerBookmarks, QObject *parent = nullptr);
    void setSettingsManager(SettingsManager *p_settingsManager);
    void setBookmarkManager(BookmarkManager *p_bookmarkManager);

signals:
    void ignoreNextCopy();
    void seeContent(DataWidget *widget);

public slots:
    void createWidget(const Core::ClipboardData &data);
    void createBookmarkWidget(const Core::ClipboardData &data, const Core::Bookmark &bookmark);
    void simpleWidgetBookmarkedChanged(bool bookmarked);
    void bookmarkWidgetBookmarkedChanged(bool bookmarked);
    void bookmarkWidgetRemoved(DataWidget *widget);

private:
    DataWidgetContainer *mw_container;
    DataWidgetContainer *mw_containerBookmarks;

    SettingsManager *m_p_settingsManager = nullptr;
    BookmarkManager *m_p_bookmarkManager = nullptr;

};

#endif // WIDGETSMANAGER_H
