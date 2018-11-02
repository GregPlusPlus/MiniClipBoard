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

#include "moreoptionsdialog.h"

MoreOptionsDialog::MoreOptionsDialog(SettingsManager *settingsMgr, ExcludedProcessesManager *excludedProcMgr, QWidget *parent) : QDialog(parent), m_p_settingsManager(settingsMgr), m_p_excludedProcManager(excludedProcMgr)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("More options..."));
    setMinimumWidth(350);

    m_layout = new QVBoxLayout;
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    mw_timeOutGroup = new QGroupBox(tr("Keep data into clipboard during..."), this);
    mw_timeOutGroup->setCheckable(true);
    connect(mw_timeOutGroup, &QGroupBox::clicked, [=](bool checked) {
        m_p_settingsManager->settings()->timeOutEnabled = checked;
        m_p_settingsManager->save();
    });

    m_timeOutLayout = new QHBoxLayout;

    mw_timeOutGroup->setLayout(m_timeOutLayout);

    mw_timeOutEdit = new QTimeEdit(this);
    mw_timeOutEdit->setDisplayFormat(tr("hh:mm:ss"));
    connect(mw_timeOutEdit, &QTimeEdit::timeChanged, [=](const QTime &time) {
        m_p_settingsManager->settings()->clipboardTimeOut = time;
        m_p_settingsManager->save();
    });

    m_timeOutLayout->addWidget(mw_timeOutEdit);

    mw_excludedProcGroup = new QGroupBox(tr("Excluded processes"), this);
    mw_excludedProcGroup->setCheckable(true);

    connect(mw_excludedProcGroup, &QGroupBox::clicked, [=](bool checked) {
        m_p_settingsManager->settings()->excludeProcesses = checked;
        m_p_settingsManager->save();
    });

    m_excludedProcLayout = new QGridLayout;

    mw_excludedProcView = new QListView(this);
    mw_excludedProcView->setEditTriggers(QAbstractItemView::DoubleClicked);

    mw_newExcludedProcButton = new QPushButton(tr("Exclude new process"));
    connect(mw_newExcludedProcButton, &QPushButton::clicked, [=]() {
        BrowseDialog dial;
        dial.setText(tr("Browse or type a RegEx starting with '?'"));

        if(dial.exec() == QDialog::Accepted) {
            if(!dial.getFileName().isEmpty()) {
                addPath(dial.getFileName());
            }
        }
    });

    mw_remExcludedProcButton = new QPushButton(tr("Remove process"));
    connect(mw_remExcludedProcButton, &QPushButton::clicked, [=]() {
        m_excludedProcListModel->removeRow(mw_excludedProcView->currentIndex().row());
        updateExcludedProcessesList();
    });

    m_excludedProcLayout->addWidget(mw_excludedProcView,      0,  0, 10, 2);
    m_excludedProcLayout->addWidget(mw_newExcludedProcButton, 10, 0, 1,  1);
    m_excludedProcLayout->addWidget(mw_remExcludedProcButton, 10, 1, 1,  1);

    mw_excludedProcGroup->setLayout(m_excludedProcLayout);

    m_layout->addWidget(mw_timeOutGroup);
    m_layout->addWidget(mw_excludedProcGroup);

    setLayout(m_layout);

    loadSettings();
    loadExcludedProcesses();
}

void MoreOptionsDialog::loadSettings()
{
    mw_timeOutGroup->setChecked(m_p_settingsManager->settings()->timeOutEnabled);
    mw_timeOutEdit->setTime(m_p_settingsManager->settings()->clipboardTimeOut);
    mw_excludedProcGroup->setChecked(m_p_settingsManager->settings()->excludeProcesses);

    if(!ProcessUtils::processUtilsAvailable()) {
        mw_excludedProcGroup->setEnabled(false);
        mw_excludedProcGroup->setChecked(false);
        m_excludedProcLayout->addWidget(new QLabel(tr("❗❗ This feature is currently not supported on your OS. ❗❗")), 11, 0, 1, 2);
    }
}

void MoreOptionsDialog::loadExcludedProcesses()
{
    m_excludedProcListModel = new QStringListModel(m_p_excludedProcManager->toStringList());
    connect(m_excludedProcListModel, &QStringListModel::dataChanged, [=]() {
        updateExcludedProcessesList();
    });

    mw_excludedProcView->setModel(m_excludedProcListModel);
}

void MoreOptionsDialog::updateExcludedProcessesList()
{
    m_p_excludedProcManager->fromStringList(m_excludedProcListModel->stringList());
    m_p_excludedProcManager->saveToFile();
}

void MoreOptionsDialog::addPath(const QString &path)
{
    QString p(path);
    if(p.startsWith("?")) {
        p.remove(0, 1);
    } else {
        p.replace("\\", "\\\\");
        p.replace("/", "\\/");
        p.replace("#", "\\#");
        p.replace("!", "\\!");
        p.replace("^", "\\^");
        p.replace("$", "\\$");
        p.replace("(", "\\(");
        p.replace(")", "\\)");
        p.replace("[", "\\[");
        p.replace("]", "\\]");
        p.replace("{", "\\{");
        p.replace("}", "\\}");
        p.replace("?", "\\?");
        p.replace("+", "\\+");
        p.replace("*", "\\*");
        p.replace(".", "\\.");
    }

    if(!QRegExp(p).isValid()) {
        QMessageBox::warning(this, tr("Invalid RegEx"), tr("The RegEx you entered is not valid !"));

        return;
    }

    if(m_excludedProcListModel->insertRow(m_excludedProcListModel->rowCount())) {
        QModelIndex index = m_excludedProcListModel->index(m_excludedProcListModel->rowCount() - 1, 0);
        m_excludedProcListModel->setData(index, p);
        updateExcludedProcessesList();
    }
}
