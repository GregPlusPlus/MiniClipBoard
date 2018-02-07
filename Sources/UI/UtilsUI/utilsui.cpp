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

#include "utilsui.h"

QFrame *UtilsUI::createSeparator(QFrame::Shape shape)
{
    QFrame* line = new QFrame();
    line->setFrameShape(shape);
    line->setFrameShadow(QFrame::Raised);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    line->setFixedHeight(2);
    return line;
}

void UtilsUI::applyStyleSheet(const QString &path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);

    QString StyleSheet = QLatin1String(file.readAll());

    file.close();

    qApp->setStyleSheet(StyleSheet);
}

void UtilsUI::applyStyleSheet(QWidget *widget, const QString &path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);

    QString StyleSheet = QLatin1String(file.readAll());

    file.close();

    widget->setStyleSheet(StyleSheet);
}

QWidgetAction *UtilsUI::createWidgetActionSeparator(const QString &text, QWidget *parent)
{
    QLabel *label = new QLabel(text, parent);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background: none; font-size: 15px;");

    QWidgetAction* a = new QWidgetAction(parent);
    a->setDefaultWidget(label);

    return a;
}
