#include "controller.h"
#include <QDate>
Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    this->main_win = main;
    this->holder = holder;
    this->dep = 0;
    this->dep_form = 0;
    valid_start_sum = valid_date_open = valid_days_count = valid_add_month_sum = valid_date_remove = false;
}


void Controller::validStartSum()
{
    valid_start_sum = dep_form->ui->day_count->hasAcceptableInput() && dep->validSum();
}

void Controller::validDateOpen()
{
    QDate qd = dep_form->ui->start_date->date();
    Date d(qd.day(), qd.month(), qd.year());

}

void Controller::validDaysCount()
{

}

void Controller::validAddMonthSum()
{

}

void Controller::validDateRemove()
{

}

void Controller::validAllConditions()
{
    bool b = valid_start_sum && valid_date_open && valid_days_count && valid_add_month_sum;
    if(ui->remove_date->isEnabled())
        b = b && valid_date_remove;
    if(b)
        ui->do_calc_button->setEnabled(true);

}
