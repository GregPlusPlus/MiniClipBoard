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

#ifndef UNIQUEPROCESSCHECKER_H
#define UNIQUEPROCESSCHECKER_H

#include <QObject>

#include <QSharedMemory>
#include <QBuffer>

#include <QDebug>

#define SHARED_MEMORY_KEY "557e0b49-212c-48de-8349-bdb4d2cabaf0"

class UniqueProcessChecker : public QObject
{
    Q_OBJECT

public:
    explicit UniqueProcessChecker(QObject *parent = nullptr);

    static bool makeUnique(QObject *parent);
    static bool isUnique(QObject *parent);
    static QString key();

signals:

public slots:

private:
};

#endif // UNIQUEPROCESSCHECKER_H
