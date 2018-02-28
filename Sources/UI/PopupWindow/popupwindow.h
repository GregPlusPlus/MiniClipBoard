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

#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QGuiApplication>

#include <QWidget>
#include <QDesktopWidget>

#include <QVBoxLayout>

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QBitmap>

#include <QUrl>

#include <QRect>

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include <QEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

#include <QDebug>

#include "tray.h"

class PopupWindow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float notifyOpacity READ notifyOpacity WRITE setNotifyOpacity)

public:
    enum WindowEdge{Edge_None, Edge_Left, Edge_Right, Edge_Top, Edge_Bottom, Edge_TopLeft, Edge_TopRight, Edge_BottomLeft, Edge_BottomRight};
    enum Side{Side_Left, Side_Right, Side_Top, Side_Bottom};

public:
    PopupWindow(QWidget *parent = 0);
    ~PopupWindow();

    void setCentralWidget(QWidget *widget);

    QWidget *centralWidget() const;

    QBitmap iconMask() const;
    void setIconMask(QBitmap iconMask);

    float notifyOpacity() const;
    void setNotifyOpacity(float notifyOpacity);

    bool getDrawProgress() const;

signals:
    bool toggled(bool visible);

public slots:
    void toggleWindow();
    void setTrayIcon(const QIcon &icon);
    void notify();
    void updateSizePos(const QSize &_size);
    void setDrawTrayProgress(bool _drawProgress);
    void setTrayProgress(int current, int max);

private:
    QWidget *mw_centralWidget;

    QIcon m_trayIcon;
    QBitmap m_iconMask;
    float m_notifyOpacity;

    QPoint m_mousePos;
    QPoint m_originalPos;
    QSize m_originalSize;
    int m_lastSize;
    bool m_mousePressed;
    WindowEdge m_edge;

    Side m_side;

    bool m_toggled;

    int m_currentProgress;
    int m_maxProgress;
    bool m_drawProgress;

private:
    QPoint globalPosToLocalPos(const QPoint &mousePos);
    WindowEdge getEdgeFromMousePos(const QPoint &mousePos);
    void mouseMove(const QPoint &point);
    void mousePressed(const QPoint point);
    void drawProgress();

protected:
    Tray *mw_tray;

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void updateMask();
};

#endif // WIDGET_H
