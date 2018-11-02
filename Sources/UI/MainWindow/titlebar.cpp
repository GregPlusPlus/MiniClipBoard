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

#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setWindowAnchored(m_windowAnchored);

    qApp->installEventFilter(this);
}

bool TitleBar::windowAnchored() const
{
    return m_windowAnchored;
}

void TitleBar::setWindowAnchored(bool windowAnchored)
{
    m_windowAnchored = windowAnchored;

    if(m_windowAnchored){
        setFixedHeight(5);
        setCursor(Qt::ArrowCursor);
    } else {
        setFixedHeight(18);
        setCursor(Qt::OpenHandCursor);
    }

    update();
}

void TitleBar::mouseMove(const QPoint &point)
{
    if(!m_windowAnchored && m_mousePressed) {
        emit mouseDP(point - m_lastP);

        m_lastP = point;
    }
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    QLinearGradient grad(QPoint(0, 0), QPoint(0, height()));
    if(m_windowAnchored) {
        grad.setColorAt(0, QColor("#282C34"));
    } else {
        grad.setColorAt(0, QColor("#363B47"));
    }
    grad.setColorAt(1, QColor("#282C34"));

    painter.setBrush(grad/*Qt::red*/);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    painter.setPen(QColor("#4A5260"));

    painter.drawLine(QPoint(width() / 2 - 6, 3), QPoint(width() / 2 + 6, 3));
    //    painter.drawLine(QPoint(width() / 2 - 6, 5), QPoint(width() / 2 + 6, 5));
    //    painter.drawLine(QPoint(width() / 2 - 6, 7), QPoint(width() / 2 + 6, 7));
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton) {
        return;
    }

    if(!m_windowAnchored) {
        setCursor(Qt::ClosedHandCursor);
        m_mousePressed = true;

        m_lastP = QCursor::pos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton) {
        return;
    }

    if(!m_windowAnchored) {
        setCursor(Qt::OpenHandCursor);
        m_mousePressed = false;
    }
}

bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    if(event->type() == QEvent::MouseMove && !m_windowAnchored && m_mousePressed) {
        mouseMove(QCursor::pos());
    }

    return false;
}
