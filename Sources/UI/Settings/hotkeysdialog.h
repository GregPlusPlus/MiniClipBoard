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

#ifndef HOTKEYSDIALOG_H
#define HOTKEYSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include <QMessageBox>

#include <QFormLayout>

#include <QMap>

#include <QDebug>

#include "../../Core/HotKeysManager/hotkeysmanager.h"
#include "../../Core/HotKeysManager/hotkeysutils.h"

class HotKeysDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HotKeysDialog(HotKeysManager *manager, QWidget *parent = nullptr);

signals:

public slots:
    void changeSequences();

private:
    QFormLayout     *m_layout;

    QLineEdit       *mw_toggleWindow;
    QLineEdit       *mw_close;
    QLineEdit       *mw_pauseResume;
    QLineEdit       *mw_clearClipboard;

    QPushButton     *mw_applyButton;

    HotKeysManager  *m_manager;

private:
    void init();
};

#endif // HOTKEYSDIALOG_H
