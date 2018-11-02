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

#include "dragdropscreen.h"

DragDropScreen::DragDropScreen(QWidget *parent) : QWidget(parent)
{
    setVisible(false);

    m_downIcon.load(":/icons/ic_arrow_downward_white_48dp");
    m_bucketIcon.load(":/icons/bucket_48dp");

    connect(&m_animTimer, &QTimer::timeout, this, &DragDropScreen::waveAnim);
}

void DragDropScreen::reveal()
{
    if(!m_ready) {
        return;
    }

    m_ready = false;

    show();
    raise();

    m_downPos   = 0;
    m_bucketPos = 0;
    m_wave      = 0;
    m_wavePos   = 0;

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacity);
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity");
    anim->setDuration(200);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
    connect(anim, &QPropertyAnimation::finished, [=]() {
        m_ready = true;
        m_wavePos = 0;
        m_downPos = 40;
        m_animTimer.start(10);
        opacity->deleteLater();
    });
    connect(anim, &QPropertyAnimation::valueChanged, [=](QVariant value) {
        m_downPos = 40.0 * value.toFloat();
        m_bucketPos = 5.0 * value.toFloat();
        update();
    });
}

void DragDropScreen::disappear()
{
    hide();

    m_animTimer.stop();
}

void DragDropScreen::waveAnim()
{
    if(m_wave == 3.1) {
        m_wave = 0;
    }

    m_wavePos = (cos(m_wave) * 10) - 10;
    m_wave += 0.05;

    update();
}

void DragDropScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);

    p.setBrush(QColor(30, 30, 40, 180));
    p.setPen(Qt::NoPen);

    p.drawRect(rect());

    p.drawPixmap((width() / 2) - (m_downIcon.width() / 2), (height() / 2) - (m_downIcon.height() / 2) - 40 + m_downPos + m_wavePos, m_downIcon);
    p.drawPixmap((width() / 2) - (m_bucketIcon.width() / 2), (height() / 2) - (m_bucketIcon.height() / 2) + 5 - m_bucketPos, m_bucketIcon);
}
