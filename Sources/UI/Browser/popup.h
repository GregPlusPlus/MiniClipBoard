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

#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QLabel>

#include <QGridLayout>

#include "../CoreUI/Widgets/infospopup.h"

class Popup : public InfosPopup
{
    Q_OBJECT

public:
    explicit Popup();

signals:

public slots:
    void setTitle(const QString &title);
    void setHttpsUse(bool use);

private:
    QGridLayout *m_layout;

    QLabel      *mw_title;
    QLabel      *mw_security;
};

#endif // POPUP_H
