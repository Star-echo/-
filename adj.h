#ifndef ADJ_H
#define ADJ_H

#include "pf.h"
namespace Ui {
class adj;
}

class adj : public QWidget
{
    Q_OBJECT

public:
    explicit adj(QWidget *parent = 0);
    //int ifA;
    pf* f;
    //MyGraph tg;
    ~adj();

protected:


private:
    Ui::adj *ui;
};

#endif // ADJ_H
