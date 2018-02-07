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
    m_updatesAlreadyChecked = false;
    mw_viewer = nullptr;
    mw_loader = nullptr;
    mw_welcome = nullptr;
    mp_settingsManager = nullptr;
    m_bookmarksPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/bookmarks";

    setWindowIcon(QIcon(":/images/ic_content_paste_white_48dp_2x"));
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

        SettingsDialog *dialog = new SettingsDialog(mp_settingsManager);
        connect(dialog, &SettingsDialog::settingsChanged, [=]() {
            mp_settingsManager->save();
            applySettings();
        });
        connect(dialog, &SettingsDialog::checkForUpdates, [=]() {
            checkForUpdates();
        });
        connect(dialog, &SettingsDialog::finished, [=](int result) {
            Q_UNUSED(result)
            m_settingsDialogAlreadyOpen = false;
            dialog->deleteLater();
        });

        dialog->exec();
    });

    initBookmarksDir();

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

void MainWindow::initBookmarksDir()
{
    if(!QDir(m_bookmarksPath).exists()) {
        QDir().mkpath(m_bookmarksPath);
    }
    m_bookmarkManager.setDir(QDir(m_bookmarksPath));
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

    if(mp_settingsManager->settings()->notify) {
        notify();
    }

    if(isVisible()) {
        m_newDataCount++;
        updateDataCount();
    }

    Core::autoReinterpretData(clipboardData, mp_settingsManager->settings()->reinterpret);

    DataWidget *w = new DataWidget(this);
    w->generateUuid();
    w->setData(clipboardData);
    w->setDateTime(QDateTime::currentDateTime());
    w->setShowThumbnails(mp_settingsManager->settings()->showThumbnails);
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
    connect(mw_welcome, &WelcomeScreen::deleted, [=]() {
        mw_welcome = nullptr;
    });
    mw_welcome->show();
    if(!isVisible()) {
        toggleWindow();
    }
}

void MainWindow::updaterFinishedCheck(QString version, QString changelog, bool isAppLastVersion)
{
    if(isAppLastVersion) {
        return;
    }

    QString fileSuffix;
    if(Utils::buildOS() == "windows") {
        fileSuffix = ".exe";
    }

    m_updaterPath = QString("MiniClipBoard_update%1").arg(fileSuffix);

    QMessageBox box(QMessageBox::Question,
                    tr("Updates available"),
                    tr("A new version of MiniClipBoard is available.<br>New version : <i>%1</i> | Current version : <i>%2</i><br>Do you want to download and install it?").arg(version).arg(Utils::appVersion()),
                    QMessageBox::Yes | QMessageBox::No);
    box.setDetailedText(changelog);
    box.exec();

    if(box.standardButton(box.clickedButton()) == QMessageBox::Yes) {
        DownloadDialog *dial = new DownloadDialog();
        dial->setMessage(tr("Downloading file from <a href=\"%1\">%2</a> ...").arg(m_updater.getLastVersion().installerURL).arg(m_updater.getLastVersion().installerURL));

        connect(&m_updater, &Updater::downloadFinished, [=]() {
            dial->setMessage(tr("Writing file to disk..."));

            QFile lastversion(m_updaterPath);

            if(lastversion.open(QIODevice::WriteOnly)) {
                lastversion.write(m_updater.getDataInstaller());
                lastversion.close();

                dial->setMessage(tr("Ready to install..."));

                updaterDownloadFinished();
            } else {
                QMessageBox::warning(nullptr, tr("Failed to update MiniClipBoard"), tr("Unable to write file to disk.<br><i>%1</i>").arg(lastversion.errorString()));
            }
        });
        //connect(&m_updater, SIGNAL(finishedDownload()), this, SLOT(updaterDownloadFinished()));
        connect(&m_updater, SIGNAL(progress(qint64,qint64)), dial, SLOT(progress(qint64,qint64)));
        connect(&m_updater, &Updater::error, [=](QString error) {
            QMessageBox::warning(nullptr, tr("Updater error !"), tr("An error occured when downloading file : <br><i>%1</i>").arg(error));
        });

        m_updater.downloadNewVersion();
        dial->show();
    }
}

void MainWindow::updaterDownloadFinished()
{
    QMessageBox::information(nullptr, tr("Download completed!"), tr("MiniClipBoard will be closed to complete the installation."));

    QProcess::startDetached(m_updaterPath);

    qApp->exit();
}

SettingsManager *MainWindow::settingsManager() const
{
    return mp_settingsManager;
}

void MainWindow::setSettingsManager(SettingsManager *settingsManager)
{
    mp_settingsManager = settingsManager;

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

void MainWindow::createBookmarkWidgets()
{
    mw_loader->reveal();

    QList<Core::Bookmark> bookmarks = loadBookmarks();

    bookmarks = Core::reorderBookmarks(bookmarks);

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
    if(mp_settingsManager->settings()->firstStart) {
        mp_settingsManager->settings()->firstStart = false;
        mp_settingsManager->save();

        showWelcomeScreen();
    }

    setWindowFlag(Qt::WindowStaysOnTopHint, mp_settingsManager->settings()->windowAlwaysOnTop);

    updateShowThumbnails();

    if(mp_settingsManager->settings()->autoCheckUpdates && !m_updatesAlreadyChecked) {
        checkForUpdates();
        m_updatesAlreadyChecked = true;
    }
}

void MainWindow::updateShowThumbnails()
{
    for(int i = 0; i < mw_container->getContainer()->widgets().count(); i++) {
        DataWidget *w = qobject_cast<DataWidget*>(mw_container->getContainer()->widgets().at(i));

        w->setShowThumbnails(mp_settingsManager->settings()->showThumbnails);
    }
    for(int i = 0; i < mw_containerBookmarks->getContainer()->widgets().count(); i++) {
        DataWidget *w = qobject_cast<DataWidget*>(mw_containerBookmarks->getContainer()->widgets().at(i));

        w->setShowThumbnails(mp_settingsManager->settings()->showThumbnails);
    }
}

void MainWindow::checkForUpdates()
{
    disconnect(&m_updater, SIGNAL(finishedCheck(QString,QString,bool)), this, SLOT(updaterFinishedCheck(QString,QString,bool)));
    connect(&m_updater, SIGNAL(finishedCheck(QString,QString,bool)), this, SLOT(updaterFinishedCheck(QString,QString,bool)));
    m_updater.checkForUpdates();
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
