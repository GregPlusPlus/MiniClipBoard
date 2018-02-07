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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QStatusBar>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QDialog>
#include <QMessageBox>

#include <QIcon>

#include <QtConcurrent/QtConcurrent>

#include <QDebug>

#include "../../Core/core.h"
#include "../../Core/settingsmanager.h"
#include "../../Utils/utils.h"
#include "../UtilsUI/utilsui.h"
#include "aboutdialog.h"
#include "creditsdialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(SettingsManager *manager, QWidget *parent = nullptr);

    SettingsManager *manager() const;
    void setManager(SettingsManager *manager);

signals:
    void settingsChanged();
    void checkForUpdates();

public slots:
    void settingsUIChanged();

private:
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_layout;
    QVBoxLayout *m_reinterpretLayout;
    QHBoxLayout *m_langLayout;
    QVBoxLayout *m_updatesLayout;
    QVBoxLayout *m_legalInfoslayout;

    QGroupBox *mw_reinterpretGroupBox;
    QGroupBox *mw_langGroupBox;
    QGroupBox *mw_updatesGroup;
    QGroupBox *mw_legalInfosGroup;

    QCheckBox *mw_reinterpretUrl;
    QCheckBox *mw_reinterpretColor;
    QCheckBox *mw_notify;
    QCheckBox *mw_showThumbnails;
    QCheckBox *mw_alwaysOnTop;
    QCheckBox *mw_autoUpdates;

    QComboBox *mw_lang;
    QPushButton *mw_infoLang;

    QPushButton *mw_checkForUpdates;
    QPushButton *mw_aboutButton;
    QPushButton *mw_creditsButton;

    QStatusBar *mw_statusBar;

    SettingsManager *m_manager;

private:
    void initUISettings();
    void saveSettings();
    void showAppInfos();

};

#endif // SETTINGSDIALOG_H
