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

#ifndef CLOUD_H
#define CLOUD_H

#include "API/Pastebin/pastebin.h"
#include "../Core/Core/core.h"

class Cloud : public QObject
{
    Q_OBJECT

public:
    explicit Cloud::Cloud(QObject *parent = nullptr);
    int getSupportedType(CloudTypes::Cloud_Platform platform);
    void upload(const CloudTypes::CloudData &data);

signals:
    void uploaded(const QString &result, CloudTypes::Cloud_Platform platform);
    void error(const QString &error, CloudTypes::Cloud_Platform platform);

private:
    Pastebin *m_p_pastebin;
};

#endif // CLOUD_H
