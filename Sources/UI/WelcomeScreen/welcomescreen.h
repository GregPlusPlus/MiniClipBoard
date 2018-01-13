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

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>

#include <QGridLayout>

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "../../Utils/utils.h"

class WelcomeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeScreen(QWidget *parent = nullptr);

signals:
    void deleted();

public slots:
    void fadeOut();

private :
    QGridLayout *m_layout;

    QTextBrowser *mw_text;
    QPushButton *mw_skip;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WELCOMESCREEN_H
