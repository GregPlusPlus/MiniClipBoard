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

#include "colorthumbnailwidget.h"

ColorThumbnailWidget::ColorThumbnailWidget(QColor color, QWidget *parent) : QWidget(parent), m_color(color)
{
    setFixedSize(20, 40);
}

void ColorThumbnailWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(QPen(QColor("#19232D"), 1.5));
    painter.setBrush(m_color);

    painter.drawEllipse(QPoint(width() / 2, height() / 2), 5, 5);
}
