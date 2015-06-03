#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "calc_logic/templates/depositholder.h"
#include "calc_logic/model/deposit.h"
#include "calc_logic/model/profitresult.h"
#include "ui_logic/depositform.h"
#include "ui_logic/mainwindow.h"
#include "utils/array.h"
#include "ui_depositform.h"
#include "ui_mainwindow.h"
#include <QObject>
class Controller : QObject
{
    Q_OBJECT

    DepositForm* dep_form;
    Deposit* dep;
    DepositHolder* holder;
    MainWindow* main_win;
    Array<ProfitResult, 3> results;
    bool blocked; //флаг запрета на открытие еще одной формы расчета вкладов

    int currentResult; //тукущее поле заполнения

    bool valid_start_sum;
    bool valid_date_open;
    bool valid_days_count;
    bool valid_add_month_sum;
    bool valid_date_remove;

    void validAllConditions();
    void enableAll();


public:
    Controller(){};
    Controller(MainWindow* main, DepositHolder* holder);


private slots:
    void newDepositCalculate();

    void onDestroyDepForm();

    void setRemoveDate();
    void setCap();
    void setValute();
    void setTemplate();

    void validStartSum();
    void validDateOpen();
    void validDaysCount();
    void validAddMonthSum();
    void validDateRemove();

};

#endif // CONTROLLER_H
