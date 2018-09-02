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
    PointsArea* m_targetArea;
    int m_pointesStep;
};

#endif // SPLINEALGORITHM_H
