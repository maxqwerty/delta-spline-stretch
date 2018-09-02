#include "widget.h"

#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_stepSlider(new QSlider())
    , m_pointsArea(new PointsArea(this))
    , m_algorithm(SplineAlgorithm(m_pointsArea))
{
    m_stepSlider->setOrientation(Qt::Horizontal);
    m_stepSlider->setTickInterval(10);
    m_stepSlider->setTickPosition(QSlider::TicksBelow);
    m_stepSlider->setPageStep(1);
    m_stepSlider->setRange(0, 100);

    QVBoxLayout* mainLay = new QVBoxLayout();

    QHBoxLayout* controlsLay = new QHBoxLayout();

    m_algorithm.setStep(0);

    QLabel* tickText = new QLabel("0", this);
    tickText->setMinimumWidth(20);
    tickText->setMaximumWidth(20);

    controlsLay->addWidget(tickText);
    controlsLay->addWidget(m_stepSlider);

    connect(m_stepSlider, &QSlider::valueChanged,
            [tickText, this](int value)
    {
        m_algorithm.setStep(value);
        tickText->setText(QString::number(value));
    });

    QPushButton* calcButton = new QPushButton("Calc", this);
    connect(calcButton, &QPushButton::clicked,
            this, &Widget::onCalcClicked);
    controlsLay->addWidget(calcButton);

    QPushButton* clearButton = new QPushButton("Clear", this);
    connect(clearButton, &QPushButton::clicked,
            this, &Widget::onClearClicked);
    controlsLay->addWidget(clearButton);


    QPushButton* presetButton = new QPushButton("Preset", this);
    connect(presetButton, &QPushButton::clicked,
            [&]()
    {
        m_pointsArea->setMainPoints(QList<QPoint>()
                                    << QPoint(50, 50)
                                    << QPoint(100, 250)
                                    << QPoint(150, 50)
                                    << QPoint(200, 250)
                                    << QPoint(250, 50));
    });
    controlsLay->addWidget(presetButton);

    mainLay->addLayout(controlsLay);
    mainLay->addWidget(m_pointsArea);

    setLayout(mainLay);
}

void Widget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    m_pointsArea->setAdditionalPoints(QList<QPointF>());
}

void Widget::onCalcClicked()
{
    m_stepSlider->setEnabled(false);

    m_algorithm.calc();

    m_stepSlider->setEnabled(true);
}

void Widget::onClearClicked()
{
    m_pointsArea->clear();
}
