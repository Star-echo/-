#ifndef WIDGET_H
#define WIDGET_H

#include "adj.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    MyGraph G;
    MyGraph G_exam;
    QFrame* myf;
    QFrame* myf1;
    int ifUp;
    int ifE;
    int ifT;
    int ifC;
    int theVN;
    int theAN;
    int count;

    void setTable(QFrame*f,int x,int y);
    void setTableR(QWidget*a);

    Speci *s;
    adj *a;

    void setTable();
    void setVex(QFrame*f,int vexNum,int ifTo);
    void ResetVex(QFrame*f);

    void gc(int n,int &x,int &y);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);

private slots:

    void on_ensure1_clicked();

    void on_ensure2_clicked();

    void on_example_clicked();

    void on_tupo_clicked();

    void on_cri_clicked();

    void on_look_clicked();

    void on_adj_clicked();

    void on_reset_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
