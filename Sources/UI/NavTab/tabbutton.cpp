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

#include "tabbutton.h"

TabButton::TabButton(QWidget *parent) : QPushButton(parent)
{
    m_index = 0;
    m_fade = 0;
    m_mousePress = false;

    setAttribute(Qt::WA_TranslucentBackground);
    setFixedHeight(50);
    setCursor(Qt::PointingHandCursor);
    setAcceptDrops(true);

    connect(this, &QPushButton::clicked, [=]() {
        emit buttonSelected(m_index);
        update();
    });
}

int TabButton::index() const
{
    return m_index;
}

void TabButton::setIndex(int index)
{
    m_index = index;

    update();
}

int TabButton::fade() const
{
    return m_fade;
}

void TabButton::setFade(int fade)
{
    m_fade = fade;

    update();
}

void TabButton::setIconNormal(const QIcon &icon)
{
    m_normalIcon = icon;
}

void TabButton::setIconHighlighted(const QIcon &icon)
{
    m_highlightedIcon = icon;
}

void TabButton::mousePressEvent(QMouseEvent *event)
{
    m_mousePress = true;

    fadeIn(50);

    QPushButton::mousePressEvent(event);
}

void TabButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePress = false;

    fadeIn(50); //Not a typo

    QPushButton::mouseReleaseEvent(event);
}

bool TabButton::selected() const
{
    return m_selected;
}

void TabButton::setSelected(bool selected)
{
    m_selected = selected;

    if(m_selected) {
        fadeIn(200);
    } else {
        fadeOut(200);
    }

    putIcon();
}

void TabButton::setSelected(bool selected, bool animated)
{
    if(animated) {
        setSelected(selected);

        return;
    } else {
        m_selected = selected;
        if(m_selected) {
            m_fade = 50;
        } else {
            m_fade = 0;
        }
    }

    putIcon();
}

void TabButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    if(m_mousePress) {
        painter.setBrush(QColor(40, 40, 40, m_fade));
    } else {
        painter.setBrush(QColor(255, 255, 255, m_fade));
    }

    painter.setPen(Qt::NoPen);

    painter.drawRect(0, 0, width(), height());

    QPixmap pixmap = icon().pixmap(icon().actualSize(QSize(32, 32)));

    painter.drawPixmap(width() / 2 - pixmap.width() / 2,
                       height() / 2 - pixmap.height() / 2,
                       pixmap);
}

void TabButton::putIcon()
{
    if(m_selected) {
        setIcon(m_highlightedIcon);
    } else {
        setIcon(m_normalIcon);
    }
}

void TabButton::fadeIn(int duration)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "fade");

    anim->setDuration(duration);
    anim->setStartValue(0);
    anim->setEndValue(50);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
}

void TabButton::fadeOut(int duration)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "fade");

    anim->setDuration(duration);
    anim->setStartValue(50);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
}
