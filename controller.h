#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QPalette>
#include "calc_logic/templates/depositholder.h"
#include "calc_logic/model/deposit.h"
#include "calc_logic/model/profitresult.h"
#include "ui_logic/depositform.h"
#include "ui_logic/mainwindow.h"
#include "utils/array.h"
#include "ui_depositform.h"
#include "ui_mainwindow.h"
class Controller : QObject
{
    Q_OBJECT

    //QPalette DEFAULT;
    //QPalette MAX;

    Deposit* dep;
    DepositHolder* holder;
    DepositForm* dep_win;
    MainWindow* main_win;

    bool blocked; //флаг запрета на открытие еще одной формы расчета вкладов
    //Array<ProfitResult, 3> results;
    //Array<bool, 3> results_field_free;
    int currentResult; //тукущее поле заполнения
    //int results_count;

    bool valid_start_sum;
    bool valid_open_date;
    bool valid_close_date;
    bool valid_days_count;
    bool valid_supplement_sum;

    void validAllConditions();
    void newDepositCalculate();
    void enableAll(bool isTemp);


public:
    Controller(MainWindow* main, DepositHolder* holder);


private slots:
    void _1AddButtonAction();//
    void _2AddButtonAction();//
    void _3AddButtonAction();//

    void _1ClearButtonAction();//
    void _2ClearButtonAction();//
    void _3ClearButtonAction();// можно было обойтись двумя слотами

    void onClosingDepWindow();

    void setEarlyClosingDateFlag();
    void setCapitalisationFlag();
    void setSupplementationFlag();
    void setValute();
    void setTemplate();

    void validStartSum();
    void validDateOpen();
    void validDaysCount();
    void validSupplementSum();
    void validEarlyCloseDate();

    void calculate();

};

#endif // CONTROLLER_H
