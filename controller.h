#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

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

    Deposit* dep;
    DepositHolder* holder;
    DepositForm* dep_win;
    MainWindow* main_win;
    Array<ProfitResult, 3> results;

    bool blocked; //флаг запрета на открытие еще одной формы расчета вкладов

    int currentResult; //тукущее поле заполнения
    int results_count;

    bool valid_start_sum;
    bool valid_open_date;
    bool valid_close_date;
    bool valid_days_count;
    bool valid_supplement_sum;

    inline void validAllConditions();
    void enableAll();


public:
    Controller(){};
    Controller(MainWindow* main, DepositHolder* holder);


private slots:
    void newDepositCalculate();

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

};

#endif // CONTROLLER_H
