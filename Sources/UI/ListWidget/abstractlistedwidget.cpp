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

#include "abstractlistedwidget.h"

AbstractListedWidget::AbstractListedWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    qApp->installEventFilter(this);
}

AbstractListedWidget::~AbstractListedWidget()
{

}

QUuid AbstractListedWidget::Uuid() const
{
    return m_Uuid;
}

void AbstractListedWidget::setUuid(const QUuid &Uuid)
{
    m_Uuid = Uuid;
}

void AbstractListedWidget::generateUuid()
{
    m_Uuid = QUuid::createUuid();
}

void AbstractListedWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if(!m_mouseIn) {
        return;
    }

    QPainter painter(this);

    int alpha = (float)(1 - (float)(abs((width() / 2) - m_mousePos.x())) / (float)(width() / 2)) * 25.f;

    alpha = (alpha < 0)?0:alpha;

    QRadialGradient grad(QPoint(m_mousePos.x(), height() / 2),
                         1.5 * height(),
                         QPoint(m_mousePos.x(), height() / 2));

    grad.setColorAt(0, QColor(255, 255, 255, alpha));
    grad.setColorAt(1, Qt::transparent);

    painter.setBrush(grad);
    painter.setPen(Qt::NoPen);

    painter.drawRect(0, 0, width(), height());
}

void AbstractListedWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = true;

    update();
}

void AbstractListedWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_mouseIn = false;

    update();
}

void AbstractListedWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();

    update();
}

bool AbstractListedWidget::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if(event->type() == QEvent::MouseMove) {
        m_mousePos = mapFromGlobal(QCursor::pos());
        update();
    }

    return false;
}

int AbstractListedWidget::animationDuration() const
{
    return m_animationDuration;
}

void AbstractListedWidget::setAnimationDuration(int animationDuration)
{
    m_animationDuration = animationDuration;
}
