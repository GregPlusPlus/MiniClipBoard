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

#ifndef NAVBAR_H
#define NAVBAR_H

#include <QApplication>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>

#include <QMovie>

#include <QUrl>

#include <QDebug>

#include "../CoreUI/Widgets/flatactionbutton.h"
#include "urlbar.h"
#include "popup.h"

class NavBar : public QWidget
{
    Q_OBJECT

public:
    enum Controls {
        Controls_All        = 0xff,
        Controls_NoControls = 0,
        Controls_Close      = 1,
        Controls_Refresh    = 2,
        Controls_Navigate   = 4,
        Controls_Url        = 8,
        Controls_External   = 16
    };

public:
    explicit NavBar(QWidget *parent = nullptr);
    ~NavBar();

    int controls() const;
    void setControls(int flags);

signals:
    void backward();
    void forward();
    void refresh();
    void urlEntered(const QUrl &url);
    void openExternal();
    void closeBrowser();

public slots:
    void setUrl(const QUrl &url);
    void setIcon(const QIcon &icon);
    void setTitle(const QString &title);
    void setLoading();
    void enableBack(bool enabled);
    void enableForward(bool enabled);
    void showDetails();

private:
    QHBoxLayout         *m_layout;
    FlatActionButton    *mw_close;
    QPushButton         *mw_backward;
    QPushButton         *mw_refresh;
    QPushButton         *mw_forward;
    URLBar              *mw_url;
    FlatActionButton    *mw_external;
    Popup               *mw_popup;

    QMovie *m_loadingAnimation;

    int m_controls;
};

#endif // NAVBAR_H
