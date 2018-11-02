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

#include "imageviewer.h"

ImageViewer::ImageViewer(const QPixmap &image, QWidget *parent) : QWidget(parent), m_image(image)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);

    mw_toolsWidget = new QWidget(this);
    mw_toolsWidget->setStyleSheet("background: none;");

    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);

    mw_toolsWidget->setLayout(m_layout);

    mw_drawCheckeredBg = new QCheckBox(tr("draw checkered background"), this);
    mw_drawCheckeredBg->show();
    mw_drawCheckeredBg->setCursor(Qt::ArrowCursor);
    mw_drawCheckeredBg->setMaximumHeight(30);
    //mw_drawCheckeredBg->setChecked(true);

    mw_fitView = new FlatActionButton(QIcon(":/icons/ic_crop_free_white_18dp"), tr("Fit view"));
    connect(mw_fitView, &FlatActionButton::clicked, [=]() {
        m_zoom = 1;
        updateScale();
    });

    m_layout->addWidget(mw_drawCheckeredBg);
    m_layout->addWidget(mw_fitView);

    updateScale();

    connect(mw_drawCheckeredBg, &QCheckBox::toggled, [=]() {
        update();
    });
}

void ImageViewer::drawCheckeredBg(QPainter &painter)
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

void ImageViewer::constrainImgPos()
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

void ImageViewer::updateScale()
{
    m_scale = (m_image.width() > width() || m_image.height() > height() - 30)?m_image.size().scaled(QSize(width() - 20, height() - 45), Qt::KeepAspectRatio) * m_zoom:m_image.size();
    constrainImgPos();

    update();
}

void ImageViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    //mw_drawCheckeredBg
    mw_toolsWidget->move(5, height() - 25);

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

    painter.drawRoundRect(-5, height() - 30, mw_toolsWidget->width() + 20, 35, 7, 7);
    //}
}

void ImageViewer::wheelEvent(QWheelEvent *event)
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
}

void ImageViewer::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = true;
}

void ImageViewer::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = false;
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();

    if(m_mousePress) {
        m_vect = m_mousePos - m_mousePosPress;
        m_actualImgPos = m_oldImgPos + m_vect;

        constrainImgPos();

        update();
    }
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    m_mousePress = true;
    m_mousePosPress = event->pos();

    if(m_zoom > 1) {
        setCursor(Qt::ClosedHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
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

void ImageViewer::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateScale();
}
