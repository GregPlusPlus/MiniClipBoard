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

#ifndef ERRORWIDGET_H
#define ERRORWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>

class ErrorWidget : public QWidget
{
    Q_OBJECT

public:
    enum ErrType {
        ErrType_NotFound,
        ErrType_Unknown,
        ErrType_BadPlugin
    };

public:
    ErrorWidget(ErrType type, const QString fileName, QWidget *parent = nullptr);

private:
    QVBoxLayout *m_layout;
    QLabel *mw_icon;
    QLabel *mw_text;
};

#endif // ERRORWIDGET_H
