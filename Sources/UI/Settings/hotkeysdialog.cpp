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

#include "hotkeysdialog.h"

HotKeysDialog::HotKeysDialog(HotKeysManager *manager, QWidget *parent) : QDialog(parent), m_manager(manager)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("Hotkeys settings"));

    m_layout = new QFormLayout;
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    mw_toggleWindow     = new QLineEdit(this);
    mw_close            = new QLineEdit(this);
    mw_pauseResume      = new QLineEdit(this);
    mw_clearClipboard   = new QLineEdit(this);

    mw_applyButton      = new QPushButton(tr("Apply"), this);
    connect(mw_applyButton, &QPushButton::clicked, this, &HotKeysDialog::changeSequences);

    init();

    m_layout->addRow(tr("Toggle window"),   mw_toggleWindow);
    m_layout->addRow(tr("Close"),           mw_close);
    m_layout->addRow(tr("Pause/Resume"),    mw_pauseResume);
    m_layout->addRow(tr("Clear clipboard"), mw_clearClipboard);
    m_layout->addRow(QString(),             mw_applyButton);

    setLayout(m_layout);
}

void HotKeysDialog::changeSequences()
{
    try {
        m_manager->unregisterAll();
        m_manager->registerHotKey(HotKeysManager::Action_ToggleWindow,    mw_toggleWindow->text());
        m_manager->registerHotKey(HotKeysManager::Action_Close,           mw_close->text());
        m_manager->registerHotKey(HotKeysManager::Action_PauseResume,     mw_pauseResume->text());
        m_manager->registerHotKey(HotKeysManager::Action_ClearClipboard,  mw_clearClipboard->text());
    } catch(const UException &exception) {
        QMessageBox::critical(this, tr("Unable to register Hot Key."), tr("Unable to register Hot Key : %1").arg(exception.what()));

        return;
    }

    HotKeysUtils::saveSequences(m_manager->sequences(), HotKeysUtils::fileName());
}

void HotKeysDialog::init()
{
    mw_toggleWindow->setText(m_manager->sequences().value(  HotKeysManager::Action_ToggleWindow));
    mw_close->setText(m_manager->sequences().value(         HotKeysManager::Action_Close));
    mw_pauseResume->setText(m_manager->sequences().value(   HotKeysManager::Action_PauseResume));
    mw_clearClipboard->setText(m_manager->sequences().value(HotKeysManager::Action_ClearClipboard));
}
