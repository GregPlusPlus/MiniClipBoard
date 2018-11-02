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

#ifndef CLIPBOARDDATA_H
#define CLIPBOARDDATA_H

#include <QColor>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QUrl>

#include <QUuid>

#include <QByteArray>
#include <QDataStream>

#include <QDateTime>

#include "../../Utils/utils.h"

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

struct ClipboardData {
    ClipboardData() {type = MimeType_None;}

    bool operator ==(const ClipboardData& a) const {
        return (a.type == type &&
                a.color == color &&
                a.text == text &&
                a.Html == Html &&
                a.image.toImage() == image.toImage() &&
                a.URLs == URLs);
    }

    friend QDataStream &operator <<(QDataStream& os, const ClipboardData &data) {
        os << uint8_t(data.type);

        switch (data.type) {
        case MimeType_Image:
            os << data.image;
            break;
        case MimeType_Color:
            os << data.color;
            break;
        case MimeType_Html:
            os << QString(data.Html);
            break;
        case MimeType_Text:
            os << QString(data.text.toUtf8());
            break;
        case MimeType_URLs:
            os << data.URLs;
            break;
        default:
            return os;
            break;
        }

        os << QDateTime::currentDateTime();

        os << Utils::getUserName();

        return os;
    }

    friend QDataStream &operator >>(QDataStream &is, ClipboardData &data) {
        uint8_t flag = 0;
        is >> flag;

        data.type = static_cast<MimeType>(flag);

        switch (data.type) {
        case MimeType_Image:
            is >> data.image;
            if(data.image.isNull()) {
                return is;
            }
            break;
        case MimeType_Color:
            is >> data.color;
            if(!data.color.isValid()) {
                return is;
            }
            break;
        case MimeType_Html:
            is >> data.Html;
            data.Html = QString(data.Html.toUtf8());
            if(data.Html.isNull()) {
                return is;
            }
            break;
        case MimeType_Text:
            is >> data.text;
            data.text = QString(data.text.toUtf8());
            if(data.text.isNull()) {
                return is;
            }
            break;
        case MimeType_URLs:
            is >> data.URLs;
            if(data.URLs.isEmpty()) {
                return is;
            }
            break;
        case MimeType_None:
            return is;
        default:
            ClipboardData _data;
            _data.type = MimeType_Invalid;
            return is;
            break;
        }

        return is;
    }

    MimeType type;
    QColor color;
    QString text;
    QString Html;
    QPixmap image;
    Urls URLs;
};

}

#endif // CLIPBOARDDATA_H
