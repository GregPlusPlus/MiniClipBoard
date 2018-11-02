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

#include "uniqueprocesschecker.h"

UniqueProcessChecker::UniqueProcessChecker(QObject *parent) : QObject(parent)
{

}

bool UniqueProcessChecker::makeUnique(QObject *parent)
{
    QSharedMemory *sharedMemory = new QSharedMemory(key(), parent);

    bool state = sharedMemory->create(1);

    qDebug() << "UniqueProcessChecker - Create : " << ((state)?"[OK]":"[Fail]") << sharedMemory->errorString() << sharedMemory->key();

    return state;
}

bool UniqueProcessChecker::isUnique(QObject *parent)
{
    QSharedMemory *sharedMemory = new QSharedMemory(key(), parent);

    bool state = sharedMemory->attach();

    qDebug() << "UniqueProcessChecker - Check  : " << ((!state)?"[Unique]":"[Run twice]") << sharedMemory->errorString() << sharedMemory->key();

    return !state;
}

QString UniqueProcessChecker::key()
{
    return SHARED_MEMORY_KEY;
}
