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

#ifndef TOOLTIPWINDOW_H
#define TOOLTIPWINDOW_H

#include <QObject>
#include <QWidget>

#include <QCursor>

#include <QPainter>

#include <QBitmap>

#include <QTimer>

#include <QPaintEvent>
#include <QMouseEvent>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QDebug>

#include <cmath>

class TooltipWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TooltipWindow(QWidget *parent = nullptr);

    QWidget *getCentralWidget() const;
    void setCentralWidget(QWidget *value);

    bool getAutoClose() const;
    void setAutoClose(bool autoClose);

signals:
    void closeRequested();

public slots:

private:
    QWidget *mw_centralWidget;

    QTimer m_timerMousePosUpdate;

    bool m_autoClose = true;

private:
    void updateOpacity();
    int getMouseDistance(const QPoint &p);

    void fadeIn();

protected:
    void paintEvent(QPaintEvent *event);

    void updateMask();
};

#endif // TOOLTIPWINDOW_H
