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

#ifndef DRAGDROPWIDGET_H
#define DRAGDROPWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QPainter>
#include <QBrush>
#include <QPen>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QTimer>

#include <QDebug>

class DragDropScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DragDropScreen(QWidget *parent = nullptr);

signals:

public slots:
    void reveal();
    void disappear();
    void waveAnim();

private:
    QPixmap m_downIcon;
    QPixmap m_bucketIcon;

    int m_downPos = 0;
    int m_bucketPos = 0;

    QTimer m_animTimer;
    double m_wave = 0;
    int m_wavePos = 0;

    bool m_ready = true;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DRAGDROPWIDGET_H
