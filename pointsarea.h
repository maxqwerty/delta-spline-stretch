#ifndef POINTSAREA_H
#define POINTSAREA_H

#include <QWidget>

class PointsArea : public QWidget
{
    Q_OBJECT
public:
    explicit PointsArea(QWidget *parent = nullptr);
    void clear();

    QList<QPoint> mainPoints();
    void setMainPoints(QList<QPoint>);
    void setAdditionalPoints(QList<QPointF> points);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QList<QPoint> m_points;
    QList<QPointF> m_additionalPoints;
};

#endif // POINTSAREA_H
