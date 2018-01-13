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

#include <QDebug>

#include "Core/core.h"
#include "Core/bookmarkmanager.h"
#include "Core/settingsmanager.h"
#include "UI/CoreUI/coreui.h"
#include "UI/PopupWindow/popupwindow.h"
#include "UI/ListWidget/container.h"
#include "UI/DataWidgetContainer/datawidgetcontainer.h"
#include "UI/DataWidget/datawidget.h"
#include "UI/NavTab/navtab.h"
#include "UI/ContentViewer/contentviewer.h"
#include "UI/Settings/settingsdialog.h"
#include "UI/LoaderScreen/loaderscreen.h"
#include "UI/WelcomeScreen/welcomescreen.h"

class MainWindow : public PopupWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    SettingsManager *settingsManager() const;
    void setSettingsManager(SettingsManager *settingsManager);

signals:

public slots:
    void dataChanged();
    void ignoreNextCopy();
    void widgetBookmarkedChanged(bool bookmarked);
    void bookmarkWidgetBookmarkedChanged(bool bookmarked);
    void bookmarkWidgetRemoved(AbstractListedWidget* widget);
    void widgetRemoved(QWidget *widget);
    void seeContent(DataWidget *widget);
    void showWelcomeScreen();

private:
    NavTab *mw_navTab;
    DataWidgetContainer *mw_container;
    DataWidgetContainer *mw_containerBookmarks;
    ContentViewer *mw_viewer;
    LoaderScreen *mw_loader;
    WelcomeScreen *mw_welcome;

    BookmarkManager m_bookmarkManager;
    SettingsManager *m_settingsManager;

    Core::ClipboardData m_currentData;
    int m_newDataCount;

    bool m_ignoreNextCopy;
    bool m_settingsDialogAlreadyOpen;

private:
    bool previousDataIsTheSame(const QMimeData *mime);
    QList<Core::Bookmark> loadBookmarks();
    QList<Core::Bookmark> reorderBookmarks(const QList<Core::Bookmark> &bookmarks);
    void createBookmarkWidgets();
    bool askToRemoveBookMark();
    void updateDataCount();
    void applySettings();
    void updateShowThumbnails();

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
