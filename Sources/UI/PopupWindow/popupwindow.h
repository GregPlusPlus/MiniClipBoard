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

#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QGuiApplication>

#include <QWidget>
#include <QDesktopWidget>

#include <QScreen>

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
    enum Side{Side_Left, Side_Right, Side_Top, Side_Bottom, Side_None};

public:
    PopupWindow(QWidget *parent = nullptr);
    ~PopupWindow();

    void setCentralWidget(QWidget *widget);

    QWidget *centralWidget() const;

    QBitmap iconMask() const;
    void setIconMask(QBitmap iconMask);

    float notifyOpacity() const;
    void setNotifyOpacity(float notifyOpacity);

    bool getDrawProgress() const;

    Tray *tray() const;

    bool getAnchored() const;
    void setAnchored(bool _anchored);

signals:
    void toggled(bool visible);
    void anchored(bool anchored);

public slots:
    void toggleWindow();
    void setTrayIcon(const QIcon &icon);
    void notify();
    void updateSizePos(const QSize &_size);
    void setDrawTrayProgress(bool _drawProgress);
    void setTrayProgress(int current, int max);

private:
    QWidget *mw_centralWidget = nullptr;

    Tray    *mw_tray;

    QIcon m_trayIcon;
    QBitmap m_iconMask;
    float m_notifyOpacity;

    QPoint m_mousePos;
    QPoint m_originalPos;
    QSize m_originalSize;
    int m_lastSize;
    bool m_mousePressed = false;
    WindowEdge m_edge;

    Side m_side;

    bool m_toggled;

    bool m_anchored = true;

    int m_currentProgress   = 0;
    int m_maxProgress       = 0;
    bool m_drawProgress     = false;

private:
    WindowEdge getEdgeFromMousePos(const QPoint &mousePos);
    void updateSizePosAnchored(const QSize &_size);
    void updateSizePosFloating(const QSize &_size);
    void mouseMove(const QPoint &point);
    void mousePressed(const QPoint point);
    void drawProgress();
    void slideToCenter();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void updateMask();
};

#endif // WIDGET_H
