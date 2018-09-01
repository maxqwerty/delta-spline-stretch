#ifndef POINTSAREA_H
#define POINTSAREA_H

#include <QWidget>

class PointsArea : public QWidget
{
    Q_OBJECT
public:
    explicit PointsArea(QWidget *parent = nullptr);
    void clear();

signals:

public slots:
};

#endif // POINTSAREA_H
