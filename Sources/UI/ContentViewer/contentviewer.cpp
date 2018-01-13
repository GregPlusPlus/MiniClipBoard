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

#include "contentviewer.h"

ContentViewer::ContentViewer(QWidget *parent) : QWidget(parent)
{
    m_headerHeight = 69;

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QLabel{background-color: none;}");
    setAcceptDrops(true);

    setFixedSize(parent->size());
    move(0, 0);

    mw_header = new QWidget(this);
    mw_header->setGeometry(0, 0, width(), m_headerHeight);
    mw_header->setAttribute(Qt::WA_TranslucentBackground);
    mw_header->show();

    m_headerLayout = new QGridLayout;
    m_headerLayout->setMargin(0);
    m_headerLayout->setSpacing(0);

    mw_quitButton = new QPushButton(QIcon(":/icons/arrow_next_big_left"), QString(), this);
    mw_quitButton->setFlat(true);
    mw_quitButton->setFixedSize(40, m_headerHeight);
    mw_quitButton->setCursor(Qt::PointingHandCursor);
    mw_quitButton->setStyleSheet("QPushButton{background-color: none; border: none; padding-bottom: 1px;}"
                                 "QPushButton:hover{background-color: rgba(255, 255, 255, .1);}"
                                 "QPushButton:pressed{background-color: rgba(0, 0, 0, .1);}");
    connect(mw_quitButton, &QPushButton::clicked, [=](){
        fadeOut();
    });

    mw_title = new QLabel(this);
    mw_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mw_title->setFixedHeight(m_headerHeight / 2);
    mw_title->setAlignment(Qt::AlignBottom);

    QFont fontData = mw_title->font();
    fontData.setBold(true);
    fontData.setPixelSize(15);
    mw_title->setFont(fontData);

    mw_infosLabel = new QLabel(this);
    mw_infosLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mw_infosLabel->setFixedHeight(m_headerHeight / 2);

    mw_saveButton = new QPushButton(QIcon(":/icons/ic_save_white_18dp"), QString(), this);
    mw_saveButton->setFixedSize(20, 20);
    mw_saveButton->setCursor(Qt::PointingHandCursor);
    mw_saveButton->setFlat(true);
    mw_saveButton->setToolTip(tr("Save data to file"));
    connect(mw_saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));

    QFont fontInfos = mw_title->font();
    fontInfos.setItalic(true);
    fontInfos.setPixelSize(10);
    mw_infosLabel->setFont(fontInfos);

    m_headerLayout->addWidget(mw_quitButton, 0, 0, 2, 1);
    m_headerLayout->addWidget(mw_title, 0, 1, 1, 4);
    m_headerLayout->addWidget(mw_saveButton, 1, 1, 1, 1);
    m_headerLayout->addWidget(mw_infosLabel, 1, 2, 1, 3, Qt::AlignLeft);

    mw_viwer = new QWidget(this);

    mw_header->setLayout(m_headerLayout);
}

Core::ClipboardData ContentViewer::data() const
{
    return m_data;
}

void ContentViewer::setData(const Core::ClipboardData &data)
{
    m_data = data;

    displayData();
}

QDateTime ContentViewer::dateTime() const
{
    return m_dateTime;
}

void ContentViewer::setDateTime(const QDateTime &dateTime)
{
    m_dateTime = dateTime;

    displayInfos();
}

QString ContentViewer::title() const
{
    return m_title;
}

void ContentViewer::setTitle(const QString &title)
{
    m_title = title;

    mw_title->setText(elidedText(QString(title).remove("\n"), mw_title));
}

void ContentViewer::save()
{
    QString filter;
    switch (m_data.type) {
    case Core::MimeType_Text :
        filter = tr("Plain text (*.txt)");
        break;
    case Core::MimeType_Html :
        filter = tr("Hypertext Markup Language (*.html)");
        break;
    case Core::MimeType_Image :
        filter = tr("Portable Network Graphics (*.png)");
        break;
    case Core::MimeType_URLs :
        filter = ("Plain text (*.txt)");
        break;
    case Core::MimeType_Color :
        filter = ("Plain text (*.txt)");
        break;
    default:
        return;
        break;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save to file"), QString(), filter);

    if(!fileName.isEmpty()) {
        switch (m_data.type) {
        case Core::MimeType_Text :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(m_data.text.toUtf8());
            }
        }
            break;
        case Core::MimeType_Html :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(m_data.Html.toUtf8());
            }
        }
            break;
        case Core::MimeType_Image :
        {m_data.image.save(fileName);}
            break;
        case Core::MimeType_URLs :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                QString str;
                for(int i = 0; i < m_data.URLs.count(); i++) {
                    str.append(m_data.URLs.at(i).toString() + "\n\r");
                }
                f.write(str.toUtf8());
            }
        }
            break;
        case Core::MimeType_Color :
        {
            QFile f(fileName);
            if(f.open(QIODevice::WriteOnly)) {
                f.write(m_data.color.name().toUtf8());
            }
        }
            break;
        default:
            return;
            break;
        }
    }
}

void ContentViewer::fadeIn()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(m_animationDuration);
    animation->setStartValue(QPoint(-width(), y()));
    animation->setEndValue(QPoint(0, y()));
    animation->setEasingCurve(QEasingCurve::OutQuart);
    animation->start();
}

void ContentViewer::fadeOut()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(m_animationDuration);
    animation->setStartValue(QPoint(0, y()));
    animation->setEndValue(QPoint(-width(), y()));
    animation->setEasingCurve(QEasingCurve::InBack);
    connect(animation, &QPropertyAnimation::finished, [=](){
        emit closed();
        deleteLater();
    });
    animation->start();
}

int ContentViewer::animationDuration() const
{
    return m_animationDuration;
}

void ContentViewer::setAnimationDuration(int animationDuration)
{
    m_animationDuration = animationDuration;
}

QString ContentViewer::elidedText(const QString &text, QLabel *label)
{
    QFontMetrics metrics(label->font());
    return metrics.elidedText(text, Qt::ElideRight, label->width() - 30);
}

void ContentViewer::applyMask()
{
    if(!parent()) {
        return;
    }

    QWidget *_parent = qobject_cast<QWidget *>(parent());

    while(_parent->parent()) {
        _parent = qobject_cast<QWidget *>(_parent->parent());
    }

    setMask(_parent->mask());
}

void ContentViewer::displayInfos()
{
    QString infos = m_dateTime.toString(tr("dd/MM/yy hh:mm:ss"));


    mw_infosLabel->setText(infos);
}

void ContentViewer::displayData()
{
    if(mw_viwer) {
        delete mw_viwer;
    }

    switch (m_data.type) {
    case Core::MimeType_Text :
        mw_viwer = new TextViewer(m_data.text, this);
        break;
    case Core::MimeType_Html :
        mw_viwer = new HTMLViewer(m_data.Html, this);
        break;
    case Core::MimeType_Image :
        mw_viwer = new ImageViwer(m_data.image, this);
        break;
    case Core::MimeType_URLs :
        mw_viwer = new LinksViwer(m_data.URLs, this);
        break;
    case Core::MimeType_Color :
        mw_viwer = new ColorViewer(m_data.color, this);
        break;
    default:
        mw_viwer = nullptr;
        return;
        break;
    }

    mw_viwer->show();
}

void ContentViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    applyMask();

    QPainter painter(this);

    QBrush bg(QColor("#313D4A"));
    painter.setBrush(bg);

    painter.drawRect(0, 0, width(), height());

    bg.setColor(QColor("#282C34"));
    QPen border(QColor("#19232D"));

    painter.setBrush(bg);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width(), m_headerHeight);

    painter.setPen(border);
    painter.drawLine(0, m_headerHeight, width(), m_headerHeight);

    mw_title->setText(elidedText(m_title, mw_title));

    mw_header->setGeometry(0, 0, width(), m_headerHeight);

    if(mw_viwer) {
        mw_viwer->setGeometry(0, m_headerHeight + 1, width(), height() - m_headerHeight);
    }
}
