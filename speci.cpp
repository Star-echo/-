#include "speci.h"
#include "ui_speci.h"
Speci::Speci(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::Speci)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    this->horizontalHeader()->setObjectName("hHeader");
    this->verticalHeader()->setObjectName("vHeader");
    this->setStyleSheet(
                "QHeaderView{background:transparent;}"
                "QHeaderView#hHeader::section {"
                "font-size:22px;"
                "font-weight: bold;"
                "color:white;"
                "background:#0077b6;"
                "min-height:49px;"
                "min-width:49px;"
                "border:none;"
                "text-align:center;"
                "}"
                "QHeaderView#vHeader::section {"
                "font-size:22px;"
                "min-height:49px;"
                "color:black;"
                "background:white;"
                "border:none;"
                "}"
                "QTableView::item{"
                "background:#ade8f4;"
                "min-width:49px;"
                "}"
                "QTableView {"
                "background:#FFFFFF;"        // 整个表格控件 背景色
                "border:none;"               // 整个表格控件 边框
                "font-size:18px; "
                "}"
                );

}


Speci::~Speci()
{
    delete ui;
}
