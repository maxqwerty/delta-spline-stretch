#ifndef PATHAREA_H
#define PATHAREA_H

#include <QWidget>

class PathArea : public QWidget
{
    Q_OBJECT
public:
    explicit PathArea(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QList<QPoint> m_points;
};

#endif // PATHAREA_H
