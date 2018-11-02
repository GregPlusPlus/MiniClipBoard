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

#include "datawidget.h"

DataWidget::DataWidget(QWidget *parent) : AbstractListedWidget(parent)
{
    m_data.type = Core::MimeType_None;

    //setFixedHeight(70);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_layout = new QGridLayout;
    m_layout->setContentsMargins(0, 10, 0, 0);

    mw_icon = new QLabel(this);
    mw_icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //mw_icon->setFixedSize(30, 30);

    mw_thumbnailWidget = new QWidget(this);

    mw_title = new QLabel(this);
    mw_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QFont fontData = mw_title->font();
    fontData.setBold(true);
    fontData.setPixelSize(15);
    mw_title->setFont(fontData);

    mw_infosLabel = new QLabel(this);
    mw_infosLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QFont fontInfos = mw_title->font();
    fontInfos.setItalic(true);
    fontInfos.setPixelSize(10);
    mw_infosLabel->setFont(fontInfos);

    mw_bookmark = new FlatActionButton(QIcon(":/icons/ic_favorite_border_white_18dp"), tr("Bookmark"), this);
    connect(mw_bookmark, &FlatActionButton::clicked, this, &DataWidget::toggleBookMark);

    mw_copy = new FlatActionButton(QIcon(":/icons/ic_content_copy_white_18dp"), tr("Copy"), this);
    connect(mw_copy, &FlatActionButton::clicked, this, &DataWidget::copy);

    mw_remove = new FlatActionButton(QIcon(":/icons/ic_remove_circle_white_18dp"), tr("Remove from list"), this);
    connect(mw_remove, &FlatActionButton::clicked, this, &DataWidget::removeWidget);

    mw_seeContent = new QPushButton(this);
    mw_seeContent->setFlat(true);
    mw_seeContent->setIcon(QIcon(":/icons/arrow_next_big_right"));
    mw_seeContent->setCursor(Qt::PointingHandCursor);
    mw_seeContent->setToolTip(tr("See content"));
    mw_seeContent->setFixedWidth(20);
    connect(mw_seeContent, &QPushButton::clicked, [=]() {
        emit seeContent(this);
    });

    m_layout->addWidget(mw_icon,                    0, 0, 2, 2);
    m_layout->addWidget(mw_thumbnailWidget,         0, 2, 2, 2);
    m_layout->addWidget(mw_title,                   0, 4, 1, 4);
    m_layout->addWidget(mw_infosLabel,              1, 4, 1, 1);
    m_layout->addWidget(mw_bookmark,                1, 5, 1, 1);
    m_layout->addWidget(mw_copy,                    1, 6, 1, 1);
    m_layout->addWidget(mw_remove,                  1, 7, 1, 1);
    m_layout->addWidget(mw_seeContent,              0, 8, 2, 1);
    m_layout->addWidget(UtilsUI::createSeparator(), 2, 0, 1, 8);

    setLayout(m_layout);
}

DataWidget::~DataWidget()
{

}

void DataWidget::setDataColor(const QColor &color)
{
    m_data.type = Core::MimeType_Color;
    m_data.color = color;

    setIcon(QPixmap(":/icons/ic_color_lens_white_24dp"));

    QString title = tr("r: %1, g: %2, b: %3, a: %4").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());

    m_title     = title;
    m_fullTitle = title;
    mw_title->setText(title);

    delete mw_thumbnailWidget;
    mw_thumbnailWidget = new ColorThumbnailWidget(m_data.color, this);
    mw_thumbnailWidget->setVisible(m_showThumbnails);
    m_layout->addWidget(mw_thumbnailWidget, 0, 2, 2, 2);

    displayInfos();
}

void DataWidget::setDataHTML(const QString &html)
{
    m_data.type = Core::MimeType_Html;
    m_data.Html = html;

    setIcon(QPixmap(":/icons/ic_text_format_white_24dp"));

    QTextDocument doc;
    doc.setHtml(html);

    QString title = doc.toPlainText().replace("\n", " ");

    m_title     = title.left(m_maxTitleLength);
    m_fullTitle = title;
    mw_title->setText(elidedText(title, mw_title));

    displayInfos();
}

void DataWidget::setDataText(const QString &text)
{
    m_data.type = Core::MimeType_Text;
    m_data.text = text.toUtf8();

    setIcon(QPixmap(":/icons/ic_text_fields_white_24dp"));

    QString title = QString(text).remove("\n");

    m_title     = title.left(m_maxTitleLength);
    m_fullTitle = title;
    mw_title->setText(elidedText(title, mw_title));

    displayInfos();
}

void DataWidget::setDataImage(const QPixmap &image)
{
    m_data.type = Core::MimeType_Image;
    m_data.image = image;

    setIcon(QPixmap(":/icons/ic_photo_white_24dp"));

    QString title = tr("%1x%2 | Depth: %3").arg(image.width()).arg(image.height()).arg(image.depth());

    m_title     = title;
    m_fullTitle = title;
    mw_title->setText(title);

    delete mw_thumbnailWidget;
    mw_thumbnailWidget = new ImageThumbnail(&m_data.image, this);
    mw_thumbnailWidget->setVisible(m_showThumbnails);
    m_layout->addWidget(mw_thumbnailWidget, 0, 2, 2, 2);

    displayInfos();
}

void DataWidget::setDataUrls(const Core::Urls &urls)
{
    m_data.type = Core::MimeType_URLs;
    m_data.URLs = urls;

    if(filesFromURLs(urls) == 1) {
        setIcon(QPixmap(":/icons/ic_insert_drive_file_white_24dp"));
    } else if(filesFromURLs(urls) > 1) {
        setIcon(QPixmap(":/icons/ic_insert_drive_multiple_files_white_24dp"));
    } else {
        setIcon(QPixmap(":/icons/ic_link_white_24dp"));
    }

    QString title = textFromURLs(urls);

    m_title     = title;
    m_fullTitle = title;
    mw_title->setText(elidedText(title, mw_title));

    displayInfos();
}

void DataWidget::toggleBookMark()
{
    m_bookmarked = !m_bookmarked;

    if(m_bookmarked) {
        //mw_bookmark->setIcon(QIcon(":/icons/ic_bookmark_white_18dp"));
        mw_bookmark->setIcon(QIcon(":/icons/ic_favorite_white_18dp"));
    } else {
        //mw_bookmark->setIcon(QIcon(":/icons/ic_bookmark_border_white_18dp"));
        mw_bookmark->setIcon(QIcon(":/icons/ic_favorite_border_white_18dp"));
    }

    emit bookmarkChanged(m_bookmarked);
}

void DataWidget::removeWidget()
{
    m_beingRemoved = true;
    fadeOut();
}

void DataWidget::copy()
{
    emit ignoreNextCopy();

    QMimeData *data = new QMimeData;

    switch (m_data.type) {
    case Core::MimeType_Color:
        data->setColorData(QVariant(m_data.color));
        break;
    case Core::MimeType_Html: {
        data->setHtml(m_data.Html);
        QTextDocument doc;
        doc.setHtml(m_data.Html);
        data->setText(doc.toPlainText());
    }
        break;
    case Core::MimeType_Text:
        data->setText(m_data.text);
        break;
    case Core::MimeType_Image:
        data->setImageData(QVariant(m_data.image));
        break;
    case Core::MimeType_URLs:
        data->setUrls(m_data.URLs);
        break;
    default:
        return;
        break;
    }

    QApplication::clipboard()->setMimeData(data);
}

bool DataWidget::showThumbnails() const
{
    return m_showThumbnails;
}

void DataWidget::setShowThumbnails(bool showThumbnails)
{
    m_showThumbnails = showThumbnails;

    mw_thumbnailWidget->setVisible(m_showThumbnails);
}

void DataWidget::setDateTime(const QDateTime &dateTime)
{
    m_dateTime = dateTime;

    displayInfos();
}

QDateTime DataWidget::dateTime() const
{
    return m_dateTime;
}

Core::ClipboardData DataWidget::data() const
{
    return m_data;
}

void DataWidget::setData(const Core::ClipboardData &data)
{
    m_data = data;

    switch (m_data.type) {
    case Core::MimeType_Color:
        setDataColor(data.color);
        break;
    case Core::MimeType_Html:
        setDataHTML(data.Html);
        break;
    case Core::MimeType_Image:
        setDataImage(data.image);
        break;
    case Core::MimeType_Text:
        setDataText(data.text);
        break;
    case Core::MimeType_URLs:
        setDataUrls(data.URLs);
        break;
    default:
        return;
        break;
    }
}

void DataWidget::setBookmarked(bool bookmarked)
{
    m_bookmarked = bookmarked;

    if(m_bookmarked) {
        //mw_bookmark->setIcon(QIcon(":/icons/ic_bookmark_white_18dp"));
        mw_bookmark->setIcon(QIcon(":/icons/ic_favorite_white_18dp"));
    } else {
        //mw_bookmark->setIcon(QIcon(":/icons/ic_bookmark_border_white_18dp"));
        mw_bookmark->setIcon(QIcon(":/icons/ic_favorite_border_white_18dp"));
    }

    emit bookmarkChanged(m_bookmarked);
}

bool DataWidget::bookmarked() const
{
    return m_bookmarked;
}

Core::Urls DataWidget::URLs() const
{
    return m_data.URLs;
}

QPixmap DataWidget::image() const
{
    return m_data.image;
}

QString DataWidget::text() const
{
    return m_data.text;
}

QString DataWidget::HTML() const
{
    return m_data.Html;
}

QColor DataWidget::color() const
{
    return m_data.color;
}

QString DataWidget::title() const
{
    return m_title;
}

QString DataWidget::textFromURLs(const Core::Urls &urls)
{
    QString str_urls;

    for(QUrl _url : urls) {
        QString url(_url.toString());

        if(_url.isLocalFile()) {
            url.remove("file:///");
            str_urls += tr("File: ") + QFileInfo(url).fileName();
        } else {
            str_urls += url;
        }

        str_urls += " , ";
    }

    return str_urls.left(str_urls.length() - 3);
}

int DataWidget::filesFromURLs(const Core::Urls &urls)
{
    int count = 0;

    for(QUrl url : urls) {
        if(url.toString().startsWith("file:///")) {
            count++;
        }
    }

    return count;
}

void DataWidget::setIcon(const QPixmap &pixmap)
{
    mw_icon->setPixmap(pixmap);
}

void DataWidget::displayInfos()
{
    mw_infosLabel->setText(m_dateTime.toString(tr("dd/MM/yy hh:mm:ss")));
}

QString DataWidget::elidedText(const QString &text, QLabel *label)
{
    QFontMetrics metrics(label->font());
    return metrics.elidedText(text, Qt::ElideRight, label->width() - 30);
}

void DataWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    mw_title->setText(elidedText(m_title, mw_title));
}

void DataWidget::fadeIn()
{
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
    QPropertyAnimation *animOpacity = new QPropertyAnimation(opacity, "opacity");

    setGraphicsEffect(opacity);

    animOpacity->setDuration(m_animationDuration);
    animOpacity->setStartValue(0);
    animOpacity->setEndValue(1);
    animOpacity->setEasingCurve(QEasingCurve::OutQuint);
    animOpacity->start();

    QPropertyAnimation *animSize = new QPropertyAnimation(this, "size");
    animSize->setDuration(m_animationDuration);
    animSize->setStartValue(QSize(width(), 0));
    animSize->setEndValue(QSize(width(), height()));
    animSize->setEasingCurve(QEasingCurve::InOutExpo);
    animSize->start();
}

void DataWidget::fadeOut()
{
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity", this);
    connect(anim, &QPropertyAnimation::finished, [=]() {
        emit removed(this);
    });

    setGraphicsEffect(opacity);

    anim->setDuration(m_animationDuration);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();

    QPropertyAnimation *animSize = new QPropertyAnimation(this, "size");
    animSize->setDuration(m_animationDuration);
    animSize->setStartValue(size());
    animSize->setEndValue(QSize(width(), 0));
    animSize->setEasingCurve(QEasingCurve::InOutBack);
    animSize->start();
}

QString DataWidget::fullTitle() const
{
    return m_fullTitle;
}

bool DataWidget::beingRemoved() const
{
    return m_beingRemoved;
}
