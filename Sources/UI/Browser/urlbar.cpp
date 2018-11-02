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

#include "urlbar.h"

URLBar::URLBar(QWidget *parent) : QLineEdit(parent)
{
    setStyleSheet("QLineEdit{padding-left: 28px;}");
    home(0);

    mw_icon = new IconWidget(this);
    mw_icon->setPixmap(QPixmap(":/icons/ic_language_white_18dp"));
    mw_icon->raise();
}

IconWidget *URLBar::iconWidget() const
{
    return mw_icon;
}

void URLBar::resizeEvent(QResizeEvent *event)
{
    QLineEdit::resizeEvent(event);

    mw_icon->move(5, 4);
}
