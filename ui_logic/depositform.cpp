#include "depositform.h"
#include "ui_depositform.h"

DepositForm::DepositForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepositForm)
{
    ui->setupUi(this);

    QRegExp sum_exp("[1-9]{1}[0-9]{0,9}");
    QRegExp days_exp("[1-9]{1}[0-9]{0,3}");
    QRegExpValidator* validator = new QRegExpValidator(sum_exp, this);
    ui->start_sum->setValidator(validator);
    ui->supplement_sum->setValidator(validator);
    ui->day_count->setValidator(new QRegExpValidator(days_exp, this));
    QStringList list;
    list.append("RUB");
    list.append("USD");
    list.append("EUR");
    ui->valute_list->addItems(list);

}



DepositForm::~DepositForm()
{
    delete ui;
}
