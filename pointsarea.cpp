#include "pointsarea.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>

PointsArea::PointsArea(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(300, 300);
}

void PointsArea::clear()
{
    m_points.clear();
    update();
}

void PointsArea::mouseReleaseEvent(QMouseEvent* event)
{
    if(!(event->button() & Qt::LeftButton))
    {
        QWidget::mouseReleaseEvent(event);
    }

    m_points.append(event->pos());

    event->accept();

    update();
}

void PointsArea::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QBrush brush(Qt::white, Qt::SolidPattern);
    QPen pen(Qt::black);

    QPainter painter(this);
    painter.setBrush(brush);
    painter.setPen(pen);

    foreach (QPoint p, m_points) {
        QRect r(0, 0, 3, 3);
        r.moveCenter(p);

        painter.drawRect(r);
    }
}
