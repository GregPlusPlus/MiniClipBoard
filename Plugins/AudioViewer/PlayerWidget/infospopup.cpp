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

#include "infospopup.h"

InfosPopup::InfosPopup(Side side, QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint/* | Qt::SubWindow*/ | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);

    setSide(side);

    setMinimumSize(60, 60);

    mw_container = new QWidget(this);
    mw_container->setAttribute(Qt::WA_TranslucentBackground);

    qApp->installEventFilter(this);

    updatePopupPos();
}

void InfosPopup::setLayout(QLayout *layout)
{
    mw_container->setLayout(layout);

    updatePopupPos();
}

void InfosPopup::setAnchorWidget(QWidget *anchor)
{
    mw_anchor = anchor;

    updatePopupPos();
}

void InfosPopup::cleanDestroy()
{
    setAnchorWidget(nullptr);
    deleteLater();
}

void InfosPopup::moveToPoint(const QPoint &point)
{
    m_point = point;
    move(point.x() - (width() / 2), point.y());
}

void InfosPopup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    mw_container->adjustSize();

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QLinearGradient grad(QPoint(0, m_indicatorSize), QPoint(0, height()));
    grad.setColorAt(0, QColor("#435363"));
    grad.setColorAt(1, QColor("#313C47"));

    p.setBrush(grad);
    p.setPen(QPen(QColor("#19232D"), 1.01));

    int yOff = (m_side == Side_Bottom)?m_indicatorSize:1;

    QRect rect(1, yOff, width() - 2, height() - m_indicatorSize - 1);

    p.drawRoundedRect(rect, 5.5, 5.5);

    if(m_side == Side_Bottom) {
        const QPoint indicatorPoints[3] = {
            QPoint(width() / 2, 0),
            QPoint((width() / 2) + m_indicatorSize, m_indicatorSize),
            QPoint((width() / 2) - m_indicatorSize, m_indicatorSize)
        };

        p.drawPolygon(indicatorPoints, 3);
    } else {
        const QPoint indicatorPoints[3] = {
            QPoint(width() / 2, height()),
            QPoint((width() / 2) + m_indicatorSize, height() - m_indicatorSize),
            QPoint((width() / 2) - m_indicatorSize, height() - m_indicatorSize)
        };

        p.drawPolygon(indicatorPoints, 3);
    }

    p.setPen(QPen((m_side == Side_Bottom)?QColor("#435363"):QColor("#313C47"), 2));

    p.drawLine((width() / 2) - m_indicatorSize + 2, (m_side == Side_Bottom)?m_indicatorSize:height() - m_indicatorSize,
               (width() / 2) + m_indicatorSize - 2, (m_side == Side_Bottom)?m_indicatorSize:height() - m_indicatorSize);

    resize(mw_container->width() + 1, mw_container->height() + m_indicatorSize + 1);

    mw_container->move(1, (m_side == Side_Bottom)?m_indicatorSize + 1:1);
    mw_container->resize(size() - QSize(2, m_indicatorSize - 2));
}

void InfosPopup::updatePopupPos()
{
    if(mw_anchor) {
        if(m_side == Side_Bottom) {
            moveToPoint(mw_anchor->mapToGlobal(QPoint(mw_anchor->x() + (mw_anchor->width() / 2),
                                                      mw_anchor->y() + mw_anchor->height()) - mw_anchor->pos()));
        } else {
            moveToPoint(mw_anchor->mapToGlobal(QPoint(mw_anchor->x() + (mw_anchor->width() / 2),
                                                      mw_anchor->y() - height()) - mw_anchor->pos()));
        }
    }

    raise();
}

void InfosPopup::setVisible(bool visible)
{
    QWidget::setVisible(visible);

    updatePopupPos();
}

void InfosPopup::trigger()
{
    m_triggered = !m_triggered;
    setVisible(m_triggered);
}

InfosPopup::Side InfosPopup::side() const
{
    return m_side;
}

void InfosPopup::setSide(const Side &side)
{
    m_side = side;

    updatePopupPos();
}

bool InfosPopup::isParent(QObject *object, QObject *supposedParent)
{
    if(!supposedParent && !object) {
        return false;
    }

    while (object) {
        if(object->parent() == supposedParent) {
            return true;
        }

        object = object->parent();
    }

    return false;
}

bool InfosPopup::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(event)

    QWidget *w = qobject_cast<QWidget*>(watched);

    if((w == this || w == mw_anchor || isParent(mw_anchor, watched)) &&
            (event->type() == QEvent::Create ||
             event->type() == QEvent::Move   ||
             event->type() == QEvent::Resize ||
             event->type() == QEvent::ActivationChange)) {

        if(mw_anchor) {
            updatePopupPos();

            if(m_triggered && !mw_anchor->isVisible()) {
                setVisible(false);
            }
            if(m_triggered && mw_anchor->isVisible()) {
                setVisible(true);
            }
        }
    }

    return false;
}
