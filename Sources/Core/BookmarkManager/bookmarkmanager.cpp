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

#include "bookmarkmanager.h"

BookmarkManager::BookmarkManager(QObject *parent) : QObject(parent)
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

    for(QString file : files) {
        if(!QUuid(file).isNull()) {
            list.append(QUuid(file));
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

    exportDir.mkdir("bookmarks");

    for(QUuid Uuid : Uuids) {
        if(!QFile::copy(dir().absolutePath() + "/" + Uuid.toString(),
                        exportDir.absolutePath() + "/bookmarks/" + Uuid.toString()))
        {
            if(QMessageBox::critical(nullptr, tr("File error"), tr("Unable to move file '%1' from '%2' to '%3'.")
                                     .arg(Uuid.toString())
                                     .arg(dir().absolutePath())
                                     .arg(exportDir.absolutePath() + "/bookmarks/"), QMessageBox::Ok | QMessageBox::Cancel)
                    == QMessageBox::Cancel) {
                return;
            }
        }
    }
}

void BookmarkManager::importBookmarks(const QDir &importDir)
{
    QStringList files = importDir.entryList(QDir::Files);

    for(QString file : files) {
        if(!QUuid(file).isNull()) {
            if(!QFile::copy(importDir.absolutePath() + "/" + file,
                            dir().absolutePath() + "/" + file)) {
                if(QMessageBox::critical(nullptr, tr("File error"), tr("Unable to move file '%1' from '%2' to '%3'.")
                                         .arg(file)
                                         .arg(importDir.absolutePath())
                                         .arg(dir().absolutePath()), QMessageBox::Ok | QMessageBox::Cancel)
                        == QMessageBox::Cancel) {
                    QMessageBox::information(nullptr, tr("Operation finished"), tr("You need to restart MiniClipBoard to update bookmarks."));
                    return;
                }
            }
        } else {
            if(QMessageBox::critical(nullptr, tr("File error"), tr("File name '%1' is not a valid UUID.")
                                     .arg(file), QMessageBox::Ok | QMessageBox::Cancel)
                    == QMessageBox::Cancel) {
                QMessageBox::information(nullptr, tr("Operation finished"), tr("You need to restart MiniClipBoard to update bookmarks."));
                return;
            }
        }
    }

    QMessageBox::information(nullptr, tr("Operation finished"), tr("You need to restart MiniClipBoard to update bookmarks."));
}
