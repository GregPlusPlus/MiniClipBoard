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

#include "win32.h"

bool API_available()
{
    return true;
}

QString API_getProcessPathFromActiveWindow()
{
    TCHAR wnd_title[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, (LPSTR)wnd_title, 256);

    if(hwnd == NULL) {
        return QString();
    }

    DWORD dwPID;
    GetWindowThreadProcessId(hwnd, &dwPID);

    HANDLE Handle = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE,
                dwPID
                );
    if(Handle)
    {
        TCHAR Buffer[MAX_PATH];
        if(GetModuleFileNameEx(Handle, 0, Buffer, MAX_PATH))
        {
            CloseHandle(Handle);

            return QString::fromStdWString(Buffer).replace("\\", "/");
        }

        CloseHandle(Handle);

        return QString();
    }

    return QString();
}

QString API_getActiveWindowTitle()
{
    LPWSTR wnd_title[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextW(hwnd, (LPWSTR)wnd_title, 256);

    if(hwnd == NULL) {
        return QString();
    }

    return QString::fromStdWString((LPWSTR)wnd_title);
}
