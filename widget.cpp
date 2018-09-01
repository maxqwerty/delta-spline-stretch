#include "widget.h"

#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_stepSlider(new QSlider())
    , m_pointsArea(new PointsArea(this))
{
    m_stepSlider->setOrientation(Qt::Horizontal);
    m_stepSlider->setTickInterval(10);
    m_stepSlider->setTickPosition(QSlider::TicksBelow);
    m_stepSlider->setPageStep(1);
    m_stepSlider->setRange(0, 100);

    QVBoxLayout* mainLay = new QVBoxLayout();

    QHBoxLayout* controlsLay = new QHBoxLayout();

    QLabel* tickText = new QLabel("0", this);
    tickText->setMinimumWidth(20);
    tickText->setMaximumWidth(20);

    controlsLay->addWidget(tickText);
    controlsLay->addWidget(m_stepSlider);

    connect(m_stepSlider, &QSlider::valueChanged,
            [tickText](int value)
    {
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

    mainLay->addLayout(controlsLay);
    mainLay->addWidget(m_pointsArea);

    setLayout(mainLay);
}

Widget::~Widget()
{

}

void Widget::onCalcClicked()
{
    m_stepSlider->setEnabled(false);

    //TODO: add "calculation and rendering" call here

    m_stepSlider->setEnabled(true);
}

void Widget::onClearClicked()
{
    m_pointsArea->clear();
}

int Widget::stepValue()
{
    return m_stepSlider->value();
}
