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

#include "searchbox.h"

SearchBox::SearchBox(QWidget *parent) : QWidget(parent)
{
    m_filterType = Core::MimeType_None;

    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumHeight(70);
    setAcceptDrops(true);

    mw_search = new QLineEdit(this);
    mw_search->setPlaceholderText(tr("Type here to search..."));
    mw_search->setFixedHeight(35);
    mw_search->clearFocus();
    mw_search->setStyleSheet("QLineEdit {"
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

    mw_clearButton = new QPushButton(QIcon(":/icons/ic_clear_white_18dp"), QString(), this);
    mw_clearButton->setFlat(true);
    mw_clearButton->setCursor(Qt::PointingHandCursor);
    mw_clearButton->setFixedSize(18, 18);
    mw_clearButton->setVisible(false);

    mw_optionsButton = new QPushButton(QIcon(":/icons/ic_more_vert_white_18dp"), QString(), this);
    mw_optionsButton->setFlat(true);
    mw_optionsButton->setCursor(Qt::PointingHandCursor);
    mw_optionsButton->setFixedSize(18, 30);
    mw_optionsButton->setStyleSheet("QPushButton::menu-indicator {"
                                    "image: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "padding: 0px;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background: #3E4D5C;"
                                    "border-top-left-radius: 3px;"
                                    "border-top-right-radius: 3px;"
                                    "}");

    buildMenu();

    connect(mw_search, &QLineEdit::textChanged, [=]() {
        filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
    });

    connect(mw_search, &QLineEdit::textChanged, [=](const QString &text) {
        if(text.isEmpty()) {
            mw_clearButton->setVisible(false);
        } else {
            mw_clearButton->setVisible(true);
        }
    });

    connect(mw_clearButton, &QPushButton::clicked, [=]() {
        mw_search->clear();
        mw_search->setFocus();
    });
}

Core::Filter SearchBox::getFilter()
{
    return Core::Filter(m_filterType, mw_search->text());
}

void SearchBox::buildMenu()
{
    mw_menu = new QMenu(tr("Search options"), this);
    mw_optionsButton->setMenu(mw_menu);

    mw_menu->addAction(UtilsUI::createWidgetActionSeparator(tr("<b> ── Filters ── </b>"), this));

    mw_group = new QActionGroup(this);
    mw_group->setExclusive(true);

    m_filterAll = mw_menu->addAction(tr("&All"));
    m_filterAll->setCheckable(true);
    mw_group->addAction(m_filterAll);

    m_filterImage = mw_menu->addAction(tr("&Image"));
    m_filterImage->setCheckable(true);
    mw_group->addAction(m_filterImage);

    m_filterColor = mw_menu->addAction(tr("&Color"));
    m_filterColor->setCheckable(true);
    mw_group->addAction(m_filterColor);

    m_filterHtml = mw_menu->addAction(tr("&HTML"));
    m_filterHtml->setCheckable(true);
    mw_group->addAction(m_filterHtml);

    m_filterText = mw_menu->addAction(tr("&Text"));
    m_filterText->setCheckable(true);
    mw_group->addAction(m_filterText);

    m_filterURL = mw_menu->addAction(tr("&URL"));
    m_filterURL->setCheckable(true);
    mw_group->addAction(m_filterURL);

    m_filterAll->setChecked(true);

    connect(m_filterAll, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_None;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    connect(m_filterImage, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_Image;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    connect(m_filterColor, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_Color;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    connect(m_filterHtml, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_Html;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    connect(m_filterText, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_Text;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    connect(m_filterURL, &QAction::triggered, [=](bool checked) {
        if(checked){
            m_filterType = Core::MimeType_URLs;

            filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
        }
    });

    mw_menu->addAction(UtilsUI::createWidgetActionSeparator(tr("<b> ─ Date & Time ─ </b>"), this));

    mw_dateTimePicker = new DateTimePicker(this);
    connect(mw_dateTimePicker, &DateTimePicker::dateTimeFilterChanged, [=]() {
        filterChanged(Core::Filter(m_filterType, mw_search->text(), mw_dateTimePicker->getDateTimeFilter()));
    });

    QWidgetAction *a = new QWidgetAction(this);
    a->setDefaultWidget(mw_dateTimePicker);

    mw_menu->addAction(a);
}

void SearchBox::setText(const QString &text)
{
    mw_search->setText(text);
}

void SearchBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setBrush(QColor("#282C34"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width(), height());

    painter.setPen(QColor("#19232D"));
    painter.drawLine(0, height() - 1, width(), height() - 1);

    mw_search->setFixedSize(width() - mw_optionsButton->width() - 25, height() / 2);

    mw_search->move((width() / 2 - (mw_search->width()) / 2) - 8,
                    height() / 2 - mw_search->height() / 2);

    mw_clearButton->move(mw_search->x() + mw_search->width() - 25,
                         mw_search->y() + mw_search->height() / 2 - 8);

    mw_optionsButton->move(mw_search->x() + mw_search->width() + 5,
                           height() / 2 - mw_optionsButton->height() / 2);
}
