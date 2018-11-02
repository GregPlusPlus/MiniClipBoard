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

#ifndef UNDERLYINGWINDOW_H
#define UNDERLYINGWINDOW_H

#include <QList>

#include "../PopupWindow/popupwindow.h"
#include "titlebar.h"

class UnderlyingWindow : public PopupWindow
{
    Q_OBJECT

public:
    UnderlyingWindow(QWidget *parent = nullptr);
    void setCentralWidget(QWidget *widget);

    TitleBar *titleBar() const;

    void addView(QWidget *view);
    void removeView(QWidget *view);
    void replaceView(QWidget *newView, QWidget *oldView);

    void fitContent();

private:
    QVBoxLayout *m_layout;

    QWidget     *mw_centralWidget;
    TitleBar    *mw_titleBar;

    QList<QWidget*> m_views;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // UNDERLYINGWINDOW_H
