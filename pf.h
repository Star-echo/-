#ifndef PF_H
#define PF_H

#include <QWidget>
#include "speci.h"
#include <QPainter>
#include <math.h>
#include <QFrame>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include "dp.h"
#include "mygraph.h"
#include "pf.h"
#include <QTimer>


class pf : public QFrame
{
    Q_OBJECT
public:
    explicit pf(QWidget *parent = nullptr);
    MyGraph tg;
    int ifA;
protected:
    void paintEvent(QPaintEvent *);



};



#endif // PF_H
