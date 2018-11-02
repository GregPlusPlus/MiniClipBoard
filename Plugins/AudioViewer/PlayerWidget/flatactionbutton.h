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

#ifndef FLATACTIONBUTTON_H
#define FLATACTIONBUTTON_H

#include <QPushButton>

class FlatActionButton : public QPushButton
{
    Q_OBJECT

public:
    explicit FlatActionButton(const QIcon &icon, const QString &tootltip, QWidget *parent = nullptr);
};

#endif // FLATACTIONBUTTON_H
