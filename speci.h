#ifndef SPECI_H
#define SPECI_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>
namespace Ui {
class Speci;
}

class Speci : public QTableView
{
    Q_OBJECT

public:
    explicit Speci(QWidget *parent = 0);
    QStandardItemModel* model;
    ~Speci();

private:
    Ui::Speci *ui;
};

#endif // SPECI_H
