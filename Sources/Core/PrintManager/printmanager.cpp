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

#include "printmanager.h"

PrintManager::PrintManager(Core::ClipboardData *data, QObject *parent) : QObject(parent), m_p_data(data)
{
}

void PrintManager::setData(Core::ClipboardData *p_data)
{
    m_p_data = p_data;
}

void PrintManager::print(QWidget *dialogParent)
{
    if(!m_p_data) {
        QMessageBox::warning(dialogParent, tr("No data"), tr("There is no data to print!"));

        return;
    }

    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *dialog = new QPrintDialog(&printer, dialogParent);
    dialog->setWindowTitle(tr("Print Document"));

    if (dialog->exec() != QDialog::Accepted) {
        return;
    }

    generatePrint(printer);
}

void PrintManager::generatePrint(QPrinter &printer)
{
    switch (m_p_data->type) {
    case Core::MimeType_Text :
        printText(printer);
        break;
    case Core::MimeType_Html :
        printHtml(printer);
        break;
    case Core::MimeType_Image :
        printImage(printer);
        break;
    case Core::MimeType_URLs :
        printUrls(printer);
        break;
    case Core::MimeType_Color :
        printColor(printer);
        break;
    case Core::MimeType_Invalid :
        printer.abort();
        break;
    case Core::MimeType_None:
        printer.abort();
        break;
    }
}

void PrintManager::printText(QPrinter &printer)
{
    QTextDocument td;
    td.setPlainText(m_p_data->text);
    td.print(&printer);
}

void PrintManager::printHtml(QPrinter &printer)
{
    printRawHtml(printer, m_p_data->Html, m_defaultFontSize);
}

void PrintManager::printImage(QPrinter &printer)
{
    QPainter painter;

    painter.begin(&printer);

    painter.drawPixmap(printer.pageRect().x(), printer.pageRect().y(), m_p_data->image.scaled(printer.pageRect().size(), Qt::KeepAspectRatio));

    painter.end();
}

void PrintManager::printUrls(QPrinter &printer)
{
    QString html("<h1>%1 Urls</h1>\n<hr>\n%2");
    html = html.arg(m_p_data->URLs.count()).arg("<ul>\n%1</ul>");

    for(QUrl url : m_p_data->URLs) {
        html = html.arg(QString("\t<li><a href=\"%1\">%1</a></li>\n%2").arg(url.toString())).arg("%1");
    }

    html = html.arg("");

    printRawHtml(printer, html, m_defaultFontSize - 2);
}

void PrintManager::printColor(QPrinter &printer)
{
    printer.setPageMargins(QMargins(10, 10, 10, 10), QPageLayout::Millimeter);

    QPainter painter;

    painter.begin(&printer);

    painter.setPen(QPen(Qt::black, 5));
    painter.setBrush(Qt::NoBrush);

    int boxH = 150;
    int top  = 200;
    int left = 70;
    int boxMargin = 20;
    int innerSpacing = 10;

    painter.drawText(QPoint(printer.margins().left, printer.margins().top + top + boxH / 2),                            "R");
    painter.drawText(QPoint(printer.margins().left, printer.margins().top + top + boxH + boxMargin + boxH / 2),         "G");
    painter.drawText(QPoint(printer.margins().left, printer.margins().top + top + boxH * 2 + boxMargin * 2 + boxH / 2), "B");
    painter.drawText(QPoint(printer.margins().left, printer.margins().top + top + boxH * 3 + boxMargin * 3 + boxH / 2), "A");

    painter.drawRect(printer.margins().left + left, printer.margins().top + top,                                printer.width() / 2, boxH);
    painter.drawRect(printer.margins().left + left, printer.margins().top + top + boxH + boxMargin,             printer.width() / 2, boxH);
    painter.drawRect(printer.margins().left + left, printer.margins().top + top + boxH * 2 + boxMargin * 2,     printer.width() / 2, boxH);
    painter.drawRect(printer.margins().left + left, printer.margins().top + top + boxH * 3 + boxMargin * 3,     printer.width() / 2, boxH);

    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(m_p_data->color));

    painter.drawRect(printer.margins().left + left, printer.margins().top + top / 3, printer.width() - printer.margins().left - printer.margins().right - left, top / 3);

    painter.setPen(Qt::NoPen);

    int RW = (float)((printer.width() / 2) - (innerSpacing * 2)) * (float)((float)m_p_data->color.red()    / 255.f);
    int GW = (float)((printer.width() / 2) - (innerSpacing * 2)) * (float)((float)m_p_data->color.green()  / 255.f);
    int BW = (float)((printer.width() / 2) - (innerSpacing * 2)) * (float)((float)m_p_data->color.blue()   / 255.f);
    int AW = (float)((printer.width() / 2) - (innerSpacing * 2)) * (float)((float)m_p_data->color.alpha()  / 255.f);

    painter.setBrush(Qt::red);
    painter.drawRect(printer.margins().left + left + innerSpacing, printer.margins().top + top + innerSpacing,                            RW, boxH - innerSpacing * 2);
    painter.setBrush(Qt::green);
    painter.drawRect(printer.margins().left + left + innerSpacing, printer.margins().top + top + innerSpacing + boxH + boxMargin,         GW, boxH - innerSpacing * 2);
    painter.setBrush(Qt::blue);
    painter.drawRect(printer.margins().left + left + innerSpacing, printer.margins().top + top + innerSpacing + boxH * 2 + boxMargin * 2, BW, boxH - innerSpacing * 2);
    painter.setBrush(Qt::gray);
    painter.drawRect(printer.margins().left + left + innerSpacing, printer.margins().top + top + innerSpacing + boxH * 3 + boxMargin * 3, AW, boxH - innerSpacing * 2);

    painter.setPen(QPen(Qt::black, 5));

    painter.drawText(QPoint(printer.margins().left + left * 2 + printer.width() / 2, printer.margins().top + top + boxH / 2), QString::number(m_p_data->color.red()));
    painter.drawText(QPoint(printer.margins().left + left * 2 + printer.width() / 2, printer.margins().top + top + boxH + boxMargin + boxH / 2), QString::number(m_p_data->color.green()));
    painter.drawText(QPoint(printer.margins().left + left * 2 + printer.width() / 2, printer.margins().top + top + boxH * 2 + boxMargin * 2 + boxH / 2), QString::number(m_p_data->color.blue()));
    painter.drawText(QPoint(printer.margins().left + left * 2 + printer.width() / 2, printer.margins().top + top + boxH * 3 + boxMargin * 3 + boxH / 2), QString::number(m_p_data->color.alpha()));

    painter.drawLine(QPoint(printer.margins().left + left * 2 + printer.width() / 2 + 200, printer.margins().top + top), QPoint(printer.margins().left + left * 2 + printer.width() / 2 + 200, printer.margins().top + top + boxH * 4 + boxMargin * 3));

    painter.drawText(QPoint(printer.margins().left + left * 2 + printer.width() / 2 + 200 + left, printer.margins().top + top + boxH / 2), tr("Hex RGB : %1").arg(m_p_data->color.name(QColor::HexRgb).toUpper()));

    painter.end();
}

void PrintManager::printRawHtml(QPrinter &printer, const QString &html, int fontSize)
{
    QTextDocument td;
    td.setHtml(html);

    QTextBlock block = td.findBlock(0);

    while(block.isValid()) {
        QTextCursor cursor(block);

        for(QTextBlock::iterator it = cursor.block().begin(); !(it.atEnd()); it++)
        {
            QTextCharFormat charFormat = it.fragment().charFormat();

            QFont font(charFormat.font());

            if(font.pointSize() < fontSize) {
                font.setPointSize(fontSize);
                charFormat.setFont(font);
            }

            QTextCursor tempCursor = cursor;
            tempCursor.setPosition(it.fragment().position());
            tempCursor.setPosition(it.fragment().position() + it.fragment().length(), QTextCursor::KeepAnchor);
            tempCursor.setCharFormat(charFormat);
        }

        block = block.next();
    }

    td.print(&printer);
}
