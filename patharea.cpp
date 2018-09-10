#include "patharea.h"

#include <QMouseEvent>
#include <QPainter>

PathArea::PathArea(QWidget *parent) : QWidget(parent)
{

}

void PathArea::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    if (!m_points.length())
    {
        return;
    }
    QRect pointRect(0, 0, 2, 2);

    QPainter painter(this);

    foreach (QPoint p, m_points) {
        pointRect.moveCenter(p);
        painter.drawRect(pointRect);
    }

    if (m_points.length() < 3)
    {
        return;
    }

    QPainterPath path;
    path.moveTo(m_points.first());

    {
        //FIRST

        const QPoint S = m_points.at(0);
        const QPoint E1 = m_points.at(1);
        const QPoint E2 = m_points.at(2);

        QPoint cp1 = (S + E1) / 2;

        painter.setPen(Qt::yellow);
        pointRect.moveCenter(cp1);
        painter.drawRect(pointRect);

        QPoint bufCp2 = (E1 - cp1) / 2;
        double cp2Length = std::sqrt(std::pow(bufCp2.x(), 2) + std::pow(bufCp2.y(), 2));

        QLineF l1 = QLine(E2, S);
        l1.translate(E1 - E2);
        l1.setLength(cp2Length);

        QPoint cp2 = l1.p2().toPoint();

        painter.setPen(Qt::magenta);
        pointRect.moveCenter(cp2);
        painter.drawRect(pointRect);

        path.cubicTo(cp1, cp2, E1);
    }
    {
        //MIDDLE
        for (int i = 1; i < m_points.length() - 2; ++i)
        {
            QPoint bufCp = (m_points.at(i + 1) - m_points.at(i)) / 2;
            double cpLength = std::sqrt(std::pow(bufCp.x(), 2) + std::pow(bufCp.y(), 2));

            QLineF line1(m_points.at(i - 1), m_points.at(i + 1));
            line1.translate(m_points.at(i) - m_points.at(i - 1));
            line1.setLength(cpLength / 2);

            QLineF line2(m_points.at(i + 2), m_points.at(i));
            line2.translate(m_points.at(i + 1) - m_points.at(i + 2));
            line2.setLength(cpLength / 2);

            painter.setPen(Qt::green);
            painter.drawLine(line1);
            painter.drawLine(line2);

            QPointF cp;
            line1.intersect(line2, &cp);

            path.cubicTo(line1.p2(), line2.p2(), m_points.at(i + 1));
        }
    }


    {
        //LAST

        const QPoint S = m_points.at(m_points.length() - 1);
        const QPoint E1 = m_points.at(m_points.length() - 2);
        const QPoint E2 = m_points.at(m_points.length() - 3);

        QPoint cp2 = (S + E1) / 2;

        painter.setPen(Qt::yellow);
        pointRect.moveCenter(cp2);
        painter.drawRect(pointRect);

        QPoint bufCp2 = (E1 - cp2) / 2;
        double cp2Length = std::sqrt(std::pow(bufCp2.x(), 2) + std::pow(bufCp2.y(), 2));

        QLineF l1 = QLine(E2, S);
        l1.translate(E1 - E2);
        l1.setLength(cp2Length);

        QPoint cp1 = l1.p2().toPoint();

        painter.setPen(Qt::magenta);
        pointRect.moveCenter(cp2);
        painter.drawRect(pointRect);

        path.cubicTo(cp1, cp2, S);
    }

    painter.setPen(Qt::blue);
    painter.drawPath(path);
}

void PathArea::mouseReleaseEvent(QMouseEvent* event)
{
    m_points.append(event->pos());

    update();
}
