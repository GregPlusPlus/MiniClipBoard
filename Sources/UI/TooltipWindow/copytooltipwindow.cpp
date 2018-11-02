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

#include "copytooltipwindow.h"

CopyTooltipWindow::CopyTooltipWindow(const Core::ClipboardData &data, QWidget *parent) : TooltipWindow(parent), m_data(data)
{
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);

    mw_closeButton = new FlatActionButton(QIcon(":/icons/ic_clear_white_18dp"), tr("Close"), this);
    connect(mw_closeButton, &FlatActionButton::clicked, this, &CopyTooltipWindow::closeRequested);

    mw_saveButton = new FlatActionButton(QIcon(":/icons/ic_save_white_18dp"), tr("Save data to file"), this);
    connect(mw_saveButton, &QPushButton::clicked, [=]() {
        setAutoClose(false);
        Core::saveData(m_data);
        setAutoClose(true);
    });

    mw_printButton = new FlatActionButton(QIcon(":/icons/ic_print_white_18dp"), tr("Print"), this);
    connect(mw_printButton, &QPushButton::clicked, [=]() {
        setAutoClose(false);
        PrintManager(&m_data).print();
        setAutoClose(true);
    });

    mw_removeButton = new FlatActionButton(QIcon(":/icons/ic_remove_circle_white_18dp"), tr("Remove from list"), this);
    connect(mw_removeButton, &QPushButton::clicked, [=]() {
        emit removeData(m_data);
    });

    m_layout->addWidget(mw_closeButton);
    m_layout->addWidget(mw_saveButton);
    m_layout->addWidget(mw_printButton);
    m_layout->addWidget(mw_removeButton);

    getCentralWidget()->setLayout(m_layout);
}
