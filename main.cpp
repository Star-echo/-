#include "widget.h"
#include "dp.h"
#include <QApplication>
#include <QScrollArea>
#include <QPalette>
/*void setTable(QFrame*f){
    for(int j=0;j<4;j++) {
        for(int k=0;k<5;k++) {
            DP *bt = new DP(f);
            bt->setGeometry(j*38, k*38, 38, 38);
            bt->setStyleSheet(
                        "QPushButton{"
                            "background-color:rgba(174,221,129,200);"
                            "border-style:outset;"
                            "border-width:4px;"
                            "border-radius:19px;"
                            "border-color:rgba(255,255,255,30);"
                            "font:bold 20px;"
                            "color:rgba(54,37,17,200);"
                            "padding:6px;"
                            "}"
                            "QPushButton:pressed{"
                            "background-color:rgba(174,221,129,200);"
                            "border-color:rgba(255,255,255,30);"
                            "border-style:inset;"
                            "color:rgba(0,0,0,100);"
                            "}"
                            "QPushButton:hover{"
                            "background-color:rgba(174,221,129,100);"
                            "border-color:rgba(255,255,255,200);"
                            "color:rgba(0,0,0,200);"
                            "}"
                        );
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            bt->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(0);
        }
    }
}
void setTableR(QWidget* a){
    for(int i=0;i<19;i++) {
        for(int j=0;j<20;j++) {
            QPushButton *bt =new QPushButton(a);
            bt->setGeometry(i*70,j*40,50,35);
            bt->setText(QString::asprintf("%d",i*20+j));
            bt->setStyleSheet(
                        "QPushButton{"
                            "text-align: left;"
                            "background-color:rgba(174,221,129,200);"
                            "border-style:outset;"
                            "border-width:2px;"
                            "border-radius:2px;"
                            "border-color:rgba(139,69,19, 200);"
                            "font:bold 20px;"
                            "color:rgba(54,37,17,200);"
                            "padding:6px;"
                            "}"
                        );
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            bt->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(0);
            if(i==0) bt->setText(QString::asprintf("%d",j));
        }
    }
}*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QFrame *f = new QFrame(&w);
    f->setStyleSheet("QFrame{"
                     "border-radius:10px;"
                     "border:2px solid #bdb2ff;"
                     "}");
    f->setGeometry(30,30,620,350);
    f->show();
    w.setTable(f,4,5);
    w.myf=f;
    QFrame *f1 = new QFrame(&w);
    f1->setStyleSheet("QFrame{"
                       "border:2px solid #bdb2ff;"
                       "border-radius:10px;"
                       "}");
    f1->setGeometry(30,400,620,210);
    f1->show();
    w.setTable(f1,2,10);
    w.myf1=f1;


    w.a=new adj();
    w.setTableR(w.a);

    w.show();
    return a.exec();
}
