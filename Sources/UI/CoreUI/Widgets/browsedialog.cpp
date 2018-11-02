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

#include "browsedialog.h"

BrowseDialog::BrowseDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Browse"));
    setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);

    m_layout = new QGridLayout;

    mw_text = new QLabel(tr("Browse"), this);

    mw_path = new QLineEdit(this);

    mw_browse = new QPushButton(QIcon(":/icons/ic_folder_open_white_18dp"), QString(), this);
    mw_browse->setToolTip(tr("Browse"));
    connect(mw_browse, &QPushButton::clicked, [=]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select executable"), QString(), tr("All files (*.*)"));

        if(fileName.isEmpty()) {
            return;
        }

        mw_path->setText(fileName);
    });

    mw_ok = new QPushButton(tr("Accept"), this);
    mw_ok->setFocus();
    mw_ok->setToolTip(tr("Ok"));
    connect(mw_ok, &QPushButton::clicked, [=]() {
        accept();
    });

    mw_cancel = new QPushButton(tr("Cancel"));
    mw_cancel->setToolTip(tr("Cancel operation"));
    connect(mw_cancel, &QPushButton::clicked, [=]() {
        mw_path->setText(QString());
        reject();
    });

    m_layout->addWidget(mw_text     , 0, 0, 1, 1);
    m_layout->addWidget(mw_path     , 1, 0, 1, 5);
    m_layout->addWidget(mw_browse   , 1, 5, 1, 1);
    m_layout->addWidget(mw_ok       , 2, 4, 1, 1);
    m_layout->addWidget(mw_cancel   , 2, 5, 1, 1);

    setLayout(m_layout);
}

QString BrowseDialog::getFileName()
{
    return mw_path->text();
}

void BrowseDialog::setText(const QString &text)
{
    mw_text->setText(text);
}
