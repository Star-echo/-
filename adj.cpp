#include "adj.h"
#include "ui_adj.h"

adj::adj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adj)
{
    ui->setupUi(this);
    f = new pf(this);
    f->setGeometry(0,0,1000,1000);
    QGraphicsOpacityEffect *opacityEffect1=new QGraphicsOpacityEffect;
    f->setGraphicsEffect(opacityEffect1);
    opacityEffect1->setOpacity(0.5);
}

adj::~adj()
{
    delete ui;
}


