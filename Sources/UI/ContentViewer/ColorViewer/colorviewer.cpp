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

#include "colorviewer.h"

ColorViewer::ColorViewer(const QColor &color, QWidget *parent) : QWidget(parent), m_color(color)
{
    mw_text = new QLineEdit(color.name(), this);
    mw_text->setReadOnly(true);
    mw_text->setAlignment(Qt::AlignCenter);
}

void ColorViewer::drawColorWheel(QPainter &painter, const QRect &rect, const QColor &color)
{
    QPoint center(rect.x() + rect.width() / 2, rect.y() + rect.height() / 2);
    int rad = (rect.width() >= rect.height())?rect.width() / 2:rect.height() / 2;

    QConicalGradient conicalGradient(center, 0);
    conicalGradient.setColorAt(0, Qt::red);
    conicalGradient.setColorAt(0.165, Qt::magenta);
    conicalGradient.setColorAt(0.33, Qt::blue);
    conicalGradient.setColorAt(0.495, Qt::cyan);
    conicalGradient.setColorAt(0.66, Qt::green);
    conicalGradient.setColorAt(0.83, Qt::yellow);
    conicalGradient.setColorAt(1, Qt::red);

    painter.setBrush(conicalGradient);

    painter.drawEllipse(center, rad, rad);

    QRadialGradient whiteBlur(center, rad);
    whiteBlur.setColorAt(0, Qt::white);
    whiteBlur.setColorAt(1, Qt::transparent);

    painter.setBrush(whiteBlur);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(center, rad, rad);

    double h = (float)(getHue(color) * M_PI) / 180.0f;

    QPointF curPos = getPositionFromHS(h, getSaturation(color));

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 1.5));

    painter.drawRoundedRect((curPos.x() * rad) + center.x() - 1,
                            (curPos.y() * rad) + center.y() - 1,
                            5, 5, 5, 5);

    /*painter.drawPoint((curPos.x() * rad) + center.x(),
                      (curPos.y() * rad) + center.y());*/
}

QPointF ColorViewer::getPositionFromHS(float h, float s)
{
    QPointF p = QPointF(cos(h) * s, sin(h) * s);

    return p;
}

float ColorViewer::getHue(const QColor &color)
{
    int red = color.red();
    int blue = color.blue();
    int green = color.green();

    if(red == blue && blue == green) {
        return 0.0f;
    }

    float min = qMin(qMin(red, green), blue);
    float max = qMax(qMax(red, green), blue);

    float hue = 0.0f;

    if (max == red) {
        hue = (green - blue) / (max - min);

    } else if (max == green) {
        hue = 2.0f + (blue - red) / (max - min);

    } else {
        hue = 4.0f + (red - green) / (max - min);
    }

    hue *= 60;

    if (hue < 0) {
        hue = hue + 360;
    }

    return hue;
}

float ColorViewer::getSaturation(const QColor &color)
{
    int red = color.red();
    int blue = color.blue();
    int green = color.green();

    float min = qMin(qMin(red, green), blue);
    float max = qMax(qMax(red, green), blue);

    if(max == 0) {
        return 0.0f;
    } else {
        return 1.0f - (min / max);
    }
}

float ColorViewer::getValue(const QColor &color)
{
    int red = color.red();
    int blue = color.blue();
    int green = color.green();

    float max = qMax(qMax(red, green), blue);

    return max / 255.0f;
}

void ColorViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setPen(QPen(QColor("#19232D"), 1.2));
    painter.setBrush(m_color);

    painter.drawRoundedRect(20, 20, width() - 40, 20, 7, 7);

    /*QLinearGradient liearGradient(20, 60, width() - 40, 60);
    liearGradient.setColorAt(0, Qt::red);
    liearGradient.setColorAt(0.33, Qt::green);
    liearGradient.setColorAt(0.66, Qt::blue);
    liearGradient.setColorAt(1, Qt::red);

    painter.setBrush(liearGradient);

    painter.drawRect(20, 60, width() - 40, 30);*/

    drawColorWheel(painter, QRect(20, 60, width() - 80, width() - 80), m_color);

    QLinearGradient valueGradient(0, 60, 0, width() - 80 + 60);
    valueGradient.setColorAt(0, Qt::white);
    valueGradient.setColorAt(1, Qt::black);

    painter.setBrush(valueGradient);

    painter.drawRoundedRect(width() - 40, 60, 20, width() - 80, 7, 7);

    painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

    painter.setBrush(Qt::black);

    painter.drawLine(width() - 40,
                     (60 + (width() - 80) * (1 - getValue(m_color))),
                     width() - 20,
                     (60 + (width() - 80) * (1 - getValue(m_color))));

    mw_text->move((width() / 2) - (mw_text->width() / 2) - 20, width());
}
