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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>

#include <QVBoxLayout>

#include <QCommandLineParser>

#include <QClipboard>
#include <QMimeData>

#include <QColor>
#include <QString>
#include <QImage>
#include <QUrl>

#include <QBitmap>

#include <QList>

#include <QResizeEvent>

#include <QTimer>

#include <QDebug>

#include "../../Core/Core/core.h"
#include "../../Core/ThreadLoader/threadloader.h"
#include "../../Core/BookmarkManager/bookmarkmanager.h"
#include "../../Core/SettingsManager/settingsmanager.h"
#include "../../Core/Updater/UpdaterUtils/updaterutils.h"
#include "../../Core/HotkeysManager/hotkeysmanager.h"
#include "../../Core/HotkeysManager/hotkeysutils.h"
#include "../../Core/ProcessUtils/processutils.h"
#include "../../Core/ExcludedProcessesManager/excludedprocessesmanager.h"
#include "../../Cloud/cloud.h"
#include "../../plugins/pluginsutils.h"
#include "../../Utils/utils.h"
#include "underlyingwindow.h"
#include "../../UI/CoreUI/coreui.h"
#include "../../UI/CoreUI/WidgetsManager/widgetsmanager.h"
#include "../../UI/ListWidget/container.h"
#include "../../UI/DataWidgetContainer/datawidgetcontainer.h"
#include "../../UI/DataWidget/datawidget.h"
#include "../../UI/NavTab/navtab.h"
#include "../../UI/ContentViewer/contentviewer.h"
#include "../../UI/Settings/settingsdialog.h"
#include "../../UI/Settings/moreoptionsdialog.h"
#include "../../UI/LoaderScreen/loaderscreen.h"
#include "../../UI/WelcomeScreen/welcomescreen.h"
#include "../../UI/TooltipWindow/copytooltipwindow.h"
#include "../../UI/BubbleSearch/bubblesearch.h"
#include "../../UI/DragDropScreen/dragdropscreen.h"

class MainWindow : public UnderlyingWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SettingsManager *settingsManager() const;
    void setSettingsManager(SettingsManager *settingsManager);

signals:

public slots:
    void dataChanged();
    void ignoreNextCopy();
    void clearClipBoard();
    void seeContent(DataWidget *widget);
    void showWelcomeScreen();
    void updateProgressUpdater(qint64 current, qint64 max, bool draw);
    void bubbleSearchRequested(const QString &text);

private:
    NavTab                      *mw_navTab;
    DataWidgetContainer         *mw_container;
    DataWidgetContainer         *mw_containerBookmarks;
    ContentViewer               *mw_viewer              = nullptr;
    LoaderScreen                *mw_loaderScreen        = nullptr;
    WelcomeScreen               *mw_welcomeScreen       = nullptr;
    DragDropScreen              *mw_dragDropScreen      = nullptr;
    BubbleSearch                *mw_bubbleSearch        = nullptr;
    CopyTooltipWindow           *mw_lastTooltipWindow   = nullptr;
    SettingsDialog              *mw_settingsDialog      = nullptr;
    MoreOptionsDialog           *mw_moreOptionsDialog   = nullptr;

    WidgetsManager              *m_widgetsManager       = nullptr;

    ThreadLoader                *m_loader               = nullptr;

    BookmarkManager             *m_bookmarkManager      = nullptr;
    SettingsManager             *m_p_settingsManager    = nullptr;
    HotKeysManager              m_hotKeysManager;
    ExcludedProcessesManager    m_excludedProcessesManager;
    Cloud                       *m_cloudManager         = nullptr;

    UpdaterUtils                m_updaterUtils;

    QString                     m_bookmarksPath;

    Plugins::Plugins m_plugins;

    Core::ClipboardData         m_currentData;
    int                         m_newDataCount          = 0;

    bool                        m_ignoreNextCopy        = false;
    bool                        m_updatesAlreadyChecked = false;

private:
    void newData(const QMimeData *data, Core::DataOrigin origin);
    void initPlugins();
    void initHotkeys();
    void initDialogs();
    void initCloud();
    bool isPreviousDataTheSame(const QMimeData *mime);
    void loadBookmarks();
    void displayBookmarks();
    void updateDataCount();
    void applySettings();
    void updateShowThumbnails();
    void initBookmarksDir();
    void triggerTimeOut();
    void showTooltipWindow(const Core::ClipboardData &data);

protected:
    void dragEnterEvent (QDragEnterEvent *event);
    void dragLeaveEvent (QDragLeaveEvent *event);
    void dropEvent      (QDropEvent *event);
};

#endif // MAINWINDOW_H
