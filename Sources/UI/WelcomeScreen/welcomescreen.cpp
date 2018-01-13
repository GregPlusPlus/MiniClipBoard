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

#include "welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) : QWidget(parent)
{
    m_layout = new QGridLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    mw_text = new QTextBrowser(this);
    mw_text->setHtml(Utils::welcomeHTML());
    mw_text->setStyleSheet("QTextBrowser {"
                           "padding-left: 10px;"
                           "background-color: #212930;"
                           "color: #D1DBE6;"
                           "border: none;"
                           "selection-background-color: #627182;"
                           "min-height: 20px;"
                           "border-top-width: 4px;"
                           "border-top-color: #17181A;"
                           "border-top-style: solid;"
                           "font-size: 15px;"
                           "}");
    mw_text->setReadOnly(true);
    mw_text->setOpenExternalLinks(true);

    mw_skip = new QPushButton(QIcon(":/icons/skip"), tr("Skip"), this);
    mw_skip->setLayoutDirection(Qt::RightToLeft);
    mw_skip->setFlat(true);
    mw_skip->setCursor(Qt::PointingHandCursor);
    mw_skip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mw_skip->setStyleSheet("QPushButton{background-color: none; border: none; padding: 10px;}"
                           "QPushButton:hover{background-color: rgba(255, 255, 255, .1);}"
                           "QPushButton:pressed{background-color: rgba(0, 0, 0, .1);}");
    connect(mw_skip, &QPushButton::clicked, [=]() {
        fadeOut();
    });

    m_layout->addWidget(mw_text, 0, 0, 10, 5);
    m_layout->addWidget(mw_skip, 10, 4, 1, 1, Qt::AlignRight);

    setLayout(m_layout);
}

void WelcomeScreen::fadeOut()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(300);
    animation->setStartValue(QPoint(0, y()));
    animation->setEndValue(QPoint(width(), y()));
    animation->setEasingCurve(QEasingCurve::InBack);
    connect(animation, &QPropertyAnimation::finished, [=](){
        deleteLater();
    });
    animation->start();
}

void WelcomeScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setBrush(QColor("#313D4A"));

    painter.drawRect(0, 0, width(), height());
}
