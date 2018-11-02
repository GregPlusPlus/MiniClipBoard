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

#ifndef MOREOPTIONSDIALOG_H
#define MOREOPTIONSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QTimeEdit>
#include <QListView>
#include <QGroupBox>

#include <QMessageBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QStringListModel>

#include "../../Core/Core/core.h"
#include "../../Core/SettingsManager/settingsmanager.h"
#include "../../Core/ExcludedProcessesManager/excludedprocessesmanager.h"
#include "../../Core/ProcessUtils/processutils.h"
#include "../../Utils/utils.h"
#include "../UtilsUI/utilsui.h"
#include "../CoreUI/Widgets/browsedialog.h"

class MoreOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoreOptionsDialog(SettingsManager *settingsMgr, ExcludedProcessesManager *excludedProcMgr, QWidget *parent = nullptr);

signals:

public slots:

private:
    QVBoxLayout              *m_layout;
    QHBoxLayout              *m_timeOutLayout;
    QGridLayout              *m_excludedProcLayout;

    QGroupBox                *mw_timeOutGroup;
    QGroupBox                *mw_excludedProcGroup;

    QTimeEdit                *mw_timeOutEdit;

    QListView                *mw_excludedProcView;
    QPushButton              *mw_newExcludedProcButton;
    QPushButton              *mw_remExcludedProcButton;

    QStringListModel         *m_excludedProcListModel;

    SettingsManager          *m_p_settingsManager;
    ExcludedProcessesManager *m_p_excludedProcManager;

private:
    void loadSettings();
    void loadExcludedProcesses();

private:
    void updateExcludedProcessesList();
    void addPath(const QString &path);
};

#endif // MOREOPTIONSDIALOG_H
