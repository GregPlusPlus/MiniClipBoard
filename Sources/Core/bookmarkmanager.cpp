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

#include "bookmarkmanager.h"

BookmarkManager::BookmarkManager() : QObject()
{

}

bool BookmarkManager::saveDataToFile(const QByteArray &data, const QUuid &uuid)
{
    QString path = QString("%1/%2").arg(m_dir.absolutePath()).arg(uuid.toString());

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(data);

    return true;
}

QByteArray BookmarkManager::getDataFromFile(const QUuid &uuid)
{
    QString path = QString("%1/%2").arg(m_dir.absolutePath()).arg(uuid.toString());

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    return file.readAll();
}

bool BookmarkManager::removeFile(const QUuid &uuid)
{
    QString path = QString("%1/%2").arg(m_dir.absolutePath()).arg(uuid.toString());
    QFile file(path);
    return file.remove();
}

QList<QUuid> BookmarkManager::getUuids()
{
    QList<QUuid> list;

    QStringList files = m_dir.entryList(QDir::Files);

    for(int i = 0; i < files.count(); i++) {
        QUuid uuid = QUuid(files.at(i));

        if(!uuid.isNull()) {
            list.append(uuid);
        }
    }

    return list;
}

QDir BookmarkManager::dir() const
{
    return m_dir;
}

void BookmarkManager::setDir(const QDir &dir)
{
    m_dir = dir;
}

void BookmarkManager::exportBookmarks(const QDir &exportDir)
{
    QList<QUuid> Uuids = getUuids();

    for(int i = 0; i < Uuids.count(); i++) {
        QFile::copy(dir().absolutePath() + "/" + Uuids.at(i).toString(),
                    exportDir.absolutePath() + "/" + Uuids.at(i).toString());
    }
}

void BookmarkManager::importBookmarks(const QDir &importDir)
{
    QStringList files = importDir.entryList(QDir::Files);

    for(int i = 0; i < files.count(); i++) {
        QFile::copy(importDir.absolutePath() + "/" + files.at(i),
                    dir().absolutePath() + "/" + files.at(i));
    }
}
