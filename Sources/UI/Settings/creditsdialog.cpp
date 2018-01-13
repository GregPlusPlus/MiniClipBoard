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

#include "creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Credits"));
    setWindowIcon(QIcon(":/icons/ic_info_white_18dp"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_layout = new QGridLayout;
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    mw_text = new QLabel(this);
    mw_text->setTextFormat(Qt::RichText);
    mw_text->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mw_text->setOpenExternalLinks(true);

    QFont font = mw_text->font();
    font.setPointSize(9);
    mw_text->setFont(font);

    mw_text->setText(tr("<style>" \
                        "a{color: #3399ff;}" \
                        "</style>" \
                        "<p>" \
                        "Some icons comes from <a href=\"https://material.io/icons/\">https://material.io/icons/</a><br>" \
                        "and are available under the Apache License Version 2.0.<hr>" \
                        "All trademarks are property of their respective owners." \
                        "</p>"));

    m_layout->addWidget(mw_text, 0, 0, 1, 1);

    setLayout(m_layout);
}
