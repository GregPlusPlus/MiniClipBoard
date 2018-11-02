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

#include "loaderscreen.h"

LoaderScreen::LoaderScreen(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;

    mw_text = new QLabel("Text", this);

    m_layout->addStretch(10);
    m_layout->addWidget(mw_text);
    m_layout->addStretch(10);

    m_layout->setAlignment(mw_text, Qt::AlignCenter);

    setLayout(m_layout);
}

void LoaderScreen::reveal()
{
    show();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity", this);

    setGraphicsEffect(opacity);

    anim->setDuration(150);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
}

void LoaderScreen::disappear()
{
    mw_text->setText("");

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity", this);
    connect(anim, &QPropertyAnimation::finished, [=]() {
        hide();
    });

    setGraphicsEffect(opacity);

    anim->setDuration(150);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
}

void LoaderScreen::setMessage(const QString &text)
{
    mw_text->setText(text);
}

void LoaderScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setBrush(QColor(20, 20, 20, 200));
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect());
}
