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

#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QObject>

#include <QMessageBox>

#include <QTextDocument>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextCursor>

#include <QPainter>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

#include <QDebug>

#include "../Core/core.h"

class PrintManager : public QObject
{
    Q_OBJECT

public:
    explicit PrintManager(Core::ClipboardData *data = nullptr, QObject *parent = nullptr);

    void setData(Core::ClipboardData *p_data);

signals:

public slots:
    void print(QWidget *dialogParent = nullptr);
    void generatePrint(QPrinter &printer);

private:
    Core::ClipboardData *m_p_data;

    int m_defaultFontSize = 10;

private:
    void printText  (QPrinter &printer);
    void printHtml  (QPrinter &printer);
    void printImage (QPrinter &printer);
    void printUrls  (QPrinter &printer);
    void printColor (QPrinter &printer);

    void printRawHtml(QPrinter &printer, const QString &html, int fontSize);
};

#endif // PRINTMANAGER_H
