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

#include "bubblesearch.h"

BubbleSearch::BubbleSearch(const QIcon &icon, QWidget *parent) : QWidget(parent), m_icon(icon)
{
    setAttribute(Qt::WA_NoSystemBackground,     true);
    setAttribute(Qt::WA_TranslucentBackground,  true);
    setMouseTracking(true);

    setCursor(Qt::PointingHandCursor);

    setFixedSize(QSize(width(), m_smallWidth));

    m_opacity.setOpacity(0);

    mw_container = new QWidget(this);
    mw_container->setGraphicsEffect(&m_opacity);
    mw_container->setAttribute(Qt::WA_TranslucentBackground);
    mw_container->setFixedSize(QSize(m_smallWidth, m_smallWidth));
    mw_container->hide();

    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(7, 0, 7, 0);

    mw_searchText = new QLineEdit(this);
    mw_searchText->setStyleSheet("QLineEdit{font: bold 12px;}");
    connect(mw_searchText, &QLineEdit::returnPressed, [=]() {
        QString str = mw_searchText->text();
        mw_searchText->setText(QString());
        emit search(str);
        toggle();
    });

    mw_search = new FlatActionButton(QIcon(":/icons/ic_search_white_24dp"), tr("Search"), this);
    connect(mw_search, &FlatActionButton::clicked, [=]() {
        emit search(mw_searchText->text());
        mw_searchText->setText(QString());
        toggle();
    });

    mw_close = new FlatActionButton(QIcon(":/icons/ic_clear_white_18dp"), tr("Close"), this);
    connect(mw_close, &FlatActionButton::clicked, [=]() {
        mw_searchText->setText(QString());
        toggle();
    });

    m_layout->addWidget(mw_search);
    m_layout->addWidget(mw_searchText);
    m_layout->addWidget(mw_close);

    mw_container->setLayout(m_layout);
}

void BubbleSearch::setPlaceholderText(const QString &placeholder)
{
    mw_searchText->setPlaceholderText(placeholder);
}

void BubbleSearch::toggle()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "animProgress", this);
    anim->setDuration(500);
    if(m_large) {
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->setEasingCurve(QEasingCurve::InBack);
    } else {
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->setEasingCurve(QEasingCurve::OutQuint);
        mw_container->show();
    }
    connect(anim, &QPropertyAnimation::finished, [=]() {
        if(!m_large) {
            mw_container->hide();
        }
    });

    m_large = !m_large;

    if(!m_large && m_raised) {
        setRaised(false);
    }

    mw_searchText->setFocus(Qt::MouseFocusReason);

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

float BubbleSearch::raiseProgress() const
{
    return m_raiseProgress;
}

void BubbleSearch::setRaiseProgress(float raiseProgress)
{
    m_raiseProgress = raiseProgress;

    update();
}

void BubbleSearch::updateMask(const QRect &r, qreal radius)
{
    QBitmap mask(size());
    mask.clear();

    QPainter painter(&mask);
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    painter.setBrush(QBrush(Qt::color1));

    QRect rect = r;

    rect.setX(r.x() - 1);
    rect.setY(r.y() - 1);
    rect.setWidth(r.width() + 2);
    rect.setHeight(r.height() + 2);

    painter.drawRoundedRect(rect, radius, radius);

    setMask(mask);
}

void BubbleSearch::setRaised(const bool raised)
{
    m_raised = raised;

    QPropertyAnimation *anim = new QPropertyAnimation(this, "raiseProgress", this);
    if(!raised) {
        anim->setDuration(200);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
//        anim->setEasingCurve(QEasingCurve::InQuad);
    } else {
        anim->setDuration(400);
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->setEasingCurve(QEasingCurve::InQuart);
    }
    connect(anim, &QPropertyAnimation::finished, [=]() {
    });
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BubbleSearch::setSmallWidth(int smallWidth)
{
    m_smallWidth = smallWidth;

    update();
    setFixedHeight(m_smallWidth);
}

float BubbleSearch::animProgress() const
{
    return m_animProgress;
}

void BubbleSearch::setAnimProgress(float animProgress)
{
    m_animProgress = animProgress;

    m_opacity.setOpacity(animProgress);

    update();
}

bool BubbleSearch::isLarge() const
{
    return m_large;
}

void BubbleSearch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHints(QPainter::HighQualityAntialiasing);

    p.setBrush(Qt::transparent);
    p.setPen(Qt::transparent);

    p.drawRect(rect());

    QLinearGradient grad(QPoint(0, 0), QPoint(0, height()));
    grad.setColorAt(0, QColor("#323D47"));
    grad.setColorAt(1, QColor("#242C33"));

    qreal thickness = 1.2;

    p.setBrush(grad);
    p.setPen(QPen(QColor("#19232D"), thickness));

    int w = (m_animProgress) * (width() - m_smallWidth) + m_smallWidth;
    int y = ((m_raiseProgress) * 15) + thickness;

    qreal radius = (1.0 - m_animProgress) * (height() - 4) + 4;
    QRect rect((width() / 2) - (w / 2) + thickness, y, w - (thickness * 2), m_smallWidth - (thickness * 2));

    p.drawRoundedRect(rect, radius, radius);

    QSize pixSize = m_icon.availableSizes().at(0);
    QPixmap pix(m_icon.pixmap(pixSize));

    p.setOpacity(1.0 - (m_animProgress * 2));

    p.drawPixmap(QPoint((width() / 2) - (pixSize.width() / 2), ((m_smallWidth / 2) - (pixSize.height() / 2)) + y), pix);

    mw_container->setFixedSize(QSize((width() - 5) * m_animProgress, m_smallWidth * m_animProgress));
    mw_container->move(QPoint((width() / 2) - (mw_container->width() / 2), ((m_smallWidth / 2) - (mw_container->height() / 2)) + y));


    updateMask(rect, radius);
}

void BubbleSearch::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(!m_large) {
        toggle();
    }
}

void BubbleSearch::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    if(!m_large && !m_raised) {
        setRaised(true);
    }
}

void BubbleSearch::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    if(!m_large && m_raised) {
        setRaised(false);
    }
}
