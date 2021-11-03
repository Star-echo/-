#include "widget.h"
#include "ui_widget.h"


using namespace std;
int tempC;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(10);
    ifUp=0,ifE=0,ifT=0,ifC=0,theAN=0,theVN=0;
    ui->setupUi(this);
    G_exam.ifO = 0;//首先假定无环
    G_exam.vexNum=4,G_exam.arcNum=5;
    for (int i = 0; i < G_exam.vexNum; i++) {
        G_exam.vexs[i].data = i;//点的名字
        //初始化邻接矩阵
        for (int j = 0; j < G_exam.vexNum; j++) for (int i = 0; i < G_exam.vexNum; i++) {
            if (i == j) G_exam.arcs[i][j].weight = 0;
            else G_exam.arcs[i][j].weight = -1;
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
void Widget:: gc(int n,int &x,int &y)
{
    int i;
    int sq=(int)sqrt(n);
    if(!(n%sq)) x=sq,y=n/sq;
    else {
        int flag;
        int low=pow(sq,2);
        int high=pow(sq+1,2);
        if((n-low)>=(high-n)) flag=sq+1;
        else flag = sq;
        for(i=flag-1;i>0;i--) if(!(n%i)) break;
        x=i;
        y=n/i;
    }
}

void Widget::setVex(QFrame*f,int vexNum,int ifTo){
    int x,y,si,j;
    if(vexNum>13&&ifTo) si=58;
    else si=88;
    int sq=(int)sqrt(vexNum);
    if(vexNum!=sq*sq) sq++;
    x=sq,y=sq;
    if(ifTo) {
        if(vexNum%2) y=2,x=(vexNum+1)/2;
        else y=2,x=vexNum/2;
    }
    for(int i=0;i<x;i++) {
        for(j=0;j<y;j++) {
            if(i*y+j==vexNum) break;
            DP *bt = (DP *)(f->children().at(i*y+j));
            bt->setEnabled(true);
            bt->setGeometry(i*si+20, j*si+20, 38, 38);
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
            bt->setText(QString::asprintf("%d",i*y+j));
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            bt->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(1);
        }
        if(i*y+j==vexNum) break;
    }
    for(int i=vexNum;i<20;i++) {
        DP *bt = (DP *)(f->children().at(i));
        bt->setText(QString::asprintf("%d",i));
        bt->setEnabled(false);
        bt->setStyleSheet("");
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        bt->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0);
    }
    for(int i=0;i<20-vexNum;i++) {
        DP *bt2 = (DP *)(f->children().at(i));
        if(bt2->text().toInt()<vexNum) {
            bt2->raise();
            i--;
        }
    }
}
void Widget::ResetVex(QFrame*f){
    DP *bt;
    for(int i=0;i<4;i++) {
        for(int j=0;j<5;j++) {
            bt = (DP *)(f->children().at(i*5+j));
            bt->setEnabled(false);
            bt->setGeometry(i*38, j*38, 38, 38);
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            bt->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(0);
        }
    }
}
void Widget::on_ensure1_clicked()
{
    G.vexNum=ui->vexNum->currentIndex()+1;
    G.arcNum=ui->arcNum->currentIndex()+1;
    G.ifO = 0;//首先假定无环
    for (int i = 0; i < G.vexNum; i++) {
        G.vexs[i].data = i;//点的名字
        //初始化邻接矩阵
        for (int j = 0; j < G.vexNum; j++) for (int i = 0; i < G.vexNum; i++) {
            if (i == j) G.arcs[i][j].weight = 0;
            else G.arcs[i][j].weight = -1;
        }
    }
    ifUp=1;
    theAN=G.arcNum;
    theVN=G.vexNum;
    setVex(myf,theVN,0);

}
void Widget::paintEvent(QPaintEvent *)
{
    // QString转QColor
    QString color_str = "FFFFFC";
    QColor color2(color_str.toUInt(NULL,16));
    QPainter painter(this);
    painter.setBrush(color2);
    painter.drawRect(this->rect());

    if(ifUp||ifE){
        float x1,x2,y1,y2,new_x1,new_y1,new_x2,new_y2,dx,dy,l=10,a=0.5;
        int delta=49,deltax=419;
        double alpha;
        QPainter painter(this);
        QFont font1("宋体",11,QFont::Bold,true);
        painter.setFont(font1);
        painter.setPen(QPen(QColor(139,69,19, 200),2));
        count=0;
        for(int i=0;i<theVN;i++){
            for(int j=0;j<theVN;j++){
                if((G.arcs[i][j].weight != 0 && G.arcs[i][j].weight != -1&&ifUp)||(G_exam.arcs[i][j].weight != 0 && G_exam.arcs[i][j].weight != -1&&ifE)){
                    count++;
                    for(int t=20-(theVN);t<20;t++){
                        DP *bt = (DP *)(myf->children().at(t));
                        if(bt->text().toInt()==i) x1 =bt->pos().x()+delta,y1 = bt->pos().y()+delta;
                        if(bt->text().toInt()==j) x2 =bt->pos().x()+delta,y2 = bt->pos().y()+delta;
                    }
                    alpha = atan2(y2-y1,x2-x1);//计算线段的夹角
                    new_x1= x2-l*cos(alpha-a),new_y1= y2-l*sin(alpha-a);
                    new_x2= x2-l*cos(alpha+a),new_y2= y2-l*sin(alpha+a);
                    dx=19*cos(alpha),dy=19*sin(alpha);
                    painter.drawLine(x1+dx,y1+dy,x2-dx,y2-dy);//画直线
                    painter.drawLine(new_x1-dx,new_y1-dy,x2-dx,y2-dy);//画直线
                    painter.drawLine(new_x2-dx,new_y2-dy,x2-dx,y2-dy);//画直线

                    painter.drawText((x1+x2)/2,(y1+y2)/2,"e"+QString::asprintf("%d",count)+":"+QString::asprintf("%d",G.arcs[i][j].weight*ifUp+G_exam.arcs[i][j].weight*ifE));
                }
            }
        }
        if(ifT){
            dx=10,dy=10;
            for(int i=0;i<theVN-1;i++){
                for(int t=20-(theVN)-1;t<20;t++){
                    DP *btt = (DP *)(myf1->children().at(t));
                    if(ifE){
                        if(btt->text().toInt()==(G_exam.topoVexs[i])){
                            x1 =btt->pos().x()+delta,y1 = btt->pos().y()+deltax;
                            painter.drawText(x1+2*dx,y1-2*dy,QString::asprintf("in: %d",G_exam.indegreeC[i]));
                        }

                        if(btt->text().toInt()==(G_exam.topoVexs[i+1]))

                            x2 =btt->pos().x()+delta,y2 = btt->pos().y()+deltax;

                        if(i==theVN-2)  painter.drawText(x2+2*dx,y2-2*dy,QString::asprintf("in: %d",G_exam.indegreeC[i+1]));
                    }
                    else if(ifUp){
                        if(btt->text().toInt()==(G.topoVexs[i])){
                            x1 =btt->pos().x()+delta,y1 = btt->pos().y()+deltax;
                            painter.drawText(x1+2*dx,y1-2*dy,QString::asprintf("in: %d",G.indegreeC[i]));
                        }

                        if(btt->text().toInt()==(G.topoVexs[i+1]))
                            x2 =btt->pos().x()+delta,y2 = btt->pos().y()+deltax;

                        if(i==theVN-2)  painter.drawText(x2+2*dx,y2-2*dy,QString::asprintf("in: %d",G.indegreeC[i+1]));
                    }
                }

                alpha = atan2(y2-y1,x2-x1);//计算线段的夹角
                new_x1= x2-l*cos(alpha-a),new_y1= y2-l*sin(alpha-a);
                new_x2= x2-l*cos(alpha+a),new_y2= y2-l*sin(alpha+a);
                dx=19*cos(alpha),dy=19*sin(alpha);
                painter.drawLine(x1+dx,y1+dy,x2-dx,y2-dy);//画直线
                painter.drawLine(new_x1-dx,new_y1-dy,x2-dx,y2-dy);//画直线
                painter.drawLine(new_x2-dx,new_y2-dy,x2-dx,y2-dy);//画直线

            }
        }
        if(ifC){
            for(int i=0;i<theVN;i++){
                for(int t=20-(theVN)-1;t<20;t++){
                    DP *btt1 = (DP *)(myf->children().at(t));
                    if(((ifE&&btt1->text().toInt()==G_exam.cPVexs[i]))||((btt1->text().toInt()==G.cPVexs[i])&&ifUp))
                    {
                        btt1->setStyleSheet(
                                    "QPushButton{"
                                        "background-color:#ffadad;"
                                        "border-style:outset;"
                                        "border-width:4px;"
                                        "border-radius:19px;"
                                        "border-color:rgba(255,255,255,30);"
                                        "font:bold 20px;"
                                        "color:rgba(54,37,17,200);"
                                        "padding:6px;"
                                        "}"
                                        "QPushButton:pressed{"
                                        "background-color:rgba(255,102,0,200);"
                                        "border-color:rgba(255,255,255,30);"
                                        "border-style:inset;"
                                        "color:rgba(0,0,0,100);"
                                        "}"
                                        "QPushButton:hover{"
                                        "background-color:rgba(255,102,0,100);"
                                        "border-color:rgba(255,255,255,200);"
                                        "color:rgba(0,0,0,200);"
                                        "}"
                                    );
                    }
                }
            }
        }
    }
}
void Widget::on_ensure2_clicked()
{
    update();
    tempC++;
    ui->ensure2->setToolTip("第"+QString::asprintf("%d",tempC)+"条边");
    if(tempC<=G.arcNum){
        G.arcs[ui->st->currentIndex()][ui->en->currentIndex()].weight = ui->w->text().toInt();
    if(tempC==G.arcNum) G.CreatDG(G);
    }
}

void Widget::on_example_clicked()
{
    theAN=5;
    theVN=4;
    setVex(myf,theVN,0);
    //setVex(myf1,theVN,1);
    G_exam.arcs[0][1].weight=4;
    G_exam.arcs[0][2].weight=3;
    G_exam.arcs[1][2].weight=2;
    G_exam.arcs[1][3].weight=6;
    G_exam.arcs[2][3].weight=4;
    ifE=1;
    G_exam.CreatDG(G_exam);
    update();
}

void Widget::on_tupo_clicked()
{
    setVex(myf1,theVN,1);
    ifT=1;
}

void Widget::on_cri_clicked()
{
    ifC=1;
}

void Widget::on_look_clicked()
{
    s=new Speci();

    s->model->setColumnCount(8);
    s->model->setHeaderData(0,Qt::Horizontal, "顶点");
    s->model->setHeaderData(1,Qt::Horizontal, "Ve");
    s->model->setHeaderData(2,Qt::Horizontal, "Vl");
    s->model->setHeaderData(3,Qt::Horizontal, " ");
    s->model->setHeaderData(4,Qt::Horizontal, "活动");
    s->model->setHeaderData(5,Qt::Horizontal, "E");
    s->model->setHeaderData(6,Qt::Horizontal, "L");
    s->model->setHeaderData(7,Qt::Horizontal, "L-E");

    s->model->setRowCount(theAN);
    int a=-1,b=-1;
    for(int i=0;i<theAN;i++){
        if(i<theVN) {
            s->model->setItem(i, 0, new QStandardItem("V"+QString::asprintf("%d",i)));
            a=ifE?G_exam.ve[i]:G.ve[i],b=ifE?G_exam.vl[i]:G.vl[i];
            s->model->setItem(i,1, new QStandardItem(QString::asprintf("%d",a)));
            s->model->setItem(i,2, new QStandardItem(QString::asprintf("%d",b)));
        }
        s->model->setItem(i,4, new QStandardItem("E"+QString::asprintf("%d",i)));
    }

    int i=0;
    for(int j=0;j<theVN;j++){
        for(int k=0;k<theVN;k++){
            if(G_exam.arcs[j][k].weight!=0&&G_exam.arcs[j][k].weight!=-1&&ifE){
                s->model->setItem(i,5, new QStandardItem(QString::asprintf("%d",G_exam.arcs[j][k].ee)));
                s->model->setItem(i,6, new QStandardItem(QString::asprintf("%d",G_exam.arcs[j][k].el)));
                s->model->setItem(i,7, new QStandardItem(QString::asprintf("%d",G_exam.arcs[j][k].el-G_exam.arcs[j][k].ee)));
                i++;
            }
            else if(G.arcs[j][k].weight!=0&&G.arcs[j][k].weight!=-1&&ifUp){
                s->model->setItem(i,5, new QStandardItem(QString::asprintf("%d",G.arcs[j][k].ee)));
                s->model->setItem(i,6, new QStandardItem(QString::asprintf("%d",G.arcs[j][k].el)));
                s->model->setItem(i,7, new QStandardItem(QString::asprintf("%d",G.arcs[j][k].el-G.arcs[j][k].ee)));
                i++;
            }
        }
    }
    s->setModel(s->model);
    s->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    s->show();
}

void Widget::on_adj_clicked()
{
    a->f->ifA=1;
    a->f->tg=ifUp?G:G_exam;
    a->show();

}

void Widget::on_reset_clicked()
{
    if(ifE){
        ifUp=0,ifE=0,ifT=0,ifC=0,theAN=0,theVN=0;
        ResetVex(myf);
        ResetVex(myf1);
        setTableR(a);
    }
    else if(ifUp){
        ifUp=0,ifE=0,ifT=0,ifC=0,theAN=0,theVN=0;
        ResetVex(myf);
        ResetVex(myf1);
        setTableR(a);
        MyGraph G_new;
        G=G_new;
    }
}

void  Widget::setTable(QFrame*f,int x,int y){
    for(int j=0;j<x;j++) {
        for(int k=0;k<y;k++) {
            DP *bt = new DP(f);
            bt->setGeometry(j*88, k*88, 38, 38);
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
void  Widget::setTableR(QWidget* a){
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
}
