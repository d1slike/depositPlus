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

namespace constants {
    static const QString NOT_SUIT_SUM = "<html><head/><body><p><span style=\"font-size:7pt; font-style:italic; color:#ff0000;\">* минимальная сумма : %1</span></p></body></html>";
    static const QString NOT_SUIT_DAY = "<html><head/><body><p><span style=\"font-size:7pt; font-style:italic; color:#ff0000;\">* мин. количество дней : %1</span></p></body></html>";
    static const QString NOT_SUIT_DATE ="<html><head/><body><p><span style=\"font-size:7pt; font-style:italic; color:#ff0000;\">* неверная дата</span></p></body></html>";
}



class Controller : QObject
{
    Q_OBJECT

    Deposit* dep;
    DepositHolder* holder;
    DepositForm* dep_win;
    MainWindow* main_win;

    int cur_row;

    bool blocked; //флаг запрета на открытие еще одной формы расчета вкладов

    bool valid_start_sum;
    bool valid_open_date;
    bool valid_close_date;
    bool valid_days_count;
    bool valid_supplement_sum;

    void validAllConditions();

    void enableAll(bool isTemp);
    void resetMinimalConditions();


public:
    Controller(MainWindow* main, DepositHolder* holder);


private slots:

    void cleanTable();
    void deleteAll();

    void showAbout();
    void showTeam();

    void onClosingDepWindow();
    void newDepositCalculate();
    void setEarlyClosingDateFlag();
    void setCapitalisationFlag();
    void setSupplementationFlag();
    void setValute(int);
    void setTemplate(int);

    void validStartSum();
    void validDateOpen();
    void validDaysCount();
    void validSupplementSum();
    void validEarlyCloseDate();

    void calculate();

};

#endif // CONTROLLER_H
