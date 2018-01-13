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

#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QObject>
#include <QWidget>

#include <QList>
#include <QStringList>

#include <QByteArray>
#include <QUuid>

#include <QFile>
#include <QDir>

#include <QDebug>

#include "core.h"

#include <QMessageBox>

class BookmarkManager
{
public:
    BookmarkManager();
    bool saveDataToFile(const QByteArray &data, const QUuid &uuid);
    QByteArray getDataFromFile(const QUuid &uuid);
    bool removeFile(const QUuid &uuid);
    QList<QUuid> getUUids();

    QDir dir() const;
    void setDir(const QDir &dir);

private:
    QDir m_dir;
};

#endif // BOOKMARKMANAGER_H
