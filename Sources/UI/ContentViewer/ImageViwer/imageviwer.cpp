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

#include "imageviwer.h"

ImageViwer::ImageViwer(const QPixmap &image, QWidget *parent) : QWidget(parent), m_image(image)
{
    m_zoom = 1;

    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);

    mw_drawCheckeredBg = new QCheckBox(tr("draw checkered background"), this);
    mw_drawCheckeredBg->show();
    mw_drawCheckeredBg->setCursor(Qt::ArrowCursor);
    //mw_drawCheckeredBg->setChecked(true);

    updateScale();

    connect(mw_drawCheckeredBg, &QCheckBox::toggled, [=]() {
        update();
    });
}

void ImageViwer::drawCheckeredBg(QPainter &painter)
{
    painter.setBrush(QColor(Qt::white));

    painter.drawRect(0, 0, width(), height());

    painter.setBrush(QColor(Qt::gray));

    for(int i = 0; i < width(); i += 20) {
        for(int j = 0; j < height(); j += 10) {
            int offset = (int)((j / 10) % 2) * (int)10;
            painter.drawRect(i + offset, j, 10, 10);
        }
    }
}

void ImageViwer::constrainImgPos()
{
    if(m_actualImgPos.x() <= width() - 10 - (m_scale.width() * m_zoom)) {
        m_actualImgPos.setX(width() - 10 - (m_scale.width() * m_zoom));
    }

    if(m_actualImgPos.x() >= 10) {
        m_actualImgPos.setX(10);
    }

    if(m_actualImgPos.y() <= height() - 10 - (m_scale.height() * m_zoom)) {
        m_actualImgPos.setY(height() - 10 - (m_scale.height() * m_zoom));
    }

    if(m_actualImgPos.y() >= 10) {
        m_actualImgPos.setY(10);
    }
}

void ImageViwer::updateScale()
{
    m_scale = (m_image.width() > width() || m_image.height() > height() - 30)?m_image.size().scaled(QSize(width() - 20, height() - 45), Qt::KeepAspectRatio) * m_zoom:m_image.size();
    constrainImgPos();
}

void ImageViwer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    mw_drawCheckeredBg->move(5, height() - 25);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Qt4CompatiblePainting);

    painter.setPen(Qt::NoPen);

    painter.eraseRect(geometry());

    if(mw_drawCheckeredBg->isChecked()) {
        drawCheckeredBg(painter);
    }

    painter.drawPixmap(QRect(/*QPoint((width() / 2 - m_scale.width() * m_zoom / 2),
                       ((height() - 30) / 2 - m_scale.height() * m_zoom / 2)) + */ m_actualImgPos,
                       m_scale * m_zoom),
                       m_image);

    //if(mw_drawCheckeredBg->isChecked()) {
    painter.setPen(QColor("#19232D"));
    painter.setBrush(QColor("#313D4A"));

    painter.drawRoundRect(-5, height() - 30, mw_drawCheckeredBg->width() + 20, 35, 7, 7);
    //}
}

void ImageViwer::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    m_zoom += numSteps / 10.f;

    m_zoom = (m_zoom < 1)?1:m_zoom;

    if(m_zoom > 1) {
        setCursor(Qt::OpenHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }

    updateScale();

    update();
}

void ImageViwer::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = true;
}

void ImageViwer::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = false;
}

void ImageViwer::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();

    if(m_mousePress) {
        m_vect = m_mousePos - m_mousePosPress;
        m_actualImgPos = m_oldImgPos + m_vect;

        constrainImgPos();

        update();
    }
}

void ImageViwer::mousePressEvent(QMouseEvent *event)
{
    m_mousePress = true;
    m_mousePosPress = event->pos();

    if(m_zoom > 1) {
        setCursor(Qt::ClosedHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ImageViwer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    m_mousePress = false;
    m_oldImgPos = m_actualImgPos;

    if(m_zoom > 1) {
        setCursor(Qt::OpenHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }

    update();
}

void ImageViwer::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateScale();
}
