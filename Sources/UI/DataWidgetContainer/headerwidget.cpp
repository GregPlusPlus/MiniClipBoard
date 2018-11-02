#include "headerwidget.h"

HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent)
{
    m_text = tr("Wow, such empty !");
    m_icon = QPixmap(":/icons/wind_18dp");

    connect(&m_animTimer, &QTimer::timeout, [=]() {
        m_animFrame++;

        if(m_animFrame == 24) {
            m_animFrame = 0;
            m_animTimer.stop();
        }

        update();
    });

    setToolTip(tr("Any copied data will appear here.\n"
                  "Copy something from another software to fill this area with awesomeness !"));

    setFixedHeight(30);
}

void HeaderWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#242D35"));

    painter.drawRect(rect());

    painter.setPen(QPen("#BECEE5"));

    QSize textSize = QFontMetrics(painter.font()).size(Qt::TextSingleLine, m_text);

    painter.drawText(QPoint((width() / 2) - (textSize.width() / 2), textSize.height() + 3), m_text);

    int offset = sin(m_animFrame / 2) * 5;

    painter.drawPixmap(QPoint((width() / 2) + (textSize.width() / 2) + 5 + offset, 4), m_icon);
}

void HeaderWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(!m_animTimer.isActive()) {
        m_animTimer.start(10);
    }
}
