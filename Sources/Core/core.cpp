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

#include "core.h"

Core::ClipboardData Core::QMimeToClipboardData(const QMimeData *mime)
{
    ClipboardData data;

    if(mime->hasImage()) {
        data.image = qvariant_cast<QPixmap>(mime->imageData());
        data.type = MimeType_Image;
    } else if(mime->hasColor()) {
        data.color = qvariant_cast<QColor>(mime->colorData());
        data.type = MimeType_Color;
    } else if(mime->hasUrls()) {
        data.URLs = mime->urls();
        data.type = MimeType_URLs;
    } else if(mime->hasHtml()) {
        data.Html = mime->html();
        data.type = MimeType_Html;
    } else if(mime->hasText()) {
        data.text = mime->text().toUtf8();
        data.type = MimeType_Text;
    } else {
        return ClipboardData();
    }

    return data;
}

void Core::clearClipboardData(ClipboardData &data)
{
    data.type = MimeType_None;
    data.color = QColor();
    data.image = QPixmap();
    data.URLs = QList<QUrl>();
    data.text = QString();
    data.Html = QString();
}

void Core::reinterpretData(ClipboardData &data, MimeType type)
{
    if(data.type == MimeType_Text && type == MimeType_URLs) {
        data.type = MimeType_URLs;
        data.URLs = Urls(QUrl::fromStringList(QStringList(data.text)));
        data.text.clear();
    } else if(data.type == MimeType_URLs && type == MimeType_Text) {

    } else if(data.type == MimeType_Text && type == MimeType_Color) {
        data.type = MimeType_Color;
        data.color = QColor(data.text);
        data.text.clear();
    }
}

bool Core::isTextAnUrl(const QString &text)
{
    if(text.startsWith("http://") ||
            text.startsWith("https://") ||
            text.startsWith("file:///") ||
            text.startsWith("www.")) {
        return true;
    }

    return false;
}

void Core::autoReinterpretData(ClipboardData &data, const int &reinterpretFlags)
{
    if((reinterpretFlags & ReinterpretData_TextToUrl) != 0) {
        if(data.type == MimeType_Text && isTextAnUrl(data.text)) {
            reinterpretData(data, MimeType_URLs);
        }
    }

    if((reinterpretFlags & ReinterpretData_TextToColor) != 0) {
        if(data.type == MimeType_Text &&
                data.text.length() == 7 &&
                data.text.startsWith('#')) {
            reinterpretData(data, MimeType_Color);
        }
    }
}

QByteArray Core::clipboardDataToByteArray(const ClipboardData &data)
{
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_9);

    stream << uint8_t(data.type);

    switch (data.type) {
    case MimeType_Image:
        stream << data.image;
        break;
    case MimeType_Color:
        stream << data.color;
        break;
    case MimeType_Html:
        stream << QString(data.Html);
        break;
    case MimeType_Text:
        stream << QString(data.text.toUtf8());
        break;
    case MimeType_URLs:
        stream << data.URLs;
        break;
    default:
        return QByteArray();
        break;
    }

    stream << QDateTime::currentDateTime();

    stream << Utils::getUserName();

    return bytes;
}

Core::ClipboardData Core::byteArrayToClipboardData(const QByteArray &array, QDateTime &dateTime, QString &userName)
{
    ClipboardData data;

    if(array.isEmpty()) {
        return data;
    }

    QByteArray bytes(array);

    QDataStream stream(&bytes, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_9);

    uint8_t flag = 0;
    stream >> flag;

    data.type = static_cast<MimeType>(flag);

    switch (data.type) {
    case MimeType_Image:
        stream >> data.image;
        if(data.image.isNull()) {
            return ClipboardData();
        }
        break;
    case MimeType_Color:
        stream >> data.color;
        if(!data.color.isValid()) {
            return ClipboardData();
        }
        break;
    case MimeType_Html:
        stream >> data.Html;
        data.Html = QString(data.Html.toUtf8());
        if(data.Html.isNull()) {
            return ClipboardData();
        }
        break;
    case MimeType_Text:
        stream >> data.text;
        data.text = QString(data.text.toUtf8());
        if(data.text.isNull()) {
            return ClipboardData();
        }
        break;
    case MimeType_URLs:
        stream >> data.URLs;
        if(data.URLs.isEmpty()) {
            return ClipboardData();
        }
        break;
    case MimeType_None:
        return ClipboardData();
    default:
        ClipboardData _data;
        _data.type = MimeType_Invalid;
        return _data;
        break;
    }

    stream >> dateTime;

    stream >> userName;

    return data;
}

QList<Core::Bookmark> Core::reorderBookmarks(const QList<Core::Bookmark> &bookmarks)
{
    QList<Core::Bookmark> bms1 = bookmarks;
    QList<Core::Bookmark> bms2;

    while(!bms1.isEmpty()) {
        Core::Bookmark bm = bms1.first();
        int index = 0;

        for(int i = 0; i < bms1.count(); i++) {
            if(bms1.at(i).dt <= bm.dt) {
                bm = bms1.at(i);
                index = i;
            }
        }

        bms2.append(bm);

        bms1.removeAt(index);
    }

    return bms2;
}
