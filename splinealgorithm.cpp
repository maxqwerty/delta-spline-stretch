#include "splinealgorithm.h"

#include <QtMath>

#include <QDebug>

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
    QList<QPointF> additionalPoints;

    QList<QPoint> mainPoints = m_targetArea->mainPoints();

    QList<double> Q = calcQ(mainPoints);

    QList<double> T = calcT(mainPoints);
    QList<double> L = calcL(mainPoints, Q, T);
    QList<double> P = calcP(Q, T, L);
    QList<double> D = calcD(Q, T, P);

    for (int i=0; i < T.length(); ++i)
    {
        int step = 2;
        step = (mainPoints.at(i + 1).x() - mainPoints.at(i).x()) > 0 ?
                    step :
                    -step;

        double currX = step;

        while (qAbs(currX) <= qAbs(D.at(i)))
        {
            double currY = mainPoints.at(i).y() + Q.at(i) * currX - qPow(currX, 2) * P.at(i) / 2;

            additionalPoints.append(QPointF(mainPoints.at(i).x() + currX, currY));

            currX += step;
        }

        while (qAbs(currX) <= qAbs(T.at(i)))
        {
            double currY = mainPoints.at(i + 1).y() - Q.at(i + 1) * (T.at(i) - currX) + qPow(T.at(i) - currX, 2) * P.at(i) / 2;

            additionalPoints.append(QPointF(mainPoints.at(i).x() + currX, currY));

            currX += step;
        }
    }

    m_targetArea->setAdditionalPoints(additionalPoints);
}

QList<double> SplineAlgorithm::calcQ(const QList<QPoint> points)
{
    QList<double> Q;

    Q.append(0.0);
    for (int i=1; i < (points.length() - 1); ++i)
    {
        double value = 0.0;

        int prevY = points.at(i-1).y();
        int currY = points.at(i).y();
        int nextY = points.at(i+1).y();

        int prevX = points.at(i-1).x();
        int currX = points.at(i).x();
        int nextX = points.at(i+1).x();

        if (((prevY > currY) && (nextY > currY)) ||
            ((prevY < currY) && (nextY < currY)))
        {
            value = 0.0;
        }
        else
        {
            value = 0.5 * ((currY - prevY) / (currX - prevX) +
                           (nextY - currY) / (nextX - currX));
        }

        Q.append(value);
    }
    Q.append(0.0);

    return Q;
}

QList<double> SplineAlgorithm::calcT(const QList<QPoint> points)
{
    QList<double> T;

    for (int i=0; i < (points.length() - 1); ++i)
    {
        T.append(points.at(i + 1).x() - points.at(i).x());
    }

    return T;
}

QList<double> SplineAlgorithm::calcL(const QList<QPoint> points, const QList<double> Q, const QList<double> T)
{
    QList<double> L;

    for (int i=0; i < (points.length() - 1); ++i)
    {
        L.append(points.at(i + 1).y() - points.at(i).y() - 0.5 * T.at(i) * (Q.at(i + 1) + Q.at(i)));
    }

    return L;
}

QList<double> SplineAlgorithm::calcP(const QList<double> Q, const QList<double> T, const QList<double> L)
{
    QList<double> P;

    for (int i=0; i < T.length(); ++i)
    {
        double length = qSqrt(qPow(L.at(i), 2) + qPow(0.5 * T.at(i) * (Q.at(i + 1) - Q.at(i)), 2));
        double invertedSign = (qAbs(L.at(i)) < 1e-6)
                  ? 0.0
                  : (std::signbit(L.at(i)) ? 1.0 : -1.0);

        P.append((-L.at(i) + invertedSign * length) / (0.5 * qPow(T.at(i), 2)));
    }

    return P;
}

QList<double> SplineAlgorithm::calcD(const QList<double> Q, const QList<double> T, const QList<double> P)
{
    QList<double> D;

    for (int i=0; i < T.length(); ++i)
    {
        if (qAbs(P.at(i)) < 1e-9)
        {
            D.append(0.0);
        }
        else
        {
            D.append((Q.at(i) - Q.at(i+1) + T.at(i) * P.at(i)) / (2 * P.at(i)));
        }
    }

    return D;
}
