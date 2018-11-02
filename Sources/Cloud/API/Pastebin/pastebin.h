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

#ifndef PASTEBIN_H
#define PASTEBIN_H

#include <QString>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QTextDocument>

#include <QDebug>

#include "../../../Core/Core/core.h"
#include "../../types.h"
#include "../../cloudutils.h"

class Pastebin : public QObject
{
    Q_OBJECT

public:
    explicit Pastebin(QObject *parent = nullptr);
    void upload(const CloudTypes::CloudData &data);

    static bool pastebinKeySeemsvalid(const QString &key);

signals:
    void done(const QString &url);
    void error(const QString &error);

public slots:
    void finished();
    void _error();

private:
    QNetworkReply *m_p_reply;
    QNetworkAccessManager m_manager;

private:
    QString dataToText(const Core::ClipboardData &data);
};

#endif // PASTEBIN_H
