#include "pf.h"

pf::pf(QWidget *parent) : QFrame(parent){}

void pf::paintEvent(QPaintEvent *)
{    
      float x1,x2,y1,y2,new_x1,new_y1,new_x2,new_y2,l=10,a=0.5,ux,uy,vx,vy;
      double alpha;
      QPainter painter(this);
      painter.setPen(QPen(QColor(139,69,19, 200),2));//设置画笔形式
      if(ifA){
          VNode* p;
          int tempCount=0;
          QPushButton *bta;
          QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
          for (int i = 0; i < tg.vexNum; i++) {
              bta =(QPushButton *)(this->parentWidget()->children().at(i));
              bta->setGraphicsEffect(opacityEffect);
              opacityEffect->setOpacity(1);
              tempCount=1;
              p =tg.vexs[i].nextVex;
              while (p) {
                  bta =(QPushButton *)(this->parentWidget()->children().at(tempCount*20+i));
                  bta->setGraphicsEffect(opacityEffect);
                  opacityEffect->setOpacity(1);
                  bta->setText(QString::asprintf("%d",(int)p->data));
                  tempCount++;
                  p = p->nextVex;
              }
          }
          for (int i = 0; i < tg.vexNum; i++) {
              tempCount=1;
              bta =(QPushButton *)(this->parentWidget()->children().at(i));
              ux =bta->pos().x()+30-70,uy = bta->pos().y()+2;
              vx =bta->pos().x()+30-70,vy = bta->pos().y()+33;
              this->raise();
              painter.drawLine(ux,uy,vx,vy);//画直线
              p = tg.vexs[i].nextVex;
              while (p) {
                  bta =(QPushButton *)(this->parentWidget()->children().at(tempCount*20+i));
                  ux =bta->pos().x()+30-70,uy = bta->pos().y()+2;
                  vx =bta->pos().x()+30-70,vy = bta->pos().y()+33;

                  x1 =bta->pos().x()+30-70,y1= bta->pos().y()+17;
                  x2 =bta->pos().x(),y2 = bta->pos().y()+17;
                  alpha = atan2(y2-y1,x2-x1);//计算线段的夹角
                  new_x1= x2-l*cos(alpha-a),new_y1= y2-l*sin(alpha-a);
                  new_x2= x2-l*cos(alpha+a),new_y2= y2-l*sin(alpha+a);
                  this->raise();
                  painter.drawLine(ux,uy,vx,vy);//画直线
                  painter.drawLine(x1,y1,x2,y2);//画直线
                  painter.drawLine(new_x1,new_y1,x2,y2);//画直线
                  painter.drawLine(new_x2,new_y2,x2,y2);//画直线
                  tempCount++;
                  p = p->nextVex;
              }
              bta =(QPushButton *)(this->parentWidget()->children().at(tempCount*20+i));
              ux =bta->pos().x()+30-70,uy = bta->pos().y()+2;
              vx =bta->pos().x()+30-70,vy = bta->pos().y()+33;
              this->raise();
              painter.drawLine(ux,uy,vx,vy);//画直线
          }
      }
}
