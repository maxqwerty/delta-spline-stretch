#ifndef WIDGET_H
#define WIDGET_H

#include "pointsarea.h"
#include "splinealgorithm.h"

#include <QWidget>
#include <QSlider>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private slots:
    void onCalcClicked();
    void onClearClicked();

    virtual void resizeEvent(QResizeEvent *event);

private:
    QSlider* m_stepSlider;
    PointsArea* m_pointsArea;
    SplineAlgorithm m_algorithm;
};

#endif // WIDGET_H
