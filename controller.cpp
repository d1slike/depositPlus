#include "controller.h"
#include <QDate>

#define dep_ui dep_win->ui
#define main_ui main_win->ui

Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    main_win = main;
    this->holder = holder;
    dep = 0;
    dep_win = 0;
    blocked = false;
    DEFAULT = main_win->ui->d_result_1->palette();
    MAX = DEFAULT;
    MAX.setColor(QPalette::Window, QColor(255, 43, 43));
    for(int i = 0; i < 3; i++)
        results_field_free[i] = true;
    currentResult = -1;
    valid_start_sum = valid_open_date = valid_days_count = valid_supplement_sum = valid_close_date = false;
    connect(main_ui->add_1, SIGNAL(pressed()), this, SLOT(_1AddButtonAction()));
    connect(main_ui->add_2, SIGNAL(pressed()), this, SLOT(_2AddButtonAction()));
    connect(main_ui->add_3, SIGNAL(pressed()), this, SLOT(_3AddButtonAction()));

    connect(main_win->ui->clear_1, SIGNAL(pressed()), this, SLOT(_1ClearButtonAction()));
    connect(main_win->ui->clear_2, SIGNAL(pressed()), this, SLOT(_2ClearButtonAction()));
    connect(main_win->ui->clear_3, SIGNAL(pressed()), this, SLOT(_3ClearButtonAction()));

}

void Controller::_1AddButtonAction()
{
    if(blocked)
        return;
    currentResult = 0;
    newDepositCalculate();
}

void Controller::_2AddButtonAction()
{
    if(blocked)
        return;
    currentResult = 1;

    newDepositCalculate();
}

void Controller::_3AddButtonAction()
{
    if(blocked)
        return;
    currentResult = 2;
    newDepositCalculate();
}

void Controller::_1ClearButtonAction()
{
    results_field_free[currentResult] = true;
    currentResult = -1;
    main_win->ui->add_1->setEnabled(true);
     main_win->ui->clear_1->setEnabled(false);
    main_win->ui->d_result_1->setPlainText("");
    main_win->ui->d_result_1->setEnabled(false);

}

void Controller::_2ClearButtonAction()
{
    results_field_free[currentResult] = true;
    currentResult = -1;
    main_win->ui->add_2->setEnabled(true);
    main_win->ui->clear_2->setEnabled(false);
    main_win->ui->d_result_2->setPlainText("");
    main_win->ui->d_result_2->setEnabled(false);
}

void Controller::_3ClearButtonAction()
{
    results_field_free[currentResult] = true;
    currentResult = -1;
    main_win->ui->add_3->setEnabled(true);
    main_win->ui->clear_3->setEnabled(false);
    main_win->ui->d_result_3->setPlainText("");
    main_win->ui->d_result_3->setEnabled(false);
}


void Controller::newDepositCalculate()
{
    dep = new Deposit;
    dep_win = new DepositForm(main_win);
    valid_close_date = valid_days_count = valid_open_date = valid_start_sum = valid_supplement_sum = false;
    connect(dep_win, SIGNAL(finished(int)), this, SLOT(onClosingDepWindow()));
    connect(dep_win->ui->start_sum, SIGNAL(textChanged(QString)), this, SLOT(validStartSum()));
    connect(dep_win->ui->start_date, SIGNAL(dateChanged(QDate)), this, SLOT(validDateOpen()));
    connect(dep_win->ui->day_count, SIGNAL(textChanged(QString)), this, SLOT(validDaysCount()));
    connect(dep_win->ui->deposit_list, SIGNAL(currentIndexChanged(int)), this, SLOT(setTemplate()));
    connect(dep_win->ui->valute_list, SIGNAL(currentIndexChanged(int)), this, SLOT(setValute()));
    connect(dep_win->ui->supplement_flag, SIGNAL(clicked(bool)), this, SLOT(setSupplementationFlag()));
    connect(dep_win->ui->supplement_sum, SIGNAL(textChanged(QString)), this, SLOT(validSupplementSum()));
    connect(dep_win->ui->capitalisation_flag, SIGNAL(clicked(bool)), this, SLOT(setCapitalisationFlag()));
    connect(dep_win->ui->early_close_date, SIGNAL(dateChanged(QDate)), this, SLOT(validEarlyCloseDate()));
    connect(dep_win->ui->early_close_date_flag, SIGNAL(clicked(bool)), this, SLOT(setEarlyClosingDateFlag()));
    connect(dep_win->ui->do_calc_button, SIGNAL(pressed()), this, SLOT(calculate()));

    for(int i = 0; i < holder->getCount(); i++)
        dep_ui->deposit_list->addItem(holder->getName(i));
    blocked = true;
    dep_ui->valute_list->currentIndexChanged(0);
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
    bool b = dep_win->ui->supplement_flag->isChecked();
    dep_win->ui->supplement_sum->setEnabled(b);
    dep->setSupplementation(b);
}

void Controller::setValute()
{
    switch(dep_win->ui->valute_list->currentIndex())
    {
    case 0:
        dep->getStartSum().setValute(RUB);
        dep->getSupplementSum().setValute(RUB);
        break;
    case 1:
        dep->getStartSum().setValute(USD);
        dep->getSupplementSum().setValute(USD);
        break;
    case 2:
        dep->getStartSum().setValute(EUR);
        dep->getSupplementSum().setValute(EUR);
        break;
    }
    validStartSum();
}

void Controller::setTemplate()
{
    dep->setTemplate(holder->getTempl(dep_win->ui->deposit_list->currentIndex()));
    enableAll();
}

void Controller::validStartSum()
{
    valid_start_sum = dep_win->ui->start_sum->hasAcceptableInput();
    if(valid_start_sum)
        dep->getStartSum().setValue(dep_ui->start_sum->text().toInt());
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
    valid_days_count = valid_days_count && dep->validDayCount();
    //valid_close_date = valid_days_count;
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
    if(dep_ui->early_close_date_flag->isChecked())
    {
        Date d(dep_win->ui->early_close_date->date());
        valid_close_date = d.validMe();
        if(valid_close_date)
            dep->setCloseDate(d);
        validAllConditions();
    }

}

void Controller::calculate()
{

    results[currentResult] = dep->getProfit();
    results_field_free[currentResult] = false;
    switch (currentResult) {
    case 0:
        main_win->ui->d_result_1->setEnabled(true);
        main_win->ui->add_1->setEnabled(false);
        main_win->ui->clear_1->setEnabled(true);
        main_win->ui->d_result_1->setPlainText(results[currentResult].toString());
        break;
    case 1:
        main_win->ui->d_result_2->setEnabled(true);
        main_win->ui->add_2->setEnabled(false);
        main_win->ui->clear_2->setEnabled(true);
        main_win->ui->d_result_2->setPlainText(results[currentResult].toString());
        break;
    case 2:
        main_win->ui->d_result_3->setEnabled(true);
        main_win->ui->add_3->setEnabled(false);
        main_win->ui->clear_3->setEnabled(true);
        main_win->ui->d_result_3->setPlainText(results[currentResult].toString());
        break;
    default:
        break;
    }
    main_win->ui->d_result_1->setPalette(DEFAULT);
    main_win->ui->d_result_2->setPalette(DEFAULT);
    main_win->ui->d_result_3->setPalette(DEFAULT);
    ProfitResult max;
    for(int i = 0; i < 3; i++)
    {
        if(results_field_free[i])
            continue;
        else
            max = results[i];
    }
    int max_field = 0;
    for(int i = 0; i < 3; i++)
        if(results[i] > max)
        {
            max = results[i];
            max_field = i;
        }
    switch(max_field)
    {
    case 1:
        main_win->ui->d_result_1->setPalette(MAX);
        break;
    case 2:
        main_win->ui->d_result_1->setPalette(MAX);
        break;
    case 3:
        main_win->ui->d_result_1->setPalette(MAX);
        break;
    }
    dep_win->close();
}

inline void Controller::validAllConditions()
{

    bool b = valid_start_sum && valid_open_date && valid_days_count;
    if(dep_ui->supplement_flag->isChecked())
        b = b && valid_supplement_sum;
    if(dep_ui->early_close_date_flag->isChecked())
        b = b && valid_close_date;
    dep_win->ui->do_calc_button->setEnabled(b);

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
