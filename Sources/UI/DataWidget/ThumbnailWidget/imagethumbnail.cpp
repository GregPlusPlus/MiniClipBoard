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

#include "imagethumbnail.h"

ImageThumbnail::ImageThumbnail(QPixmap *pix, QWidget *parent) : QWidget(parent), m_pixmap(pix)
{
    setFixedSize(40, 40);
    setAttribute(Qt::WA_TranslucentBackground);

    updatePix();
}

QPixmap *ImageThumbnail::pixmap() const
{
    return m_pixmap;
}

void ImageThumbnail::setPixmap(QPixmap *pixmap)
{
    m_pixmap = pixmap;
}

void ImageThumbnail::updatePix()
{
    m_scaledPix = m_pixmap->scaled(QSize(width() - 1, height() - 1), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void ImageThumbnail::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(QPen(QColor("#19232D"), 1));
    painter.setBrush(Qt::black);

    int pixY = (height() / 2) - (m_scaledPix.height() / 2);

    painter.drawRect(QRect(QPoint(0, pixY), m_scaledPix.size()));
    painter.drawPixmap(QRect(QPoint(1, pixY + 1), QSize(m_scaledPix.width() - 1, m_scaledPix.height() - 1)), m_scaledPix);
}

void ImageThumbnail::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    updatePix();
}
