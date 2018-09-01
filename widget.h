#ifndef WIDGET_H
#define WIDGET_H

#include "pointsarea.h"

#include <QWidget>
#include <QSlider>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onCalcClicked();
    void onClearClicked();

protected:
    int stepValue();

private:
    QSlider* m_stepSlider;
    PointsArea* m_pointsArea;
};

#endif // WIDGET_H
