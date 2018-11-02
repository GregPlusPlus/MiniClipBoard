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

#ifndef THREADLOADER_H
#define THREADLOADER_H

#include <QThread>

#include "../Core/core.h"
#include "../BookmarkManager/bookmarkmanager.h"

class ThreadLoader : public QThread
{
    Q_OBJECT

public:
    explicit ThreadLoader(BookmarkManager *manager, QObject *parent = nullptr);

    Core::Bookmarks bookmarks() const;

signals:
    void progress(int current, int max);

public slots:

private:
    Core::Bookmarks m_bookmarks;
    BookmarkManager *m_manager;

protected:
    void run();
};

#endif // THREADLOADER_H
