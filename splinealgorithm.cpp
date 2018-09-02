#include "splinealgorithm.h"

SplineAlgorithm::SplineAlgorithm(PointsArea* target)
    : m_targetArea(target)
{
}

void SplineAlgorithm::setStep(int step)
{
    m_pointesStep = step;

    calc();
}

void SplineAlgorithm::calc()
{
    //TODO: place splines algorithm here
    QList<QPoint> additionalPoints;

    QList<QPoint> mainPoints = m_targetArea->mainPoints();

    m_targetArea->setAdditionalPoints(additionalPoints);
}
