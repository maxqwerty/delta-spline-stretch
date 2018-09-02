#ifndef SPLINEALGORITHM_H
#define SPLINEALGORITHM_H

#include "pointsarea.h"

class SplineAlgorithm
{
public:
    SplineAlgorithm(PointsArea* target);

    void setStep(int step);
    void calc();

private:
    QList<double> calcQ(const QList<QPoint> points);
    QList<double> calcT(const QList<QPoint> points);
    QList<double> calcL(const QList<QPoint> points, const QList<double> Q, const QList<double> T);
    QList<double> calcP(const QList<double> Q, const QList<double> T, const QList<double> L);
    QList<double> calcD(const QList<double> Q, const QList<double> T, const QList<double> P);

private:
    PointsArea* m_targetArea;
    int m_pointesStep;
};

#endif // SPLINEALGORITHM_H
