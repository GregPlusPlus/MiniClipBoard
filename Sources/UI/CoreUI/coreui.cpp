/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017 Grégoire BOST

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

#include "coreui.h"

DataWidget *CoreUI::copyDataWidget(DataWidget *widget, QWidget *parent)
{
    DataWidget *w = new DataWidget(parent);

    if(widget->data().type == Core::MimeType_Color) {
        w->setDataColor(widget->color());
    } else if(widget->data().type == Core::MimeType_Html) {
        w->setDataHTML(widget->HTML());
    } else if(widget->data().type == Core::MimeType_Image) {
        w->setDataImage(widget->image());
    } else if(widget->data().type == Core::MimeType_Text) {
        w->setDataText(widget->text());
    } else if(widget->data().type == Core::MimeType_URLs) {
        w->setDataUrls(widget->URLs());
    }

    w->setBookmarked(widget->bookmarked());

    w->setShowThumbnails(widget->showThumbnails());

    return w;
}

AbstractListedWidget *CoreUI::getWidgetFromUUID(const QList<AbstractListedWidget *> &widgets, const QUuid &uuid)
{
    for(int i = 0; i < widgets.count() ; i++) {
        if(uuid == widgets.at(i)->Uuid()) {
            return widgets.at(i);
        }
    }

    return nullptr;
}

int CoreUI::filterDataWidgets(const Core::Filter &filter, QList<AbstractListedWidget *> widgets)
{
    int count = 0;

    if(filter.text.isEmpty()) {
        for(int i = 0; i < widgets.count(); i++) {
            DataWidget *w = qobject_cast<DataWidget *>(widgets.at(i));
            w->setVisible(true);
        }
    }

    for(int i = 0; i < widgets.count(); i++) {
        DataWidget *w = qobject_cast<DataWidget *>(widgets.at(i));

        if(w->title().toLower().contains(filter.text) &&
                (w->data().type == filter.type || filter.type == Core::MimeType_None) &&
                ((filter.dateTimeFilter.type == Core::DateTimeFilterType_None) ||
                (filter.dateTimeFilter.type == Core::DateTimeFilterType_Before && w->dateTime() <= filter.dateTimeFilter.dateTime_2) ||
                (filter.dateTimeFilter.type == Core::DateTimeFilterType_After && w->dateTime() >= filter.dateTimeFilter.dateTime_1) ||
                (filter.dateTimeFilter.type == Core::DateTimeFilterType_Between && w->dateTime() >= filter.dateTimeFilter.dateTime_1 && w->dateTime() <= filter.dateTimeFilter.dateTime_2))) {
            w->setVisible(true);
            count ++;
        } else {
            w->setVisible(false);
        }
    }

    return count;
}
