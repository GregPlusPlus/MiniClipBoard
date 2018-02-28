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

#include "popupwindow.h"

PopupWindow::PopupWindow(QWidget *parent)
    : QWidget(parent)
{
    mw_centralWidget = nullptr;
    m_mousePressed = false;

    m_drawProgress = false;
    m_currentProgress = 0;
    m_maxProgress = 0;

    qApp->setQuitOnLastWindowClosed(false);
    qApp->installEventFilter(this);
    this->installEventFilter(this);

    setFixedSize(350, 500);

    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
    setAcceptDrops(true);

    mw_tray = new Tray(this);
    connect(mw_tray, SIGNAL(quit()), qApp, SLOT(quit()));
    connect(mw_tray, SIGNAL(triggered()), this, SLOT(toggleWindow()));
    connect(mw_tray, &Tray::resetSize, [=]() {
        updateSizePos(QSize(350, 500));
    });

    mw_tray->show();

    connect(QApplication::desktop(), &QDesktopWidget::workAreaResized, [=]() {
        updateSizePos(size());
    });
}

PopupWindow::~PopupWindow()
{

}

void PopupWindow::toggleWindow()
{
    setVisible(!isVisible());
    raise();
    activateWindow();
    emit toggled(isVisible());

    updateSizePos(size());
}

void PopupWindow::setTrayIcon(const QIcon &icon)
{
    m_trayIcon = icon;
    mw_tray->setIcon(m_trayIcon);
}

void PopupWindow::notify()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "notifyOpacity");
    anim->setDuration(300);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->start();

    connect(anim, &QPropertyAnimation::finished, [=]() {
        mw_tray->setIcon(m_trayIcon);
    });
}

float PopupWindow::notifyOpacity() const
{
    return m_notifyOpacity;
}

void PopupWindow::setNotifyOpacity(float notifyOpacity)
{
    m_notifyOpacity = notifyOpacity;

    QSize pixSize = m_trayIcon.availableSizes().at(0);
    QPixmap pix = m_trayIcon.pixmap(pixSize);

    QPainter painter(&pix);
    painter.setBrush(QColor(255, 255, 255, notifyOpacity * 150));
    painter.setPen(Qt::NoPen);
    painter.setClipRegion(QRegion(m_iconMask));

    painter.drawRect(QRect(QPoint(0, 0), pixSize));

    mw_tray->setIcon(pix);

    drawProgress();
}

QBitmap PopupWindow::iconMask() const
{
    return m_iconMask;
}

void PopupWindow::setIconMask(QBitmap iconMask)
{
    m_iconMask = iconMask;
}

void PopupWindow::updateSizePos(const QSize &_size)
{
    QRect screenRect = QApplication::desktop()->screenGeometry();
    QRect availRect = QApplication::desktop()->availableGeometry();

    setFixedSize(_size);

    if(availRect.height() < screenRect.height() && availRect.y() == 0) {
        move(availRect.width() - _size.width() + 1, availRect.height() - _size.height());
        m_side = Side_Bottom;
    } else if(availRect.y() > 0) {
        move(availRect.width() - _size.width(), availRect.y());
        m_side = Side_Top;
    } else if(availRect.width() < screenRect.width() && availRect.x() == 0) {
        move(availRect.width() - _size.width(), screenRect.height() - _size.height());
        m_side = Side_Right;
    } else  if(availRect.x() > 0) {
        move(availRect.x(), screenRect.height() - _size.height());
        m_side = Side_Left;
    } else {
        move(availRect.width() - _size.width() + 1, availRect.height() - _size.height());
        m_side = Side_Bottom;
    }
}

void PopupWindow::setTrayProgress(int current, int max)
{
    m_currentProgress = current;
    m_maxProgress = max;

    drawProgress();
}

bool PopupWindow::getDrawProgress() const
{
    return m_drawProgress;
}

void PopupWindow::setDrawTrayProgress(bool _drawProgress)
{
    m_drawProgress = _drawProgress;

    drawProgress();
}

QPoint PopupWindow::globalPosToLocalPos(const QPoint &mousePos)
{
    return mousePos - pos();
}

PopupWindow::WindowEdge PopupWindow::getEdgeFromMousePos(const QPoint &mousePos)
{
    QPoint localMousePos = globalPosToLocalPos(mousePos);

    if(localMousePos.y() <= 5 && localMousePos.y() >= 0 &&
            localMousePos.x() <= 5 && localMousePos.x() >= 0) {
        return Edge_TopLeft;
    } else if(localMousePos.y() <= 5 && localMousePos.y() >= 0 &&
              localMousePos.x() >= width() - 5 && localMousePos.x() <= width()) {
        return Edge_TopRight;
    } else if(localMousePos.y() >= height() - 5 && localMousePos.y() <= height() &&
              localMousePos.x() <= 5 && localMousePos.x() >= 0) {
        return Edge_BottomLeft;
    } else if(localMousePos.y() >= height() - 5 && localMousePos.y() <= height() &&
              localMousePos.x() >= width() - 5 && localMousePos.x() <= width()) {
        return Edge_BottomRight;
    } else if(localMousePos.y() <= 5 && localMousePos.y() >= 0) {
        return Edge_Top;
    } else if(localMousePos.x() <= 5 && localMousePos.x() >= 0) {
        return Edge_Left;
    } else if(localMousePos.y() >= height() - 5 && localMousePos.y() <= height()) {
        return Edge_Bottom;
    } else if(localMousePos.x() >= width() - 5 && localMousePos.x() <= width()) {
        return Edge_Right;
    } else {
        return Edge_None;
    }
}

void PopupWindow::mouseMove(const QPoint &point)
{
    if(!m_mousePressed) {
        m_edge = getEdgeFromMousePos(point);
        if(m_edge == Edge_Top && (m_side == Side_Left || m_side == Side_Bottom || m_side == Side_Right)) {
            setCursor(Qt::SizeVerCursor);
        } else if(m_edge == Edge_TopLeft && (m_side == Side_Bottom || m_side == Side_Right)) {
            setCursor(Qt::SizeFDiagCursor);
        } else if(m_edge == Edge_Left && (m_side == Side_Top || m_side == Side_Bottom || m_side == Side_Right)) {
            setCursor(Qt::SizeHorCursor);
        } else if(m_edge == Edge_BottomLeft && m_side == Side_Top) {
            setCursor(Qt::SizeBDiagCursor);
        } else if(m_edge == Edge_Bottom && m_side == Side_Top) {
            setCursor(Qt::SizeVerCursor);
        } else if(m_edge == Edge_BottomRight) {
            setCursor(Qt::ArrowCursor);
        } else if(m_edge == Edge_Right && m_side == Side_Left) {
            setCursor(Qt::SizeHorCursor);
        } else if(m_edge == Edge_TopRight && m_side == Side_Left) {
            setCursor(Qt::SizeBDiagCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    } else if(m_mousePressed) {
        switch(m_side) {
        case Side_Bottom: {
            if(m_edge == Edge_Top) {
                int dy = -(QCursor::pos().y() - m_mousePos.y());
                int height = m_originalSize.height() + dy;
                height = (height > 500)?height:500;
                updateSizePos(QSize(width(), height));
            } else if(m_edge == Edge_Left) {
                int dx = -(QCursor::pos().x() - m_mousePos.x());
                int width = m_originalSize.width() + dx;
                width = (width > 350)?width:350;
                updateSizePos(QSize(width, height()));
            } else if(m_edge == Edge_TopLeft) {
                QPoint dp = QPoint(QCursor::pos() - m_mousePos);
                QSize d = QSize(0,0)-QSize(dp.x(), dp.y());
                QSize _size = m_originalSize + d;
                _size.setWidth((_size.width() > 350)?_size.width():350);
                _size.setHeight((_size.height() > 500)?_size.height():500);
                updateSizePos(_size);
            }
        }
        break;
        case Side_Right: {
            if(m_edge == Edge_Top) {
                int dy = -(QCursor::pos().y() - m_mousePos.y());
                int height = m_originalSize.height() + dy;
                height = (height > 500)?height:500;
                updateSizePos(QSize(width(), height));
            } else if(m_edge == Edge_Left) {
                int dx = -(QCursor::pos().x() - m_mousePos.x());
                int width = m_originalSize.width() + dx;
                width = (width > 350)?width:350;
                updateSizePos(QSize(width, height()));
            } else if(m_edge == Edge_TopLeft) {
                QPoint dp = QPoint(QCursor::pos() - m_mousePos);
                QSize d = QSize(0,0)-QSize(dp.x(), dp.y());
                QSize _size = m_originalSize + d;
                _size.setWidth((_size.width() > 350)?_size.width():350);
                _size.setHeight((_size.height() > 500)?_size.height():500);
                updateSizePos(_size);
            }
        }
        break;
        case Side_Top: {
            if(m_edge == Edge_Bottom) {
                int dy = (QCursor::pos().y() - m_mousePos.y());
                int height = m_originalSize.height() + dy;
                height = (height > 500)?height:500;
                updateSizePos(QSize(width(), height));
            } else if(m_edge == Edge_Left) {
                int dx = -(QCursor::pos().x() - m_mousePos.x());
                int width = m_originalSize.width() + dx;
                width = (width > 350)?width:350;
                updateSizePos(QSize(width, height()));
            } else if(m_edge == Edge_BottomLeft) {
                QPoint dp = QPoint(QCursor::pos() - m_mousePos);
                dp.setX(-dp.x());
                QSize d = QSize(dp.x(), dp.y());
                QSize _size = m_originalSize + d;
                _size.setWidth((_size.width() > 350)?_size.width():350);
                _size.setHeight((_size.height() > 500)?_size.height():500);
                updateSizePos(_size);
            }
        }
        break;
        case Side_Left: {
            if(m_edge == Edge_Top) {
                int dy = -(QCursor::pos().y() - m_mousePos.y());
                int height = m_originalSize.height() + dy;
                height = (height > 500)?height:500;
                updateSizePos(QSize(width(), height));
            } else if(m_edge == Edge_Right) {
                int dx = -(QCursor::pos().x() - m_mousePos.x());
                int width = m_originalSize.width() + dx;
                width = (width > 350)?width:350;
                updateSizePos(QSize(width, height()));
            } else if(m_edge == Edge_TopRight) {
                QPoint dp = QPoint(QCursor::pos() - m_mousePos);
                dp.setX(-dp.x());
                QSize d = QSize(0,0)-QSize(dp.x(), dp.y());
                QSize _size = m_originalSize + d;
                _size.setWidth((_size.width() > 350)?_size.width():350);
                _size.setHeight((_size.height() > 500)?_size.height():500);
                updateSizePos(_size);
            }
        }
        break;
        default:
        break;
        }
    }
}

void PopupWindow::mousePressed(const QPoint point)
{
    if(getEdgeFromMousePos(point) != 0) {
        m_mousePressed = true;
        m_mousePos = QCursor::pos();
        m_originalSize = size();
        m_originalPos = pos();
    }
}

void PopupWindow::drawProgress()
{
    QSize pixSize = m_trayIcon.availableSizes().at(0);
    QPixmap pix = m_trayIcon.pixmap(pixSize);

    if(m_drawProgress) {
        QPainter painter(&pix);
        painter.setBrush(QColor(255, 255, 255));
        painter.setPen(QPen(QColor(255, 255, 255, 0), 2));
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        int w = (float)((float)m_currentProgress / (float)m_maxProgress) * (pixSize.width() - 6);
        int h = 8;

        painter.drawRoundedRect(QRect(QPoint(0, (pixSize.height() / 2) - (h / 2)), QSize(pixSize.width(), h)), 4, 4);

        h = 4;

        painter.setPen(QPen(QColor(255, 255, 255, 0), 1.5));
        painter.drawRoundedRect(QRect(QPoint(3, (pixSize.height() / 2) - (h / 2)), QSize(w, h)), 4, 4);
    }

    mw_tray->setIcon(pix);
}

QWidget *PopupWindow::centralWidget() const
{
    return mw_centralWidget;
}

void PopupWindow::setCentralWidget(QWidget *widget)
{
    mw_centralWidget = widget;
}

void PopupWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setBrush(QColor("#313D4A"));
    painter.setPen(QPen(QColor("#19232D"), 1.2));

    QRect rect(0, 0, width(), height());

    painter.drawRoundedRect(rect, 5.5, 5.5);

    if(mw_centralWidget) {
        mw_centralWidget->setGeometry(0, 0, width(), height());
        updateMask();
    }
}

bool PopupWindow::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if(event->type() == QEvent::MouseMove) {
        mouseMove(QCursor::pos());
    } else if(event->type() == QEvent::MouseButtonPress) {
        mousePressed(QCursor::pos());
    } else if(event->type() == QEvent::MouseButtonRelease) {
        m_mousePressed = false;
    }

    return false;
}

void PopupWindow::updateMask()
{
    QBitmap mask(width(), height());
    mask.clear();

    QPainter painter(&mask);

    QBrush bg(Qt::color1);
    painter.setBrush(bg);

    painter.drawRoundedRect(1, 1, mw_centralWidget->width() - 3, mw_centralWidget->height() - 3, 5, 5);

    mw_centralWidget->setMask(mask);
}
