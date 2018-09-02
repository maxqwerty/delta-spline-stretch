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

void PointsArea::setMainPoints(QList<QPoint> points)
{
    m_points = points;
    update();
}

void PointsArea::setAdditionalPoints(QList<QPointF> points)
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

    QPoint p = event->pos();

    float horFactor = static_cast<double>(this->width()) / 300;
    float verFactor = static_cast<double>(this->height()) / 300;
    p.setX(p.x() / horFactor);
    p.setY(p.y() / verFactor);

    m_points.append(p);

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
        painter.drawText(p, QString("%1,%2").arg(p.x()).arg(p.y()));
    }

    painter.setPen(Qt::red);

    foreach (QPointF p, m_additionalPoints) {
        painter.drawPoint(p);
    }
}
