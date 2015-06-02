#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "calc_logic/templates/depositholder.h"
#include "calc_logic/model/deposit.h"
#include "calc_logic/model/profitresult.h"
#include "ui_logic/depositform.h"
#include "ui_logic/mainwindow.h"
#include "utils/array.h"

class Controller
{
    Deposit* dep;
    DepositForm* dep_form;
    DepositHolder* holder;
    MainWindow* main_win;
    Array<ProfitResult, 3> results;

public:
    Controller(){};
    Controller(MainWindow* main, DepositHolder* holder);
};

#endif // CONTROLLER_H
