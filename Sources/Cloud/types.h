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

#ifndef TYPES_H
#define TYPES_H

#include <QMap>
#include "../Core/Core/core.h"

namespace CloudTypes {
enum Cloud_Platform {
    Cloud_Platform_Pastebin
};

enum Cloud_DataType {
    Cloud_DataType_Text  = 1,
    Cloud_DataType_Html  = 2,
    Cloud_DataType_Image = 4
};

struct CloudData
{
    CloudData() {}
    QMap<QString, QVariant> settings;
    Core::ClipboardData     data;
    Cloud_Platform          platform;
};
}

#endif // TYPES_H
