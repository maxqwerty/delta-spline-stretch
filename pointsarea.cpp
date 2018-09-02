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
    m_additionalPoints.clear();
    update();
}

QList<QPoint> PointsArea::mainPoints()
{
    QList<QPoint> resultFactored;

    float horFactor = static_cast<double>(this->width()) / 300;
    float verFactor = static_cast<double>(this->height()) / 300;

    foreach (QPoint p, m_points) {
        QPoint factoredPoint(p.x() * horFactor,
                              p.y() * verFactor);

        resultFactored.append(factoredPoint);
    }

    return resultFactored;
}

void PointsArea::setAdditionalPoints(QList<QPoint> points)
{
    m_additionalPoints = points;
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

    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);

    foreach (QPoint p, mainPoints()) {
        QRect r(0, 0, 3, 3);

        r.moveCenter(p);

        painter.drawRect(r);
    }

    painter.setPen(Qt::red);

    foreach (QPoint p, m_additionalPoints) {
        painter.drawPoint(p);
    }
}
