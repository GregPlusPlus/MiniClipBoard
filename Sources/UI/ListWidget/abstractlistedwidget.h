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

#ifndef ABSTRACTLISTEDWIDGET_H
#define ABSTRACTLISTEDWIDGET_H


#include <QApplication>
#include <QGuiApplication>

#include <QWidget>

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRadialGradient>

#include <QCursor>

#include <QMouseEvent>

#include <QUuid>

#include <QDebug>

#include <cmath>

class AbstractListedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractListedWidget(QWidget *parent = nullptr);
    virtual ~AbstractListedWidget() = 0;
    QUuid Uuid() const;
    void setUuid(const QUuid &Uuid);

    int animationDuration() const;
    void setAnimationDuration(int animationDuration);

signals:
    void removed(AbstractListedWidget *widget);

public slots:
    virtual void removeWidget() = 0;
    void generateUuid();
    virtual void fadeIn() = 0;
    virtual void fadeOut() = 0;

private:
    QUuid m_Uuid;

    QPoint m_mousePos;

    bool m_mouseIn;

protected:
    int m_animationDuration;

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // ABSTRACTLISTEDWIDGET_H
