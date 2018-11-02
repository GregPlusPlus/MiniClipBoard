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

#ifndef EXCLUDEDPROCESSMANAGER_H
#define EXCLUDEDPROCESSMANAGER_H

#include <QObject>

#include <QString>
#include <QRegExp>

#include <QList>

#include <QDataStream>

#include <QFile>

#include <QDebug>

class ExcludedProcessesManager : public QObject
{
    Q_OBJECT

public:
    explicit ExcludedProcessesManager(QString fileName = QString(), QObject *parent = nullptr);

    bool checkProcessName(const QString &procName);

    QList<QRegExp> regExps() const;
    void setRegExps(const QList<QRegExp> &regExps);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QStringList toStringList();

signals:

public slots:
    bool loadFromFile();
    bool saveToFile();
    void fromStringList(const QStringList &list);

private:
    QList<QRegExp> m_regExps;

    QString m_fileName;
};

#endif // EXCLUDEDPROCESSMANAGER_H
