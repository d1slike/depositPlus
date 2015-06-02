#include "ui_logic/mainwindow.h"
#include <QApplication>
#include "utils/array.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DepositHolder holder;
    MainWindow w;
    w.show();
    Controller c(&w, &holder);//управление целиком передается данному объекту

    return a.exec();
}
