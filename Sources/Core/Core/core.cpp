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

#include "core.h"

Core::ClipboardData Core::QMimeDataToClipboardData(const QMimeData *mime)
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
    return QUrl(text).isValid();

    //if(text.startsWith("http://") ||
    //      text.startsWith("https://") ||
    //      text.startsWith("file:///") ||
    //      text.startsWith("www.")) {
    //  return true;
    //}

    //return false;
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

    stream << data;

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

    stream >> data;

    stream >> dateTime;

    stream >> userName;

    return data;
}

Core::Bookmarks Core::reorderBookmarks(const Core::Bookmarks &bookmarks)
{
    Core::Bookmarks bms1 = bookmarks;
    Core::Bookmarks bms2;

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

void Core::saveData(const Core::ClipboardData &data)
{
    QString filter;
    switch (data.type) {
    case Core::MimeType_Text :
        filter = QObject::tr("Plain text (*.txt)");
        break;
    case Core::MimeType_Html :
        filter = QObject::tr("Hypertext Markup Language (*.html)");
        break;
    case Core::MimeType_Image :
        filter = QObject::tr("Portable Network Graphics (*.png)");
        break;
    case Core::MimeType_URLs :
        filter = QObject::tr("Plain text (*.txt)");
        break;
    case Core::MimeType_Color :
        filter = QObject::tr("Plain text (*.txt)");
        break;
    default:
        return;
        break;
    }

    QString fileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save to file"), QString(), filter);

    if(!fileName.isEmpty()) {
        switch (data.type) {
        case Core::MimeType_Text :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(data.text.toUtf8());
            }
        }
            break;
        case Core::MimeType_Html :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(data.Html.toUtf8());
            }
        }
            break;
        case Core::MimeType_Image :
        {data.image.save(fileName);}
            break;
        case Core::MimeType_URLs :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                QString str;
                for(int i = 0; i < data.URLs.count(); i++) {
                    str.append(data.URLs.at(i).toString() + "\n\r");
                }
                f.write(str.toUtf8());
            }
        }
            break;
        case Core::MimeType_Color :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(data.color.name().toUtf8());
            }
        }
            break;
        default:
            return;
            break;
        }
    }
}

QMap<QString, Core::FileType> Core::supportedFiles()
{
    return QMap<QString, Core::FileType>{
        {"png",  Core::FileType_Image},
        {"jpg",  Core::FileType_Image},
        {"jpeg", Core::FileType_Image},
        {"bmp",  Core::FileType_Image},
        {"html", Core::FileType_Html },
        {"htm",  Core::FileType_Html },
        {"txt",  Core::FileType_Text }};
}

bool Core::isFileSupported(const QUrl &url, const Plugins::Plugins &plugins)
{
    return supportedFiles().contains(QFileInfo(url.toString()).suffix().toLower()) ||
            isFileSupportedByPlugins(url, plugins);
}

bool Core::isFileSupportedByPlugins(const QUrl &url, const Plugins::Plugins &plugins)
{
    for(Plugins::Plugin plugin : plugins) {
        PluginViewerInterface *interface = plugin.interface;

        if(interface->supportedFormats().contains(QFileInfo(url.toString()).suffix().toLower())) {
            return true;
        }
    }

    return false;
}

Core::FileType Core::getFileType(const QUrl &url, const Plugins::Plugins &plugins)
{
    if(isFileSupportedByPlugins(url, plugins)) {
        return Core::FileType_FromPlugin;
    }

    if(isFileSupported(url, plugins)) {
        return supportedFiles().value(QFileInfo(url.toString()).suffix().toLower());
    } else {
        return Core::FileType_Unknown;
    }
}
