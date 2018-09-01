#ifndef POINTSAREA_H
#define POINTSAREA_H

#include <QWidget>

class PointsArea : public QWidget
{
    Q_OBJECT
public:
    explicit PointsArea(QWidget *parent = nullptr);
    void clear();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QList<QPoint> m_points;
};

#endif // POINTSAREA_H
