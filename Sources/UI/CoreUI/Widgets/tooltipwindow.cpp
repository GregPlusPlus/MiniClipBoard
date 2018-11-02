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

#include "tooltipwindow.h"

TooltipWindow::TooltipWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
    setWindowOpacity(.9);
    fadeIn();

    mw_centralWidget = new QWidget(this);
    mw_centralWidget->setMinimumSize(80, 30);

    move(QCursor::pos());

    connect(&m_timerMousePosUpdate, &QTimer::timeout, [=]() {
        updateOpacity();
    });

    m_timerMousePosUpdate.start(42);
}

QWidget *TooltipWindow::getCentralWidget() const
{
    return mw_centralWidget;
}

void TooltipWindow::setCentralWidget(QWidget *value)
{
    mw_centralWidget = value;
}

bool TooltipWindow::getAutoClose() const
{
    return m_autoClose;
}

void TooltipWindow::setAutoClose(bool autoClose)
{
    if(autoClose) {
        QCursor::setPos(x() + width() / 2, y() + height() / 2);
    }
    m_autoClose = autoClose;
}

void TooltipWindow::updateOpacity()
{
    int dist = getMouseDistance(QCursor::pos());

    if(dist > 300 && m_autoClose) {
        m_timerMousePosUpdate.stop();
        emit closeRequested();
    }

    dist = (dist < width() / 2)?0:dist;

    double opacity = 1.f - ((double)(dist) / (300.f));

    opacity = (opacity < 0)?0:opacity;

    setWindowOpacity(.9f * opacity);
}

int TooltipWindow::getMouseDistance(const QPoint &p)
{
    QPoint center;
    center.setX(x() + (width() / 2));
    center.setY(y() + (height() / 2));

    int dx = center.x() - p.x();
    int dy = center.y() - p.y();

    return sqrt((dx * dx) + (dy * dy));
}

void TooltipWindow::fadeIn()
{
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity");

    setGraphicsEffect(opacity);

    anim->setDuration(200);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
}

void TooltipWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setBrush(QColor("#313D4A"));
    painter.setPen(QPen(QColor("#19232D"), 1.2));

    QRect rect(0, 0, width(), height());

    painter.drawRoundedRect(rect, 5.5, 5.5);

    if(mw_centralWidget) {
        mw_centralWidget->setGeometry(0, 0, width(), height());
        updateMask();
    }
}

void TooltipWindow::updateMask()
{
    QBitmap mask(width(), height());
    mask.clear();

    QPainter painter(&mask);

    QBrush bg(Qt::color1);
    painter.setBrush(bg);

    painter.drawRoundedRect(1, 1, mw_centralWidget->width() - 3, mw_centralWidget->height() - 3, 5.5, 5.5);

    mw_centralWidget->setMask(mask);
}
