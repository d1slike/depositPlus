#include "controller.h"
#include <QDate>
Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    this->main_win = main;
    this->holder = holder;
    this->dep = 0;
    this->dep_win = 0;
    blocked = false;
    valid_start_sum = valid_open_date = valid_days_count = valid_supplement_sum = valid_close_date = false;
    connect(main_win->ui->add_1, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));
    connect(main_win->ui->add_2, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));
    connect(main_win->ui->add_3, SIGNAL(pressed()), this, SLOT(newDepositCalculate()));

}

void Controller::newDepositCalculate()
{
    if(blocked)
        return;
    dep = new Deposit;
    dep_win = new DepositForm();
    connect(dep_win, SIGNAL(finished(int)), this, SLOT(onClosingDepWindow()));
    connect(dep_win->ui->start_sum, SIGNAL(textChanged(QString)), this, SLOT(validStartSum()));
    connect(dep_win->ui->start_date, SIGNAL(dateChanged(QDate)), this, SLOT(validDateOpen()));
    connect(dep_win->ui->day_count, SIGNAL(textChanged(QString)), this, SLOT(validDaysCount()));
    connect(dep_win->ui->deposit_list, SIGNAL(editTextChanged(QString)), this, SLOT(setTemplate()));
    connect(dep_win->ui->valute_list, SIGNAL(editTextChanged(QString)), this, SLOT(setValute()));
    connect(dep_win->ui->supplement_flag, SIGNAL(clicked(bool)), this, SLOT(setSupplementationFlag()));
    connect(dep_win->ui->supplement_sum, SIGNAL(textChanged(QString)), this, SLOT(validSupplementSum()));
    connect(dep_win->ui->capitalisation_flag, SIGNAL(clicked(bool)), this, SLOT(setCapitalisationFlag()));
    connect(dep_win->ui->early_close_date, SIGNAL(dateChanged(QDate)), this, SLOT(validEarlyCloseDate()));
    connect(dep_win->ui->early_close_date_flag, SIGNAL(clicked(bool)), this, SLOT(setEarlyClosingDateFlag()));

    dep_win->ui->deposit_list->addItems(holder->getNames());
    blocked = true;
    dep_win->show();

}

void Controller::onClosingDepWindow()
{
    delete dep;
    dep_win->deleteLater();
    blocked = false;
}

void Controller::setEarlyClosingDateFlag()
{
    bool b = dep_win->ui->early_close_date_flag->isChecked();
    dep_win->ui->early_close_date->setEnabled(b);
    dep->setEarlyClosing(b);
}

void Controller::setCapitalisationFlag()
{
    dep->setCapitalisation(dep_win->ui->capitalisation_flag->isChecked());
}

void Controller::setSupplementationFlag()
{
    bool b = dep_win->ui->early_close_date_flag->isChecked();
    dep_win->ui->supplement_sum->setEnabled(b);
    dep->setSupplementation(b);
}

void Controller::setValute()
{
    Valute v = (Valute) dep_win->ui->valute_list->currentIndex();
    dep->getStartSum().setValute(v);
    dep->getSupplementSum().setValute(v);
}

void Controller::setTemplate()
{
    dep->setTemplate(holder->getTemplByName(dep_win->ui->deposit_list->currentText()));
    enableAll();
}

void Controller::validStartSum()
{
    valid_start_sum = dep_win->ui->day_count->hasAcceptableInput();
    if(valid_start_sum)
        dep->getStartSum().setValue(dep_win->ui->start_sum->text().toInt());
    valid_start_sum = valid_start_sum && dep->validSum();
    validAllConditions();
}

void Controller::validDateOpen()
{
    Date d(dep_win->ui->start_date->date());
    valid_open_date = d.validMe();
    if(valid_open_date)
        dep->setOpenDate(d);
    validAllConditions();
}

void Controller::validDaysCount()
{
    valid_days_count = dep_win->ui->day_count->hasAcceptableInput();
    if(valid_days_count)
    {
            dep->setDayCount(dep_win->ui->day_count->text().toInt());
    }
    valid_days_count = valid_days_count && dep->validDate();
    validAllConditions();
}

void Controller::validSupplementSum()
{
    valid_supplement_sum = dep_win->ui->supplement_sum->hasAcceptableInput();
    if(valid_supplement_sum)
        dep->getSupplementSum().setValue(dep_win->ui->supplement_sum->text().toInt());
    validAllConditions();
}

void Controller::validEarlyCloseDate()
{
    if(dep_win->ui->early_close_date->isEnabled())
    {
        Date d(dep_win->ui->early_close_date->date());
        if(valid_close_date = d.validMe())
        {
            dep->setCloseDate(d);
            dep->setDayCount();
        }
    }
    valid_close_date = valid_close_date && dep->validDate();
    validAllConditions();

}

inline void Controller::validAllConditions()
{

    dep_win->ui->do_calc_button->setEnabled(valid_start_sum && valid_open_date && valid_days_count && valid_supplement_sum && valid_close_date);

}

void Controller::enableAll()
{
    Ui::DepositForm* ui = dep_win->ui;
    ui->day_count->setEnabled(true);
    ui->capitalisation_flag->setEnabled(dep->getTempl().isCanCapitalize());
    ui->valute_list->setEnabled(true);
    ui->start_sum->setEnabled(true);
    ui->start_date->setEnabled(true);
    ui->supplement_flag->setEnabled(dep->getTempl().isCanSupplement());
    ui->early_close_date_flag->setEnabled(dep->getTempl().isCanEarlyClose());
}
