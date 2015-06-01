#include "depositform.h"
#include "ui_depositform.h"

DepositForm::DepositForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepositForm)
{
    ui->setupUi(this);
}

DepositForm::~DepositForm()
{
    delete ui;
}
