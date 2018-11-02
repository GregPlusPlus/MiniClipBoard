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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : UnderlyingWindow(parent)
{
    //setStyleSheet("border: 1px solid red;");

    //setAnchored(false);

    m_bookmarksPath = Utils::appDataPath() + "/bookmarks";
    m_updaterUtils.setDir(QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation)));

    m_excludedProcessesManager.setFileName("excludedprocesses");
    m_excludedProcessesManager.loadFromFile();

    initPlugins();

    m_bookmarkManager = new BookmarkManager(this);

    connect(&m_updaterUtils, &UpdaterUtils::progress, this, &MainWindow::updateProgressUpdater);

    setWindowIcon(QIcon(":/images/app_icon"));
    setTrayIcon(QIcon(":/images/ic_content_paste_white_48dp_2x"));
    setIconMask(QBitmap(":/images/ic_content_paste_white_48dp_2x_mask"));

    updateDataCount();
    connect(this, &MainWindow::toggled, [=](bool visible) {
        if(visible) {
            m_newDataCount = 0;
            updateDataCount();
        }
    });

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::dataChanged);

    connect(tray(), &Tray::clearClipboard, this, &MainWindow::clearClipBoard);

    initHotkeys();
    initBookmarksDir();
    initCloud();

    mw_navTab = new NavTab(this);

    mw_container = new DataWidgetContainer(this);
    mw_container->searchBox()->setTopCrop(titleBar()->height());
    connect(tray(), &Tray::clear, [=]() {
        if(QMessageBox::question(this, tr("Clear"), tr("Do you really want to clear all the data ?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            mw_container->getContainer()->clear();
        }
    });

    mw_containerBookmarks = new DataWidgetContainer(this);
    mw_containerBookmarks->searchBox()->setTopCrop(titleBar()->height());

    m_widgetsManager = new WidgetsManager(mw_container, mw_containerBookmarks, this);
    m_widgetsManager->setBookmarkManager(m_bookmarkManager);
    connect(m_widgetsManager, &WidgetsManager::ignoreNextCopy, this, &MainWindow::ignoreNextCopy);
    connect(m_widgetsManager, &WidgetsManager::seeContent,     this, &MainWindow::seeContent);

    mw_navTab->addTab(QIcon(":/icons/ic_content_paste_white_24dp"),   QIcon(":/icons/ic_content_paste_white_highlighted_24dp"),   tr("All clipboards"), mw_container);
    mw_navTab->addTab(QIcon(":/icons/ic_favorite_border_white_24dp"), QIcon(":/icons/ic_favorite_border_white_highlighted_24dp"), tr("Favorites"),      mw_containerBookmarks);
    mw_navTab->select(0);

    setCentralWidget(mw_navTab);

    //    mw_bubbleSearch = new BubbleSearch(QIcon(":/icons/ic_search_white_24dp"), this);
    //    mw_bubbleSearch->setToolTip(tr("Search on Wikipedia"));
    //    mw_bubbleSearch->setPlaceholderText(tr("Search on Wikipedia"));
    //    connect(mw_bubbleSearch, SIGNAL(search(QString)), this, SLOT(bubbleSearchRequested(QString)));

    mw_loaderScreen = new LoaderScreen(centralWidget());
    mw_loaderScreen->hide();
    addView(mw_loaderScreen);

    mw_dragDropScreen = new DragDropScreen(centralWidget());
    addView(mw_dragDropScreen);

    loadBookmarks();
}

MainWindow::~MainWindow()
{
    delete mw_settingsDialog;
    delete mw_moreOptionsDialog;
    if(mw_lastTooltipWindow) {
        delete mw_lastTooltipWindow;
    }
}

void MainWindow::initHotkeys()
{
    QMap<size_t, QString> sequences = HotKeysUtils::loadSequences(HotKeysUtils::fileName());
    if(sequences.isEmpty()) {
        HotKeysUtils::fillDefaultSequences(&m_hotKeysManager);
        HotKeysUtils::saveSequences(m_hotKeysManager.sequences(), HotKeysUtils::fileName());
    }

    m_hotKeysManager.registerHotKeys(sequences);

    connect(&m_hotKeysManager, &HotKeysManager::toggleWindow,  this,   &MainWindow::toggleWindow);
    connect(&m_hotKeysManager, &HotKeysManager::close,         qApp,   &QApplication::quit);
    connect(&m_hotKeysManager, &HotKeysManager::pauseResume,   tray(), &Tray::pause);
    connect(&m_hotKeysManager, &HotKeysManager::clearCliboard, this,   &MainWindow::clearClipBoard);
}

void MainWindow::initDialogs()
{
    mw_settingsDialog = new SettingsDialog(m_p_settingsManager,
                                           m_bookmarkManager,
                                           &m_hotKeysManager,
                                           m_plugins);
    connect(mw_settingsDialog, &SettingsDialog::settingsChanged, [=]() {
        m_p_settingsManager->save();
        applySettings();
    });
    connect(mw_settingsDialog, &SettingsDialog::checkForUpdates, [=]() {
        mw_settingsDialog->setCursor(Qt::WaitCursor);
        m_updaterUtils.checkForUpdates(Updater::Mode_Manual);
        mw_settingsDialog->setCursor(Qt::ArrowCursor);
    });
    connect(tray(), &Tray::help, mw_settingsDialog, &SettingsDialog::exec);

    mw_moreOptionsDialog = new MoreOptionsDialog(m_p_settingsManager,
                                                 &m_excludedProcessesManager);
    connect(tray(), &Tray::moreOptions, mw_moreOptionsDialog, &MoreOptionsDialog::exec);
}

void MainWindow::initCloud()
{
    m_cloudManager = new Cloud(this);
    connect(m_cloudManager, &Cloud::uploaded, [=](const QString &result, CloudTypes::Cloud_Platform platform) {
        qDebug() << result;

        QMessageBox::information(this, tr("Operation finished"),
                                 tr("Your data was successfully uploaded to %1. See result :<br>%2")
                                 .arg(CloudUtils::getPlatformName(platform))
                                 .arg(CloudUtils::getFormatedResult(result, platform)));
    });
    connect(m_cloudManager, &Cloud::error, [=](const QString &errorStr, CloudTypes::Cloud_Platform platform) {
        qDebug() << errorStr;

        QMessageBox::warning(this, tr("Operation finished"),
                             tr("Unable upload to %1. See error :<br>%2")
                             .arg(CloudUtils::getPlatformName(platform))
                             .arg(errorStr));
    });
}

void MainWindow::initBookmarksDir()
{
    if(!QDir(m_bookmarksPath).exists()) {
        QDir().mkpath(m_bookmarksPath);
    }

    m_bookmarkManager->setDir(QDir(m_bookmarksPath));
}

void MainWindow::triggerTimeOut()
{
    if(!m_p_settingsManager->settings()->timeOutEnabled) {
        return;
    }

    QTimer::singleShot(QTime(0, 0, 0, 0).msecsTo(m_p_settingsManager->settings()->clipboardTimeOut), [=]() {
        if(tray()->paused()) {
            return;
        }

        clearClipBoard();
    });
}

void MainWindow::dataChanged()
{
    const QMimeData *mime = QApplication::clipboard()->mimeData();

    if(m_excludedProcessesManager.checkProcessName(ProcessUtils::getProcessPathFromActiveWindow()) &&
            m_p_settingsManager->settings()->excludeProcesses && ProcessUtils::processUtilsAvailable()) {
        return;
    }

    if(m_ignoreNextCopy) {
        m_ignoreNextCopy = false;
        return;
    }

    if(tray()->paused()) {
        return;
    }

    if(isPreviousDataTheSame(mime)) {
        return;
    }

    newData(mime, Core::DataOrigin_Clipboard);
}

void MainWindow::newData(const QMimeData *data, Core::DataOrigin origin)
{
    Core::ClipboardData clipboardData = Core::QMimeDataToClipboardData(data);

    if(clipboardData.type == Core::MimeType_None) {
        return;
    }

    if(m_p_settingsManager->settings()->notify) {
        notify();
    }

    if(!isVisible()) {
        m_newDataCount++;
        updateDataCount();
    }

    Core::autoReinterpretData(clipboardData, m_p_settingsManager->settings()->reinterpret);

    if(origin == Core::DataOrigin_Clipboard) {
        showTooltipWindow(clipboardData);
    }

    mw_navTab->select(0);

    m_widgetsManager->createWidget(clipboardData);

    triggerTimeOut();
}

void MainWindow::initPlugins()
{
    m_plugins = PluginsUtils::loadPlugins();
}

void MainWindow::showTooltipWindow(const Core::ClipboardData &data)
{
    if(m_p_settingsManager) {
        if(!m_p_settingsManager->settings()->tooltipCopy) {
            return;
        }
    }

    if(mw_lastTooltipWindow) {
        mw_lastTooltipWindow->deleteLater();
    }

    mw_lastTooltipWindow = new CopyTooltipWindow(data);

    connect(mw_lastTooltipWindow, &CopyTooltipWindow::closeRequested, [=]() {
        mw_lastTooltipWindow->deleteLater();
        mw_lastTooltipWindow = nullptr;
    });

    connect(mw_lastTooltipWindow, &CopyTooltipWindow::removeData, [=](const Core::ClipboardData &data) {
        for(AbstractListedWidget *abstW : mw_container->getContainer()->widgets()) {
            DataWidget *w = qobject_cast<DataWidget*>(abstW);

            if(w->data() == data) {
                w->removeWidget();
            }
        }

        delete mw_lastTooltipWindow;
        mw_lastTooltipWindow = nullptr;
    });

    mw_lastTooltipWindow->show();
}

void MainWindow::ignoreNextCopy()
{
    m_ignoreNextCopy = true;
}

void MainWindow::clearClipBoard()
{
    if(QMessageBox::question(this, tr("Clear clipboard"), tr("Do you really want to clear the clipboard ?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QApplication::clipboard()->clear();
        Core::clearClipboardData(m_currentData);
    }
}

void MainWindow::seeContent(DataWidget *widget)
{
    if(mw_viewer) {
        return;
    }

    removeView(mw_viewer);

    mw_loaderScreen->reveal();
    mw_viewer = new ContentViewer(m_plugins, centralWidget());
    addView(mw_viewer);
    mw_viewer->setData(widget->data());
    mw_viewer->setTitle(widget->title());
    mw_viewer->setDateTime(widget->dateTime());
    mw_viewer->setAnimationDuration(300);
    mw_viewer->show();
    mw_viewer->fadeIn();
    connect(mw_viewer, &ContentViewer::closed, [=]() {
        mw_loaderScreen->disappear();
        removeView(mw_viewer);
        mw_viewer = nullptr;
    });
    connect(mw_viewer, &ContentViewer::upload, [=](CloudTypes::CloudData &data) {
        m_cloudManager->upload(data);
    });
}

void MainWindow::showWelcomeScreen()
{
    mw_welcomeScreen = new WelcomeScreen(centralWidget());
    connect(mw_welcomeScreen, &WelcomeScreen::deleted, [=]() {
        mw_welcomeScreen = nullptr;
    });
    addView(mw_welcomeScreen);
}

void MainWindow::updateProgressUpdater(qint64 current, qint64 max, bool draw)
{
    setDrawTrayProgress(draw);
    setTrayProgress(int(current), int(max));
}

void MainWindow::bubbleSearchRequested(const QString &text)
{
    Browser *b = new Browser;
    b->setUrl(QUrl(QString("https://en.wikipedia.org/w/index.php?search=%1").arg(QString(QUrl::toPercentEncoding(text)))));
    b->setControls(NavBar::Controls_All);
    b->show();
}

SettingsManager *MainWindow::settingsManager() const
{
    return m_p_settingsManager;
}

void MainWindow::setSettingsManager(SettingsManager *settingsManager)
{
    m_p_settingsManager = settingsManager;

    m_widgetsManager->setSettingsManager(settingsManager);

    applySettings();
    initDialogs();
}

bool MainWindow::isPreviousDataTheSame(const QMimeData *mime)
{
    Core::ClipboardData data = Core::QMimeDataToClipboardData(mime);

    if(m_currentData == data) {
        m_currentData = data;
        return true;
    } else {
        m_currentData = data;
        return false;
    }
}

void MainWindow::loadBookmarks()
{
    setDrawTrayProgress(true);
    tray()->setToolTip(tr("MiniClipBoard - Loading bookmarks"));

    m_loader = new ThreadLoader(m_bookmarkManager, this);
    connect(m_loader, &ThreadLoader::finished, this, &MainWindow::displayBookmarks);
    connect(m_loader, &ThreadLoader::progress, [=](int current, int max) {
        setTrayProgress(current, max);
    });

    m_loader->start();
}

void MainWindow::displayBookmarks()
{
    mw_loaderScreen->reveal();

    mw_loaderScreen->setMessage(tr("<strong>Loading bookmarks, please wait...</strong>"));

    setDrawTrayProgress(true);
    tray()->setToolTip(tr("MiniClipBoard - Loading bookmarks"));

    int i = 0;

    for(Core::Bookmark bookmark : m_loader->bookmarks()) {
        qApp->processEvents();
        Core::ClipboardData data = bookmark.data;
        if(data.type == Core::MimeType_None ||
                data.type == Core::MimeType_Invalid ||
                (bookmark.userName != Utils::getUserName() && !bookmark.userName.isEmpty())) {
            continue;
        }

        m_widgetsManager->createBookmarkWidget(data, bookmark);

        setTrayProgress(i, m_loader->bookmarks().count());
        i++;
    }

    setDrawTrayProgress(false);
    tray()->setToolTip(tr("MiniClipBoard"));


    mw_loaderScreen->disappear();
}

void MainWindow::updateDataCount()
{
    if(m_newDataCount == 0) {
        tray()->setToolTip(tr("MiniClipBoard"));
    } else if(m_newDataCount == 1) {
        tray()->setToolTip(tr("MiniClipBoard - 1 new"));
    } else {
        tray()->setToolTip(tr("MiniClipBoard - %1 news").arg(m_newDataCount));
    }
}

void MainWindow::applySettings()
{
    if(m_p_settingsManager->settings()->firstStart) {
        showWelcomeScreen();
    }

    setWindowFlag(Qt::WindowStaysOnTopHint, m_p_settingsManager->settings()->windowAlwaysOnTop);

    updateShowThumbnails();

    if(m_p_settingsManager->settings()->autoCheckUpdates && !m_updatesAlreadyChecked) {
        m_updaterUtils.checkForUpdates(Updater::Mode_Auto);
        m_updatesAlreadyChecked = true;
    }
}

void MainWindow::updateShowThumbnails()
{
    for(AbstractListedWidget *abstW : mw_container->getContainer()->widgets()) {
        DataWidget *w = qobject_cast<DataWidget*>(abstW);

        w->setShowThumbnails(m_p_settingsManager->settings()->showThumbnails);
    }
    for(AbstractListedWidget *abstW : mw_containerBookmarks->getContainer()->widgets()) {
        DataWidget *w = qobject_cast<DataWidget*>(abstW);

        w->setShowThumbnails(m_p_settingsManager->settings()->showThumbnails);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();

    mw_dragDropScreen->reveal();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();

    mw_dragDropScreen->disappear();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();

    mw_dragDropScreen->disappear();

    newData(event->mimeData(), Core::DataOrigin_DragDrop);
}
