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

#include "excludedprocessesmanager.h"

ExcludedProcessesManager::ExcludedProcessesManager(QString fileName, QObject *parent) : QObject(parent), m_fileName(fileName)
{

}

bool ExcludedProcessesManager::checkProcessName(const QString &procName)
{
    for(QRegExp exp : m_regExps) {
        if(exp.indexIn(procName) != -1) {
            return true;
        }
    }

    return false;
}

bool ExcludedProcessesManager::loadFromFile()
{
    QFile file(m_fileName);

    if(file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);

        stream >> m_regExps;

        return true;
    }

    return false;
}

bool ExcludedProcessesManager::saveToFile()
{
    QFile file(m_fileName);

    if(file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);

        stream << m_regExps;

        return true;
    }

    return false;
}

void ExcludedProcessesManager::fromStringList(const QStringList &list)
{
    m_regExps.clear();

    for(QString str : list) {
        m_regExps.append(QRegExp(str));
    }
}

QString ExcludedProcessesManager::fileName() const
{
    return m_fileName;
}

void ExcludedProcessesManager::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

QStringList ExcludedProcessesManager::toStringList()
{
    QStringList list;

    for(QRegExp exp : m_regExps) {
        list.append(exp.pattern());
    }

    return list;
}

QList<QRegExp> ExcludedProcessesManager::regExps() const
{
    return m_regExps;
}

void ExcludedProcessesManager::setRegExps(const QList<QRegExp> &regExps)
{
    m_regExps = regExps;
}
