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

#ifndef IMAGEVIWER_H
#define IMAGEVIWER_H

#include <QWidget>
#include <QCheckBox>

#include <QPixmap>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QPaintEvent>
#include <QMouseEvent>

#include <QDebug>

class ImageViwer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViwer(const QPixmap &image, QWidget *parent = nullptr);

signals:

public slots:

private:
    QCheckBox *mw_drawCheckeredBg;
    QPixmap m_image;
    QSize m_scale;

    QPoint m_mousePos;
    QPoint m_mousePosPress;
    QPoint m_vect;
    QPoint m_oldImgPos;
    QPoint m_actualImgPos;

    float m_zoom;
    bool m_mouseIn;
    bool m_mousePress;

private:
    void drawCheckeredBg(QPainter &painter);
    void constrainImgPos();
    void updateScale();

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // IMAGEVIWER_H
