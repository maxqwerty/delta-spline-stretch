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

    float horFactor = static_cast<double>(this->width()) / 300;
    float verFactor = static_cast<double>(this->height()) / 300;

    foreach (QPoint p, m_points) {
        QRect r(0, 0, 3, 3);

        QPoint factoredPoint(p.x() * horFactor,
                              p.y() * verFactor);

        r.moveCenter(factoredPoint);

        painter.drawRect(r);
    }
}
