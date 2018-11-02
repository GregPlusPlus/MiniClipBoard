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

#include "threadloader.h"

ThreadLoader::ThreadLoader(BookmarkManager *manager, QObject *parent) : QThread(parent), m_manager(manager)
{

}

Core::Bookmarks ThreadLoader::bookmarks() const
{
    return m_bookmarks;
}

void ThreadLoader::run()
{
    QList<QUuid> uuids = m_manager->getUuids();

    int i = 0;

    for(QUuid uuid : uuids) {
        Core::Bookmark bm;
        bm.data = Core::byteArrayToClipboardData(m_manager->getDataFromFile(uuid), bm.dt, bm.userName);
        bm.uuid = uuid;
        m_bookmarks.append(bm);

        emit progress(i, m_bookmarks.count());
        i++;
    }

    m_bookmarks = Core::reorderBookmarks(m_bookmarks);
}
