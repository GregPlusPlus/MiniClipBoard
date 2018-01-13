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

#ifndef CORETYPES_H
#define CORETYPES_H

#include <QMimeData>

#include <QColor>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QUrl>

#include <QUuid>

#include <QByteArray>
#include <QDataStream>

#include <QDateTime>

#include <QList>

namespace Core {
typedef QList<QUrl> Urls;

enum MimeType {
    MimeType_Invalid,
    MimeType_None,
    MimeType_Color,
    MimeType_Html,
    MimeType_Text,
    MimeType_Image,
    MimeType_URLs
};

enum ReinterpretData {
    ReinterpretData_None = 0b0,
    ReinterpretData_TextToUrl = 0b1,
    ReinterpretData_TextToColor = 0b10
};

enum DateTimeFilterType {
    DateTimeFilterType_None,
    DateTimeFilterType_Before,
    DateTimeFilterType_After,
    DateTimeFilterType_Between
};

struct ClipboardData {
    ClipboardData() {type = MimeType_None;}

    bool operator==(const ClipboardData& a) const {
        return (a.type == type &&
                a.color == color &&
                a.text == text &&
                a.Html == Html &&
                a.image.toImage() == image.toImage() &&
                a.URLs == URLs);
    }

    MimeType type;
    QColor color;
    QString text;
    QString Html;
    QPixmap image;
    Urls URLs;
};

struct Bookmark
{
    QDateTime dt;
    QString userName;
    QUuid uuid;
    ClipboardData data;
};

struct Settings {
    QString lang;
    int reinterpret;
    bool notify;
    bool showThumbnails;
    bool firstStart;
    bool windowAlwaysOnTop;
};

struct DateTimeFilter
{
    DateTimeFilter(DateTimeFilterType _type = DateTimeFilterType_None, QDateTime _dateTime_1 = QDateTime(), QDateTime _dateTime_2 = QDateTime()) :
        type(_type), dateTime_1(_dateTime_1), dateTime_2(_dateTime_2){}
    DateTimeFilterType type;
    QDateTime dateTime_1;
    QDateTime dateTime_2;
};

struct Filter {
    Filter(MimeType _type = MimeType_None, QString _text = QString(), DateTimeFilter _dateTimeFilter = DateTimeFilter()) : type(_type), text(_text), dateTimeFilter(_dateTimeFilter) {}
    MimeType type;
    QString text;
    DateTimeFilter dateTimeFilter;
};
}

#endif // CORETYPES_H
