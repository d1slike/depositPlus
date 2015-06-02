#include "controller.h"

Controller::Controller(MainWindow* main, DepositHolder* holder)
{
    this->main_win = main;
    this->holder = holder;
    this->dep = 0;
    this->dep_form = 0;
}

