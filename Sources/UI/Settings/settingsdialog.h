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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QStatusBar>
#include <QScrollArea>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include <QIcon>

#include <QtConcurrent/QtConcurrent>
#include <QDesktopServices>

#include <QDebug>

#include "../../Core/Core/core.h"
#include "../../Core/Settingsmanager/settingsmanager.h"
#include "../../Core/BookmarkManager/bookmarkmanager.h"
#include "../../Core/HotKeysManager/hotkeysmanager.h"
#include "../../Utils/utils.h"
#include "../../plugins/plugins.h"
#include "../UtilsUI/utilsui.h"
#include "hotkeysdialog.h"
#include "aboutdialog.h"
#include "creditsdialog.h"
#include "cloudcredentialsdialog.h"
#include "pluginsinfodialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(SettingsManager *settingsManager,
                            BookmarkManager *bmManager,
                            HotKeysManager *hotKeysManager,
                            const Plugins::Plugins &plugins,
                            QWidget *parent = nullptr);

    SettingsManager *manager() const;
    void setManager(SettingsManager *manager);

signals:
    void settingsChanged();
    void checkForUpdates();

public slots:
    void settingsUIChanged();
    void exportBookmarks();
    void importBookmarks();

private:
    QVBoxLayout         *m_layoutScroll;

    QWidget             *mw_widget;
    QScrollArea         *mw_scroll;

    QVBoxLayout         *m_mainLayout;
    QVBoxLayout         *m_layout;
    QVBoxLayout         *m_reinterpretLayout;
    QVBoxLayout         *m_GUILayout;
    QHBoxLayout         *m_langLayout;
    QVBoxLayout         *m_cloudLayout;
    QVBoxLayout         *m_updatesLayout;
    QVBoxLayout         *m_bookmarksLayout;
    QHBoxLayout         *m_bmDirLayout;
    QVBoxLayout         *m_legalInfoslayout;

    QGroupBox           *mw_reinterpretGroup;
    QGroupBox           *mw_GUIGroup;
    QGroupBox           *mw_langGroup;
    QGroupBox           *mw_cloudGroup;
    QGroupBox           *mw_updatesGroup;
    QGroupBox           *mw_bookmarksGroup;
    QGroupBox           *mw_legalInfosGroup;

    QCheckBox           *mw_reinterpretUrl;
    QCheckBox           *mw_reinterpretColor;
    QCheckBox           *mw_notify;
    QCheckBox           *mw_showThumbnails;
    QCheckBox           *mw_alwaysOnTop;
    QCheckBox           *mw_tooltipCopy;
    QCheckBox           *mw_autoUpdates;

    QComboBox           *mw_lang;
    QPushButton         *mw_infoLang;

    QPushButton         *mw_hotKeysButton;
    QPushButton         *mw_exportBookmarks;
    QPushButton         *mw_importBookmarks;
    QPushButton         *mw_bmDirOpen;
    QPushButton         *mw_cloudButton;
    QPushButton         *mw_checkForUpdates;
    QPushButton         *mw_aboutButton;
    QPushButton         *mw_creditsButton;
    FlatActionButton    *mw_aboutPluginsButton;
    FlatActionButton    *mw_workingDirButton;

    QLineEdit           *mw_bmPath;

    QStatusBar          *mw_statusBar;

    SettingsManager     *m_settingsManager;
    BookmarkManager     *m_bookmarkManager;
    HotKeysManager      *m_hotKeysManager;

    Plugins::Plugins m_plugins;

private:
    void initUISettings();
    void saveSettings();
    void showAppInfos();

};

#endif // SETTINGSDIALOG_H
