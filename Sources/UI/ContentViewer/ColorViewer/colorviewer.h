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

#ifndef COLORVIEWER_H
#define COLORVIEWER_H

#include <QWidget>
#include <QLineEdit>

#include <QColor>

#include <QPaintEvent>

#include <QPainter>
#include <QBrush>
#include <QPen>

#include <QLinearGradient>
#include <QConicalGradient>
#include <QRadialGradient>

#include <QDebug>

#include <cmath>

class ColorViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ColorViewer(const QColor &color, QWidget *parent = nullptr);

signals:

public slots:

private:
    QLineEdit *mw_text;

    QColor m_color;

private:
    void drawColorWheel(QPainter &painter, const QRect &rect, const QColor &color);
    QPointF getPositionFromHS(float h, float s);
    float getHue(const QColor &color);
    float getSaturation(const QColor &color);
    float getValue(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // COLORVIEWER_H
