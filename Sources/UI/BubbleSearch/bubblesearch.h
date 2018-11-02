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

#ifndef BUBBLESEARCH_H
#define BUBBLESEARCH_H

#include <QWidget>
#include <QLineEdit>

#include <QHBoxLayout>

#include <QPainter>
#include <QLinearGradient>

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include <QMouseEvent>

#include <QIcon>
#include <QPixmap>
#include <QBitmap>

#include <QDebug>

#include "../CoreUI/Widgets/flatactionbutton.h"

class BubbleSearch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float animProgress READ animProgress WRITE setAnimProgress)
    Q_PROPERTY(float raiseProgress READ raiseProgress WRITE setRaiseProgress)

public:
    explicit BubbleSearch(const QIcon &icon, QWidget *parent = nullptr);

    bool isLarge() const;

    float animProgress() const;
    void setAnimProgress(float animProgress);

    void setSmallWidth(int smallWidth);

    float raiseProgress() const;
    void setRaiseProgress(float raiseProgress);

    void setRaised(const bool raised);

signals:
    void search(const QString &text);

public slots:
    void setPlaceholderText(const QString &placeholder);
    void toggle();

private:
    QHBoxLayout      *m_layout;
    QWidget          *mw_container;
    QLineEdit        *mw_searchText;
    FlatActionButton *mw_search;
    FlatActionButton *mw_close;

    QGraphicsOpacityEffect m_opacity;

    QIcon m_icon;

    bool m_large     = false;
    bool m_raised    = false;
    int m_smallWidth = 40;

    float m_animProgress = 0;
    float m_raiseProgress = 1;

private:
    void updateMask(const QRect &r, qreal radius);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // BUBBLESEARCH_H
