#include "controller.h"
#include <QDate>
Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    this->main_win = main;
    this->holder = holder;
    this->dep = 0;
    this->dep_form = 0;
    blocked = false;
    valid_start_sum = valid_date_open = valid_days_count = valid_add_month_sum = valid_date_remove = false;
    connect(main_win->ui->add_1, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));
    connect(main_win->ui->add_2, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));
    connect(main_win->ui->add_3, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));

}

void Controller::newDepositCalculate()
{
    if(blocked)
        return;
    dep = new Deposit;
    dep_form = new DepositForm();
    connect(dep_form, SIGNAL(finished(int)), this, SLOT(onDestroyDepForm()));
    connect(dep_form->ui->start_sum, SIGNAL(textChanged(QString)), this, SLOT(validStartSum()));
    connect(dep_form->ui->start_date, SIGNAL(dateChanged(QDate)), this, SLOT(validDateOpen()));
    connect(dep_form->ui->day_count, SIGNAL(textChanged(QString)), this, SLOT(validDaysCount()));
    connect(dep_form->ui->deposit_list, SIGNAL(editTextChanged(QString)), this, SLOT(setTemplate()));
    connect(dep_form->ui->valute_list, SIGNAL(editTextChanged(QString)), this, SLOT(setValute()));
    connect(dep_form->ui->month_add, SIGNAL(textChanged(QString)), this, SLOT(validAddMonthSum()));
    connect(dep_form->ui->is_cap_check, SIGNAL(clicked(bool)), this, SLOT(setCap()));
    connect(dep_form->ui->remove_date, SIGNAL(dateChanged(QDate)), this, SLOT(validDateRemove()));
    connect(dep_form->ui->remove_date_check, SIGNAL(clicked(bool)), this, SLOT(setRemoveDate()));

    dep_form->ui->deposit_list->addItems(holder->getNames());
    QStringList list;
    list.append("RUB");
    list.append("USD");
    list.append("EUR");
    dep_form->ui->valute_list->addItems(list);
    blocked = true;
    dep_form->show();

}

void Controller::onDestroyDepForm()
{
    delete dep;
    dep_form->deleteLater();
    blocked = false;
}

void Controller::setRemoveDate()
{
    bool b = dep_form->ui->remove_date_check->isChecked();
    dep_form->ui->remove_date->setEnabled(b);
    dep->setRemove(b);
}

void Controller::setCap()
{
    dep->setCap(dep_form->ui->is_cap_check->isChecked());
}

void Controller::setValute()
{
    Valute v = (Valute) dep_form->ui->valute_list->currentIndex();
    dep->getSum().setValute(v);
    dep->getAddSum().setValute(v);
}

void Controller::setTemplate()
{
    dep->setTemplate(holder->getTemplByName(dep_form->ui->deposit_list->currentText()));
    enableAll();
}

void Controller::validStartSum()
{
    valid_start_sum = dep_form->ui->day_count->hasAcceptableInput();
    if(valid_start_sum)
        dep->getSum().setValue(dep_form->ui->start_sum->text().toInt());
    valid_start_sum = valid_start_sum && dep->validSum();
    validAllConditions();
}

void Controller::validDateOpen()
{
    Date d(dep_form->ui->start_date->date());
    valid_date_open = d.checkMe();
    if(valid_date_open)
        dep->setOpenDate(d);
    validAllConditions();
}

void Controller::validDaysCount()
{
    valid_days_count = dep_form->ui->day_count->hasAcceptableInput();
    if(valid_days_count)
    {
            dep->setDayCount(dep_form->ui->day_count->text().toInt());
    }
    valid_days_count = valid_days_count && dep->validDate();
    validAllConditions();
}

void Controller::validAddMonthSum()
{
    valid_add_month_sum = dep_form->ui->month_add->hasAcceptableInput();
    if(valid_add_month_sum)
        dep->getAddSum().setValue(dep_form->ui->month_add->text().toInt());
    validAllConditions();
}

void Controller::validDateRemove()
{
    if(dep_form->ui->remove_date->isEnabled())
    {
        Date d(dep_form->ui->remove_date->date());
        if(valid_date_remove = d.checkMe())
        {
            dep->setCloseDate(d);
            dep->setDayCount();
        }
    }
    valid_date_remove = valid_date_remove && dep->validDate();
    validAllConditions();

}

void Controller::validAllConditions()
{
    bool b = valid_start_sum && valid_date_open && valid_days_count && valid_add_month_sum && valid_date_remove;
    if(b)
        dep_form->ui->do_calc_button->setEnabled(true);

}

void Controller::enableAll()
{
    Ui::DepositForm* ui = dep_form->ui;
    ui->day_count->setEnabled(true);
    ui->is_cap_check->setEnabled(true);
    ui->valute_list->setEnabled(true);
    ui->start_sum->setEnabled(true);
    ui->start_date->setEnabled(true);
    ui->month_add->setEnabled(true);
    ui->remove_date_check->setEnabled(true);
}
