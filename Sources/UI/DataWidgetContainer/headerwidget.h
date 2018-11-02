#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

#include <QHBoxLayout>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QTimer>

#include <QFontMetrics>

#include<QDebug>

#include <cmath>

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    QString m_text;
    QPixmap m_icon;

    QTimer m_animTimer;
    int m_animFrame = 0;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // HEADERWIDGET_H
