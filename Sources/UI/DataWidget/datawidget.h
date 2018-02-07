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

#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <QGridLayout>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QFont>
#include <QFontMetrics>

#include <QList>

#include <QColor>
#include <QString>
#include <QImage>
#include <QUrl>

#include <QDateTime>
#include <QTextDocument>
#include <QFileInfo>

#include <QClipboard>
#include <QMimeData>
#include <QVariant>

#include <QUuid>

#include <QDebug>

#include "../../Core/core.h"
#include "../ListWidget/abstractlistedwidget.h"
#include "ThumbnailWidget/imagethumbnail.h"
#include "ThumbnailWidget/colorthumbnailwidget.h"
#include "../../Utils/utils.h"
#include "../UtilsUI/utilsui.h"

class DataWidget : public AbstractListedWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

    QString title() const;

    QColor color() const;
    QString HTML() const;
    QString text() const;
    QPixmap image() const;
    Core::Urls URLs() const;

    bool bookmarked() const;
    void setBookmarked(bool bookmarked);

    Core::ClipboardData data() const;
    void setData(const Core::ClipboardData &data);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    bool showThumbnails() const;
    void setShowThumbnails(bool showThumbnails);

signals:
    void bookmarkChanged(bool bookmarked);
    void ignoreNextCopy();
    void seeContent(DataWidget *sender);

public slots:
    void setDataColor(const QColor &color);
    void setDataHTML(const QString &html);
    void setDataText(const QString &text);
    void setDataImage(const QPixmap &image);
    void setDataUrls(const Core::Urls &urls);
    void toggleBookMark();
    void removeWidget();
    void copy();
    void fadeIn();
    void fadeOut();

private slots:
    void fadeOutAnimationFinished();

private:
    QGridLayout *m_layout;

    QLabel *mw_icon;
    QWidget *mw_thumbnailWidget;
    QLabel *mw_title;
    QLabel *mw_infosLabel;
    QPushButton *mw_bookmark;
    QPushButton *mw_copy;
    QPushButton *mw_remove;
    QPushButton *mw_seeContent;

    Core::ClipboardData m_data;

    QString m_title;
    QDateTime m_dateTime;

    bool m_bookmarked;
    bool m_showThumbnails;

private:
    QString textFromURLs(const Core::Urls &urls);
    bool isThereFileFromURLs(const Core::Urls &urls);

    void setIcon(const QPixmap &pixmap);
    void displayInfos();
    QString elidedText(const QString &text, QLabel *label);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // DATAWIDGET_H
