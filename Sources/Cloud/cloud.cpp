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

#include "cloud.h"

Cloud::Cloud::Cloud(QObject *parent) : QObject(parent)
{
    m_p_pastebin = new Pastebin(this);
    connect(m_p_pastebin, &Pastebin::done, [=](const QString &result) {
        emit uploaded(result, CloudTypes::Cloud_Platform_Pastebin);
    });
    connect(m_p_pastebin, &Pastebin::error, [=](const QString &errorStr) {
        emit error(errorStr, CloudTypes::Cloud_Platform_Pastebin);
    });
}

int Cloud::getSupportedType(CloudTypes::Cloud_Platform platform)
{
    switch (platform) {
    case CloudTypes::Cloud_Platform_Pastebin:
        return CloudTypes::Cloud_DataType_Text | CloudTypes::Cloud_DataType_Html;
        break;
    }

    return 0;
}

void Cloud::upload(const CloudTypes::CloudData &data)
{
    if(data.platform == CloudTypes::Cloud_Platform_Pastebin) {
        m_p_pastebin->upload(data);
    }
}
