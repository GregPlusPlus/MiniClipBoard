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

#ifndef CORE_H
#define CORE_H

#include <QMimeData>

#include <QColor>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QUrl>

#include <QByteArray>
#include <QDataStream>

#include <QDateTime>

#include <QList>

#include <QDebug>

#include "coretypes.h"
#include "../Utils/utils.h"

namespace Core
{
    void reinterpretData(ClipboardData &data, MimeType type);

    bool isTextAnUrl(const QString &text);

    void autoReinterpretData(ClipboardData &data, const int &reinterpretFlags);

    ClipboardData QMimeToClipboardData(const QMimeData *mime);
    void clearClipboardData(ClipboardData &data);

    QByteArray clipboardDataToByteArray(const ClipboardData &data);
    ClipboardData byteArrayToClipboardData(const QByteArray &array, QDateTime &dateTime, QString &userName);
}

#endif // CORE_H
