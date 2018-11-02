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

#include <QTime>
#include <QDateTime>

#include <QList>

#include "../../Utils/utils.h"
#include "clipboarddata.h"

namespace Core {

enum ReinterpretData {
    ReinterpretData_None = 0,
    ReinterpretData_TextToUrl = 1,
    ReinterpretData_TextToColor = 2
};

enum DateTimeFilterType {
    DateTimeFilterType_None,
    DateTimeFilterType_Before,
    DateTimeFilterType_After,
    DateTimeFilterType_Between
};

enum DataOrigin {
    DataOrigin_Clipboard,
    DataOrigin_DragDrop
};

enum FileType {
    FileType_Image,
    FileType_Html,
    FileType_Text,
    FileType_FromPlugin,
    FileType_Unknown
};

struct Bookmark
{
    QDateTime       dt;
    QString         userName;
    QUuid           uuid;
    ClipboardData   data;
};

typedef QList<Core::Bookmark> Bookmarks;

struct Settings {
    QString lang;
    QTime   clipboardTimeOut;
    int     reinterpret;
    bool    notify;
    bool    showThumbnails;
    bool    firstStart;
    bool    windowAlwaysOnTop;
    bool    tooltipCopy;
    bool    autoCheckUpdates;
    bool    timeOutEnabled;
    bool    excludeProcesses;
};

struct DateTimeFilter
{
    DateTimeFilter(DateTimeFilterType _type = DateTimeFilterType_None, QDateTime _dateTime_1 = QDateTime(), QDateTime _dateTime_2 = QDateTime()) :
        type(_type), dateTime_1(_dateTime_1), dateTime_2(_dateTime_2){}

    DateTimeFilterType  type;
    QDateTime           dateTime_1;
    QDateTime           dateTime_2;
};

struct Filter {
    Filter(bool _caseSensitive = true, MimeType _type = MimeType_None, QString _text = QString(), DateTimeFilter _dateTimeFilter = DateTimeFilter()) :
        caseSensitive(_caseSensitive), type(_type), text(_text), dateTimeFilter(_dateTimeFilter) {}

    bool            caseSensitive;
    MimeType        type;
    QString         text;
    DateTimeFilter  dateTimeFilter;
};
}

#endif // CORETYPES_H
