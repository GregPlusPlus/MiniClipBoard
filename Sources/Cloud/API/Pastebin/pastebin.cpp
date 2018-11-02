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

#include "pastebin.h"

Pastebin::Pastebin(QObject *parent) : QObject(parent)
{

}

void Pastebin::upload(const CloudTypes::CloudData &data)
{
    qDebug() << "Trying to submit to Pastebin";

    QNetworkRequest req(QUrl("https://pastebin.com/api/api_post.php"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("api_option",               "paste");
    params.addQueryItem("api_dev_key",              CloudUtils::getValue("Pastebin/pastebin_api_key"));
    params.addQueryItem("api_paste_code",           QUrl::toPercentEncoding(dataToText(data.data)));
    params.addQueryItem("api_paste_expire_date",    QUrl::toPercentEncoding(data.settings.value("expire").toString()));
    params.addQueryItem("api_paste_private",        QUrl::toPercentEncoding(data.settings.value("private").toString()));
    params.addQueryItem("api_paste_name",           QUrl::toPercentEncoding(data.settings.value("name").toString()));

    m_p_reply = m_manager.post(req, params.toString().toUtf8());

    connect(m_p_reply, SIGNAL(finished()), this, SLOT(finished()));
    connect(m_p_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(_error()));
}

void Pastebin::finished()
{
    QString result = QString(m_p_reply->readAll());

    if(result.startsWith("Bad API request, ")) {
        emit error(result);
    } else if(m_p_reply->error() == QNetworkReply::NoError){
        emit done(result);
    }

    m_p_reply->deleteLater();
}

void Pastebin::_error()
{
    emit error(tr("Network error : %1").arg(m_p_reply->errorString()));
}

QString Pastebin::dataToText(const Core::ClipboardData &data)
{
    if(data.type == Core::MimeType_Text) {
        return data.text;
    } else if(data.type == Core::MimeType_Html) {
        QTextDocument doc;
        doc.setHtml(data.Html);
        return doc.toPlainText();
    } else if(data.type == Core::MimeType_Image) {
        return tr("Image / Size : %1x%2").arg(data.image.size().width()).arg(data.image.size().height());
    } else if(data.type == Core::MimeType_Color) {
        return tr("Color / Hex : %1").arg(data.color.name(QColor::HexRgb));
    } else if(data.type == Core::MimeType_URLs) {
        QString str = tr("%1 Urls :\n").arg(data.URLs.count());
        for(QUrl url : data.URLs) {
            str += (url.toString() + "\n");
        }
        return str;
    }

    return QString();
}

bool Pastebin::pastebinKeySeemsvalid(const QString &key)
{
    for(QChar c : key) {
        if(!c.isLetterOrNumber()) {
            return false;
        }
    }

    return !key.isEmpty();
}
