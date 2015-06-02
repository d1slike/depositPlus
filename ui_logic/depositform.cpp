#include "depositform.h"
#include "ui_depositform.h"

DepositForm::DepositForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepositForm)
{
    ui->setupUi(this);
    QRegExp sum_exp("[0-9]{1,9}");
    QRegExp days_exp("[1-9]{1,4}");
    QRegExpValidator* validator = new QRegExpValidator(sum_exp, this);
    ui->start_sum->setValidator(validator);
    ui->month_add->setValidator(validator);
    ui->day_count->setValidator(new QRegExpValidator(days_exp, this));
}

DepositForm::~DepositForm()
{
    delete ui;
}

void DepositForm::validFields()
{
    bool ok = false;
    ok = ui->start_sum->hasAcceptableInput() && ui->day_count->hasAcceptableInput();
    if(ui->month_add->isEnabled())
        ok = ui->month_add->hasAcceptableInput();

}