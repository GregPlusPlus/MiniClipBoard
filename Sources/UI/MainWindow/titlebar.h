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

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QApplication>

#include <QWidget>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QMouseEvent>

#include <QDebug>

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

    bool windowAnchored() const;
    void setWindowAnchored(bool windowAnchored);

signals:
    void mouseDP(const QPoint &dP);

public slots:

private:
    bool m_windowAnchored = true;

    bool m_mousePressed = false;

    QPoint m_lastP;

private:
    void mouseMove(const QPoint &point);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // TITLEBAR_H
