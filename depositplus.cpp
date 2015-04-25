#include "depositplus.h"
#include "ui_depositplus.h"

DepositPlus::DepositPlus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DepositPlus)
{
    ui->setupUi(this);
}

DepositPlus::~DepositPlus()
{
    delete ui;
}
