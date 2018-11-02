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

#include "lineedit.h"

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
    setFixedHeight(40);
    clearFocus();
    resetColor();
}

void LineEdit::setBorderColor(const QColor &color)
{
    setStyleSheet(QString("QLineEdit {"
                          "border: 2px solid %1;"
                          "border-radius: 4px;"
                          "background: #202634;"
                          "padding: 0 8px;"
                          "padding-right: 25px;"
                          "font: bold 14px;"
                          "}"
                          "QLineEdit:focus {"
                          "border: 2px solid %2;"
                          "}").arg(color.name(QColor::HexRgb)).arg(color.name(QColor::HexRgb)));
}

void LineEdit::resetColor()
{
    setStyleSheet("QLineEdit {"
                  "border: 2px solid #5A6C91;"
                  "border-radius: 4px;"
                  "background: #202634;"
                  "padding: 0 8px;"
                  "padding-right: 25px;"
                  "font: bold 14px;"
                  "}"
                  "QLineEdit:focus {"
                  "border: 2px solid #568AF2;"
                  "}");
}
