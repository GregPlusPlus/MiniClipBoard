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

#include "errorwidget.h"

ErrorWidget::ErrorWidget(ErrType type, const QString fileName, QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;

    mw_icon = new QLabel(this);
    mw_icon->setPixmap(QPixmap(":/icons/ic_broken_image_white_36dp"));

    mw_text = new QLabel(this);
    mw_text->setWordWrap(true);

    m_layout->addWidget(mw_icon);
    m_layout->addWidget(mw_text);
    m_layout->setAlignment(mw_icon, Qt::AlignCenter | Qt::AlignBottom);
    m_layout->setAlignment(mw_text, Qt::AlignCenter | Qt::AlignTop);

    setLayout(m_layout);

    switch (type) {
    case ErrType_NotFound:
        mw_text->setText(tr("<strong>Unable to load file<br><i>%1</i></strong>").arg(fileName));
        break;
    case ErrType_Unknown:
        mw_text->setText(tr("<strong>Unable to view file<br><i>%1</i></strong>").arg(fileName));
        break;
    case ErrType_BadPlugin:
        mw_text->setText(tr("<strong>Unable to get widget from plugin</strong>"));
        break;
    }
}
