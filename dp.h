#ifndef DP_H
#define DP_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

class DP : public QPushButton
{
    Q_OBJECT
public:
    explicit DP(QWidget *parent = nullptr);
    QPoint retP();
    void setFalse();
    QPoint q;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint pP;
};

#endif // DP_H
