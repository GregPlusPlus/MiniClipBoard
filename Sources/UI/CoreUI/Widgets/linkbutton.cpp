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

#include "linkbutton.h"

LinkButton::LinkButton(QWidget *parent) : QAbstractButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
    setIcon(QIcon(":/icons/arrow_link"));
    setMinimumWidth(80);
    setFixedHeight(40);
}

QString LinkButton::description() const
{
    return m_description;
}

void LinkButton::setDescription(const QString &description)
{
    m_description = description;

    update();
}

void LinkButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    int yOffset = (description().isEmpty())?6:0;
    QSize iconSize = icon().availableSizes().at(0);

    QPainter p(this);

    p.drawPixmap(3, 5 + yOffset, icon().pixmap(iconSize));

    QFont font(p.font());
    font.setBold(true);
    p.setFont(font);

    p.setPen(Qt::white);

    p.drawText(QPoint(iconSize.width() + 10, 17 + yOffset),
               QFontMetrics(p.font()).elidedText(text(), Qt::ElideMiddle, width() - (iconSize.width() + 10 + 5)));

    font.setBold(false);
    p.setFont(font);

    p.setPen(QPen(QColor(255, 255, 255, 170)));

    p.drawText(QRect(QPoint(icon().availableSizes().at(0).width() + 10, 20 + yOffset), QSize(width(), 20)), description());
}
