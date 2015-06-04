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
    //DEFAULT = main_ui->d_result_1->palette();
    //MAX = DEFAULT;
    //MAX.setColor(QPalette::Window, QColor(255, 43, 43));
    //for(int i = 0; i < 3; i++)
      //  results_field_free[i] = true;
    currentResult = -1;
    valid_start_sum = valid_open_date = valid_days_count = valid_supplement_sum = valid_close_date = false;
    connect(main_ui->add_1, SIGNAL(pressed()), this, SLOT(_1AddButtonAction()));
    connect(main_ui->add_2, SIGNAL(pressed()), this, SLOT(_2AddButtonAction()));
    connect(main_ui->add_3, SIGNAL(pressed()), this, SLOT(_3AddButtonAction()));

    connect(main_ui->clear_1, SIGNAL(pressed()), this, SLOT(_1ClearButtonAction()));
    connect(main_ui->clear_2, SIGNAL(pressed()), this, SLOT(_2ClearButtonAction()));
    connect(main_ui->clear_3, SIGNAL(pressed()), this, SLOT(_3ClearButtonAction()));

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
    //results_field_free[currentResult] = true;
    currentResult = -1;
    main_ui->add_1->setEnabled(true);
    main_ui->clear_1->setEnabled(false);
    main_ui->d_result_1->setPlainText("");
    main_ui->d_result_1->setEnabled(false);

}

void Controller::_2ClearButtonAction()
{
    //results_field_free[currentResult] = true;
    currentResult = -1;
    main_ui->add_2->setEnabled(true);
    main_ui->clear_2->setEnabled(false);
    main_ui->d_result_2->setPlainText("");
    main_ui->d_result_2->setEnabled(false);
}

void Controller::_3ClearButtonAction()
{
    //results_field_free[currentResult] = true;
    currentResult = -1;
    main_ui->add_3->setEnabled(true);
    main_ui->clear_3->setEnabled(false);
    main_ui->d_result_3->setPlainText("");
    main_ui->d_result_3->setEnabled(false);
}


void Controller::newDepositCalculate()
{
    dep = new Deposit;
    dep_win = new DepositForm(main_win);
    valid_close_date = valid_days_count = valid_open_date = valid_start_sum = valid_supplement_sum = false;

    dep_ui->deposit_list->addItem("Выберите вклад");
    for(int i = 0; i < holder->getCount(); i++)
        dep_ui->deposit_list->addItem(holder->getName(i));
    dep_ui->deposit_list->setCurrentIndex(0);

    dep_ui->wrong_data->setText(constants::NOT_SUIT_DATE);
    dep_ui->wrong_data->setVisible(false);
    dep_ui->min_day_count->setVisible(false);
    dep_ui->min_start_sum->setVisible(false);

    connect(dep_win, SIGNAL(finished(int)), this, SLOT(onClosingDepWindow()));
    connect(dep_ui->start_sum, SIGNAL(textChanged(QString)), this, SLOT(validStartSum()));
    connect(dep_ui->open_date, SIGNAL(dateChanged(QDate)), this, SLOT(validDateOpen()));
    connect(dep_ui->day_count, SIGNAL(textChanged(QString)), this, SLOT(validDaysCount()));
    connect(dep_ui->deposit_list, SIGNAL(currentIndexChanged(int)), this, SLOT(setTemplate(int)));
    connect(dep_ui->valute_list, SIGNAL(currentIndexChanged(int)), this, SLOT(setValute()));
    connect(dep_ui->supplement_flag, SIGNAL(clicked(bool)), this, SLOT(setSupplementationFlag()));
    connect(dep_ui->supplement_sum, SIGNAL(textChanged(QString)), this, SLOT(validSupplementSum()));
    connect(dep_ui->capitalisation_flag, SIGNAL(clicked(bool)), this, SLOT(setCapitalisationFlag()));
    connect(dep_ui->early_close_date, SIGNAL(dateChanged(QDate)), this, SLOT(validEarlyCloseDate()));
    connect(dep_ui->early_close_date_flag, SIGNAL(clicked(bool)), this, SLOT(setEarlyClosingDateFlag()));
    connect(dep_ui->do_calc_button, SIGNAL(pressed()), this, SLOT(calculate()));

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
    bool b = dep_ui->early_close_date_flag->isChecked();
    dep_ui->early_close_date->setEnabled(b);
    dep->setEarlyClosing(b);
}

void Controller::setCapitalisationFlag()
{
    dep->setCapitalisation(dep_ui->capitalisation_flag->isChecked());
}

void Controller::setSupplementationFlag()
{
    bool b = dep_ui->supplement_flag->isChecked();
    dep_ui->supplement_sum->setEnabled(b);
    dep->setSupplementation(b);
}

void Controller::setValute()
{
    switch(dep_ui->valute_list->currentIndex())
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
    resetMinimalConditions();
    validStartSum();
}

void Controller::setTemplate(int index)
{
    bool isTemp = index > -1;

    if(isTemp)
    {
        dep->setTemplate(holder->getTempl(index));
        resetMinimalConditions();
    }
    enableAll(isTemp);
}

void Controller::validStartSum()
{
    valid_start_sum = dep_ui->start_sum->hasAcceptableInput();
    if(valid_start_sum)
        dep->getStartSum().setValue(dep_ui->start_sum->text().toInt());
    valid_start_sum = valid_start_sum && dep->validSum();
    dep_ui->min_start_sum->setVisible(!valid_start_sum);
    validAllConditions();
}

void Controller::validDateOpen()
{
    Date d(dep_ui->open_date->date());
    valid_open_date = d.validMe();
    if(valid_open_date)
        dep->setOpenDate(d);
    dep_ui->wrong_data->setVisible(!valid_open_date);
    validAllConditions();
}

void Controller::validDaysCount()
{
    valid_days_count = dep_ui->day_count->hasAcceptableInput();
    if(valid_days_count)
        dep->setDayCount(dep_ui->day_count->text().toInt());
    valid_days_count = valid_days_count && dep->validDayCount();
    dep_ui->min_day_count->setVisible(!valid_days_count);
    validAllConditions();
}

void Controller::validSupplementSum()
{
    valid_supplement_sum = dep_ui->supplement_sum->hasAcceptableInput();
    if(valid_supplement_sum)
        dep->getSupplementSum().setValue(dep_ui->supplement_sum->text().toInt());
    validAllConditions();
}

void Controller::validEarlyCloseDate()
{
    if(dep_ui->early_close_date_flag->isChecked())
    {
        Date d(dep_ui->early_close_date->date());
        valid_close_date = d.validMe();
        if(valid_close_date)
            dep->setEarlyCloseDate(d);
        validAllConditions();
    }

}

void Controller::calculate()
{

    ProfitResult pr = dep->getProfit();
    //results_field_free[currentResult] = false;
    switch (currentResult) {
    case 0:
        main_ui->d_result_1->setEnabled(true);
        main_ui->add_1->setEnabled(false);
        main_ui->clear_1->setEnabled(true);
        main_ui->d_result_1->setPlainText(pr.toString());
        break;
    case 1:
        main_ui->d_result_2->setEnabled(true);
        main_ui->add_2->setEnabled(false);
        main_ui->clear_2->setEnabled(true);
        main_ui->d_result_2->setPlainText(pr.toString());
        break;
    case 2:
        main_ui->d_result_3->setEnabled(true);
        main_ui->add_3->setEnabled(false);
        main_ui->clear_3->setEnabled(true);
        main_ui->d_result_3->setPlainText(pr.toString());
        break;
    default:
        break;
    }
    /*main_ui->d_result_1->setPalette(DEFAULT);
    main_ui->d_result_2->setPalette(DEFAULT);
    main_ui->d_result_3->setPalette(DEFAULT);
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
        main_ui->d_result_1->setPalette(MAX);
        break;
    case 2:
        main_ui->d_result_1->setPalette(MAX);
        break;
    case 3:
        main_ui->d_result_1->setPalette(MAX);
        break;
    }*/
    dep_win->close();
}

void Controller::validAllConditions()
{

    bool b = valid_start_sum && valid_open_date && valid_days_count;
    if(dep_ui->supplement_flag->isChecked())
        b = b && valid_supplement_sum;
    if(dep_ui->early_close_date_flag->isChecked())
        b = b && valid_close_date;
    dep_ui->do_calc_button->setEnabled(b);

}

void Controller::enableAll(bool isTemp)
{

    dep_ui->day_count->setEnabled(isTemp);
    dep_ui->capitalisation_flag->setEnabled(isTemp ? dep->getTempl().isCanCapitalize() : isTemp);
    dep_ui->valute_list->setEnabled(isTemp);
    dep_ui->start_sum->setEnabled(isTemp);
    dep_ui->open_date->setEnabled(isTemp);
    dep_ui->supplement_flag->setEnabled(isTemp ? dep->getTempl().isCanSupplement() : isTemp);
    dep_ui->early_close_date_flag->setEnabled(isTemp ? dep->getTempl().isCanEarlyClose() : isTemp);
}

void Controller::resetMinimalConditions()
{
    dep_ui->min_start_sum->setText(constants::NOT_SUIT_SUM.arg(QString::number(dep->getTempl().getRates().getMinSum(dep->getStartSum().getValute()))));//
    dep_ui->min_day_count->setText(constants::NOT_SUIT_DAY.arg(QString::number(dep->getTempl().getRates().getMinDay(dep->getStartSum()))));// TODO это провал

}
