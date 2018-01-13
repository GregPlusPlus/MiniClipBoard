/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017 Grégoire BOST

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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : PopupWindow(parent)
{
    m_newDataCount = 0;
    m_ignoreNextCopy = false;
    m_settingsDialogAlreadyOpen = false;
    mw_viewer = nullptr;
    mw_loader = nullptr;
    mw_welcome = nullptr;
    m_settingsManager = nullptr;

    setWindowIcon(QIcon(":/images/ic_content_paste_white_48dp"));
    setTrayIcon(QIcon(":/icons/ic_content_paste_white_18dp"));
    setIconMask(QBitmap(":/icons/ic_content_paste_white_18dp_mask"));
    setAcceptDrops(true);

    updateDataCount();
    connect(this, &MainWindow::toggled, [=](bool visible) {
        if(visible) {
            m_newDataCount = 0;
            updateDataCount();
        }
    });

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(dataChanged()));
    connect(mw_tray, &Tray::clearClipboard, [=]() {
        QApplication::clipboard()->clear();
        Core::clearClipboardData(m_currentData);
    });
    connect(mw_tray, &Tray::help, [=]() {
        if(m_settingsDialogAlreadyOpen) {
            return;
        }

        m_settingsDialogAlreadyOpen = true;

        SettingsDialog *dialog = new SettingsDialog(m_settingsManager);
        connect(dialog, &SettingsDialog::settingsChanged, [=]() {
            m_settingsManager->save();
            applySettings();
        });
        connect(dialog, &SettingsDialog::finished, [=](int result) {
            Q_UNUSED(result)
            m_settingsDialogAlreadyOpen = false;
            dialog->deleteLater();
        });

        dialog->exec();
    });

    m_bookmarkManager.setDir(QDir("./bookmarks"));

    mw_navTab = new NavTab(this);

    mw_container = new DataWidgetContainer(this);
    connect(mw_tray, SIGNAL(clear()), mw_container->getContainer(), SLOT(clear()));
    connect(mw_container->getContainer(), SIGNAL(widgetRemoved(QWidget*)), this, SLOT(widgetRemoved(QWidget*)));

    mw_containerBookmarks = new DataWidgetContainer(this);
    connect(mw_containerBookmarks->getContainer(), SIGNAL(widgetRemoved(QWidget*)), this, SLOT(widgetRemoved(QWidget*)));

    mw_navTab->addTab(QIcon(":/icons/ic_content_paste_white_24dp"), tr("All clipboards"), mw_container);
    mw_navTab->addTab(QIcon(":/icons/ic_favorite_border_white_24dp"), tr("Favorites"), mw_containerBookmarks);
    mw_navTab->select(0);

    setCentralWidget(mw_navTab);

    mw_loader = new LoaderScreen(centralWidget());
    mw_loader->hide();

    createBookmarkWidgets();
}

void MainWindow::dataChanged()
{
    const QMimeData *mime = QApplication::clipboard()->mimeData();

    if(m_ignoreNextCopy) {
        m_ignoreNextCopy = false;
        return;
    }

    if(mw_tray->paused()) {
        return;
    }

    if(previousDataIsTheSame(mime)) {
        return;
    }

    Core::ClipboardData clipboardData = Core::QMimeToClipboardData(mime);

    if(clipboardData.type == Core::MimeType_None) {
        return;
    }

    if(m_settingsManager->settings()->notify) {
        notify();
    }

    if(isVisible()) {
        m_newDataCount++;
        updateDataCount();
    }

    Core::autoReinterpretData(clipboardData, m_settingsManager->settings()->reinterpret);

    DataWidget *w = new DataWidget(this);
    w->generateUuid();
    w->setData(clipboardData);
    w->setDateTime(QDateTime::currentDateTime());
    w->setShowThumbnails(m_settingsManager->settings()->showThumbnails);
    connect(w, SIGNAL(ignoreNextCopy()), this, SLOT(ignoreNextCopy()));
    connect(w, SIGNAL(bookmarkChanged(bool)), this, SLOT(widgetBookmarkedChanged(bool)));
    connect(w, SIGNAL(seeContent(DataWidget*)), this, SLOT(seeContent(DataWidget*)));

    mw_container->getContainer()->addWidget(w);
}

void MainWindow::ignoreNextCopy()
{
    m_ignoreNextCopy = true;
}

void MainWindow::widgetBookmarkedChanged(bool bookmarked)
{
    DataWidget* senderWidget = qobject_cast<DataWidget*>(sender());

    if(bookmarked) {
        m_bookmarkManager.saveDataToFile(Core::clipboardDataToByteArray(senderWidget->data()), senderWidget->Uuid());

        DataWidget *w = CoreUI::copyDataWidget(senderWidget, mw_containerBookmarks);
        connect(w, SIGNAL(bookmarkChanged(bool)), this, SLOT(bookmarkWidgetBookmarkedChanged(bool)));
        connect(w, SIGNAL(removed(AbstractListedWidget*)), this, SLOT(bookmarkWidgetRemoved(AbstractListedWidget*)));
        connect(w, SIGNAL(seeContent(DataWidget*)), this, SLOT(seeContent(DataWidget*)));
        w->setDateTime(senderWidget->dateTime());
        w->setUuid(senderWidget->Uuid());

        mw_containerBookmarks->getContainer()->addWidget(w);
    } else {
        mw_containerBookmarks->getContainer()->removeWidget(CoreUI::getWidgetFromUUID(mw_containerBookmarks->getContainer()->widgets(), senderWidget->Uuid()));
    }
}

void MainWindow::bookmarkWidgetBookmarkedChanged(bool bookmarked)
{
    if(!bookmarked) {
        DataWidget* senderWidget = qobject_cast<DataWidget*>(sender());
        DataWidget* original = qobject_cast<DataWidget*>(CoreUI::getWidgetFromUUID(mw_container->getContainer()->widgets(), senderWidget->Uuid()));

        if(original) {
            original->setBookmarked(false);
        }

        m_bookmarkManager.removeFile(senderWidget->Uuid());

        senderWidget->removeWidget();
    }
}

void MainWindow::bookmarkWidgetRemoved(AbstractListedWidget *widget)
{
    DataWidget* senderWidget = qobject_cast<DataWidget*>(widget);
    DataWidget* original = qobject_cast<DataWidget*>(CoreUI::getWidgetFromUUID(mw_container->getContainer()->widgets(), senderWidget->Uuid()));

    if(original) {
        original->setBookmarked(false);
    }

    m_bookmarkManager.removeFile(senderWidget->Uuid());

    senderWidget->removeWidget();
}

void MainWindow::widgetRemoved(QWidget *widget)
{
    DataWidget *dataWidget = qobject_cast<DataWidget*>(widget);

    if(dataWidget) {
        if(dataWidget->data() == m_currentData) {
            Core::clearClipboardData(m_currentData);
        }
    }

    delete widget;

    m_newDataCount--;
    updateDataCount();
}

void MainWindow::seeContent(DataWidget *widget)
{
    if(mw_viewer) {
        return;
    }

    mw_loader->reveal();
    mw_viewer = new ContentViewer(centralWidget());
    mw_viewer->setData(widget->data());
    mw_viewer->setTitle(widget->title());
    mw_viewer->setDateTime(widget->dateTime());
    mw_viewer->setAnimationDuration(300);
    mw_viewer->show();
    mw_viewer->fadeIn();
    connect(mw_viewer, &ContentViewer::closed, [=]() {
        mw_loader->disappear();
        mw_viewer = nullptr;
    });
}

void MainWindow::showWelcomeScreen()
{
    mw_welcome = new WelcomeScreen(centralWidget());
    mw_welcome->show();
    if(!isVisible()) {
        toggleWindow();
    }
}

SettingsManager *MainWindow::settingsManager() const
{
    return m_settingsManager;
}

void MainWindow::setSettingsManager(SettingsManager *settingsManager)
{
    m_settingsManager = settingsManager;

    applySettings();
}

bool MainWindow::previousDataIsTheSame(const QMimeData *mime)
{
    Core::ClipboardData data = Core::QMimeToClipboardData(mime);

    if(m_currentData == data) {
        m_currentData = data;
        return true;
    } else {
        m_currentData = data;
        return false;
    }
}

QList<Core::Bookmark> MainWindow::loadBookmarks()
{
    QList<QUuid> uuids = m_bookmarkManager.getUUids();
    QList<Core::Bookmark> bookmarks;

    for(int i = 0; i < uuids.count(); i++) {
        Core::Bookmark bm;
        bm.data = Core::byteArrayToClipboardData(m_bookmarkManager.getDataFromFile(uuids.at(i)), bm.dt, bm.userName);
        bm.uuid = uuids.at(i);
        bookmarks.append(bm);
    }

    return bookmarks;
}

QList<Core::Bookmark> MainWindow::reorderBookmarks(const QList<Core::Bookmark> &bookmarks)
{
    QList<Core::Bookmark> bms1 = bookmarks;
    QList<Core::Bookmark> bms2;

    while(!bms1.isEmpty()) {
        Core::Bookmark bm = bms1.first();
        int index = 0;

        for(int i = 0; i < bms1.count(); i++) {
            if(bms1.at(i).dt <= bm.dt) {
                bm = bms1.at(i);
                index = i;
            }
        }

        bms2.append(bm);

        bms1.removeAt(index);
    }

    return bms2;
}

void MainWindow::createBookmarkWidgets()
{
    mw_loader->reveal();

    QList<Core::Bookmark> bookmarks = loadBookmarks();

    bookmarks = reorderBookmarks(bookmarks);

    for(int i = 0; i < bookmarks.count(); i++) {
        Core::ClipboardData data = bookmarks.at(i).data;
        if(data.type == Core::MimeType_None ||
                data.type == Core::MimeType_Invalid ||
                (bookmarks.at(i).userName != Utils::getUserName() && !bookmarks.at(i).userName.isEmpty())) {
            continue;
        }

        DataWidget *w = new DataWidget(this);

        w->setUuid(bookmarks.at(i).uuid);
        w->setData(data);
        w->setDateTime(bookmarks.at(i).dt);
        w->setBookmarked(true);
        //w->setShowThumbnails(m_settingsManager->settings()->showThumbnails);
        connect(w, SIGNAL(bookmarkChanged(bool)), this, SLOT(bookmarkWidgetBookmarkedChanged(bool)));
        connect(w, SIGNAL(removed(AbstractListedWidget*)), this, SLOT(bookmarkWidgetRemoved(AbstractListedWidget*)));
        connect(w, SIGNAL(seeContent(DataWidget*)), this, SLOT(seeContent(DataWidget*)));

        mw_containerBookmarks->getContainer()->addWidget(w);
    }

    mw_loader->disappear();
}

void MainWindow::updateDataCount()
{
    if(m_newDataCount == 0) {
        mw_tray->setToolTip(tr("MiniClipBoard"));
    } else if(m_newDataCount == 1) {
        mw_tray->setToolTip(tr("MiniClipBoard - 1 new"));
    } else {
        mw_tray->setToolTip(tr("MiniClipBoard - %1 news").arg(m_newDataCount));
    }
}

void MainWindow::applySettings()
{
    if(m_settingsManager->settings()->firstStart) {
        m_settingsManager->settings()->firstStart = false;
        m_settingsManager->save();

        showWelcomeScreen();
    }

    setWindowFlag(Qt::WindowStaysOnTopHint, m_settingsManager->settings()->windowAlwaysOnTop);

    updateShowThumbnails();
}

void MainWindow::updateShowThumbnails()
{
    for(int i = 0; i < mw_container->getContainer()->widgets().count(); i++) {
        DataWidget *w = qobject_cast<DataWidget*>(mw_container->getContainer()->widgets().at(i));

        w->setShowThumbnails(m_settingsManager->settings()->showThumbnails);
    }
    for(int i = 0; i < mw_containerBookmarks->getContainer()->widgets().count(); i++) {
        DataWidget *w = qobject_cast<DataWidget*>(mw_containerBookmarks->getContainer()->widgets().at(i));

        w->setShowThumbnails(m_settingsManager->settings()->showThumbnails);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if(mw_viewer) {
        mw_viewer->setFixedSize(size());
    }

    if(mw_loader) {
        mw_loader->setFixedSize(size());
    }

    if(mw_welcome) {
        mw_welcome->setFixedSize(size());
    }
}
