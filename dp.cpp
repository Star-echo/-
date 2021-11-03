#pragma execution_character_set("utf-8")
#include "dp.h"

DP::DP(QWidget *parent) : QPushButton(parent){}

void DP::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        this->raise();
        this->pP = event->pos();
    }

}
QPoint DP::retP()
{
    return q;
}
void DP::setFalse(){

}

void DP::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        q=this->mapToParent(event->pos());
        this->move(this->mapToParent(event->pos()-this->pP));

        if(this->mapToParent(this->rect().topLeft()).x() <= 0) this->move(0, this->pos().y());

        if(this->mapToParent(this->rect().bottomRight()).x() >= this->parentWidget()->rect().width()){
            this->move(this->parentWidget()->rect().width() - this->width(), this->pos().y());
        }
        if(this->mapToParent(this->rect().topLeft()).y() <= 0) this->move(this->pos().x(), 0);

        if(this->mapToParent(this->rect().bottomRight()).y() >= this->parentWidget()->rect().height()){
            this->move(this->pos().x(), this->parentWidget()->rect().height() - this->height());
        }
    }   
}
