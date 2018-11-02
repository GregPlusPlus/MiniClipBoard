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

#include "underlyingwindow.h"

UnderlyingWindow::UnderlyingWindow(QWidget *parent) : PopupWindow(parent)
{
    mw_centralWidget = new QWidget(this);

    m_layout = new QVBoxLayout;
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    mw_centralWidget->setLayout(m_layout);

    mw_titleBar = new TitleBar(this);
    connect(mw_titleBar, &TitleBar::mouseDP, [=](const QPoint &dP) {
        move(pos() + dP);
    });

    m_layout->addWidget(mw_titleBar);
    PopupWindow::setCentralWidget(mw_centralWidget);

    connect(this, &UnderlyingWindow::anchored, [=](bool anchored) {
        mw_titleBar->setVisible(!anchored);
        titleBar()->setWindowAnchored(anchored);
        fitContent();
    });
}

void UnderlyingWindow::setCentralWidget(QWidget *widget)
{
    if(m_layout->itemAt(1)) {
        m_layout->removeWidget(m_layout->itemAt(1)->widget());
    }

    m_layout->addWidget(widget);
}

TitleBar *UnderlyingWindow::titleBar() const
{
    return mw_titleBar;
}

void UnderlyingWindow::addView(QWidget *view)
{
    m_views.append(view);

    fitContent();
}

void UnderlyingWindow::removeView(QWidget *view)
{
    if(m_views.contains(view)) {
        m_views.removeAll(view);
    }

    fitContent();
}

void UnderlyingWindow::replaceView(QWidget *newView, QWidget *oldView)
{
    removeView(oldView);
    addView(newView);

    fitContent();
}

void UnderlyingWindow::fitContent()
{
    for(QWidget *view : m_views) {
        if(!getAnchored()) {
            if(view) {
                view->setFixedSize(size() - QSize(0, titleBar()->height()));
                view->move(QPoint(0, titleBar()->height()));
            }
        } else {
            if(view) {
                view->move(QPoint(0, 0));
                view->setFixedSize(size());
            }
        }
    }
}

void UnderlyingWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    fitContent();
}
