#include "controller.h"
#include <QDate>
#include <QMessageBox>


#define dep_ui dep_win->ui
#define main_ui main_win->ui

Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    main_win = main;
    this->holder = holder;
    dep = 0;
    dep_win = 0;
    cur_row = 0;
    blocked = false;

    valid_start_sum = valid_open_date = valid_days_count = valid_supplement_sum = valid_close_date = false;
    connect(main_ui->add, SIGNAL(clicked(bool)), this, SLOT(newDepositCalculate()));
    connect(main_ui->delete_2, SIGNAL(clicked(bool)), this, SLOT(cleanTable()));

    connect(main_ui->action_add, SIGNAL(triggered(bool)), this, SLOT(newDepositCalculate()));
    connect(main_ui->action_del, SIGNAL(triggered(bool)), this, SLOT(cleanTable()));
    connect(main_ui->action_del_all, SIGNAL(triggered(bool)), this, SLOT(deleteAll()));
    connect(main_ui->about, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    connect(main_ui->team, SIGNAL(triggered(bool)), this, SLOT(showTeam()));

}

void Controller::cleanTable()
{
   QList<QTableWidgetSelectionRange> list = main_ui->table->selectedRanges();
   if(list.isEmpty())
       main_ui->table->removeRow(0);
   else
   for(int i = 0; i < list.size(); i++)
       for(int j = list[i].topRow(); j <= list[i].bottomRow(); j++)
           main_ui->table->removeRow(j);
}

void Controller::deleteAll()
{
    main_ui->table->selectAll();
    cleanTable();
}

void Controller::showAbout()
{
    QMessageBox::about(NULL, "О программе", "Калькулятор вкладов v0.5\n Исходный код доступен по https://github.com/d1slike/depositPlus");

}

void Controller::showTeam()
{
    QMessageBox::information(NULL, "Об авторах", "Комиссаров Я. В.(d1slike) \n Андрейцев О. (Shprechen)");
}



void Controller::newDepositCalculate()
{
    if(blocked)
        return;

    dep = new Deposit;
    dep_win = new DepositForm(main_win);
    valid_close_date = valid_days_count = valid_open_date = valid_start_sum = valid_supplement_sum = false;



    dep_ui->deposit_list->addItem("Выберите вклад");

    for(int i = 0; i < holder->getCurCount(); i++)
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
    connect(dep_ui->valute_list, SIGNAL(currentIndexChanged(int)), this, SLOT(setValute(int)));
    connect(dep_ui->supplement_flag, SIGNAL(clicked(bool)), this, SLOT(setSupplementationFlag()));
    connect(dep_ui->supplement_sum, SIGNAL(textChanged(QString)), this, SLOT(validSupplementSum()));
    connect(dep_ui->capitalisation_flag, SIGNAL(clicked(bool)), this, SLOT(setCapitalisationFlag()));
    connect(dep_ui->early_close_date, SIGNAL(dateChanged(QDate)), this, SLOT(validEarlyCloseDate()));
    connect(dep_ui->early_close_date_flag, SIGNAL(clicked(bool)), this, SLOT(setEarlyClosingDateFlag()));
    connect(dep_ui->do_calc_button, SIGNAL(pressed()), this, SLOT(calculate()));

    dep_ui->open_date->setDate(QDate::currentDate());
    dep_ui->early_close_date->setDate(QDate::currentDate());


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

void Controller::setValute(int index)
{
    switch(index)
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
    //validStartSum();
}

void Controller::setTemplate(int index)
{
    bool isTemp = index > 0;

    if(isTemp)
    {
        dep->setTemplate(holder->getTempl(index - 1));
        //resetMinimalConditions();
        dep_ui->valute_list->currentIndexChanged(0);
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
    cur_row = main_ui->table->rowCount();
    main_ui->table->setRowCount(cur_row + 1);
    main_ui->table->setItem(cur_row, 0, new QTableWidgetItem(pr.dep_name));
    main_ui->table->setItem(cur_row, 1, new QTableWidgetItem(pr.close_date));
    main_ui->table->setItem(cur_row, 2, new QTableWidgetItem(pr.rate));
    main_ui->table->setItem(cur_row, 3, new QTableWidgetItem(pr.sum));
    main_ui->table->setItem(cur_row, 4, new QTableWidgetItem(pr.profit));


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

    dep_ui->day_count_label->setEnabled(isTemp);
    dep_ui->label_start_sum->setEnabled(isTemp);
    dep_ui->early_close_date_label->setEnabled(isTemp);
    dep_ui->open_date_label->setEnabled(isTemp);
    dep_ui->valute_list_label->setEnabled(isTemp);
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
    dep_ui->min_start_sum->setText(constants::NOT_SUIT_SUM.arg(QString::number(dep->getCurrentMinSum())));
    dep_ui->min_day_count->setText(constants::NOT_SUIT_DAY.arg(QString::number(dep->getCurrentMinDays())));

}
