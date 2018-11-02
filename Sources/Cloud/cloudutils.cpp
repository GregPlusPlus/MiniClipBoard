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

#include "cloudutils.h"

QString CloudUtils::getValue(const QString &key)
{
    QSettings settings(cloudConfigFileName(), QSettings::IniFormat);

    return settings.value(key, QVariant(QString())).toString();
}

void CloudUtils::setValue(const QString &group, const QString &key, const QString &value)
{
    QSettings settings(cloudConfigFileName(), QSettings::IniFormat);

    settings.beginGroup(group);

    settings.setValue(key, value);
}

QString CloudUtils::getPlatformName(CloudTypes::Cloud_Platform platform)
{
    if(platform == CloudTypes::Cloud_Platform_Pastebin) {
        return "Pastebin";
    }

    return QString();
}

QString CloudUtils::getFormatedResult(const QString &result, CloudTypes::Cloud_Platform platform)
{
    if(platform == CloudTypes::Cloud_Platform_Pastebin) {
        return QString("Link to your paste: <a style=\"color: #3399ff;\"href=\"%1\">%1</a>").arg(result);
    }

    return result;
}

QString CloudUtils::cloudConfigFileName()
{
    return Utils::appDataPath() + "cloud.ini";
}
