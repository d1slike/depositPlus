#include "ui_logic/mainwindow.h"
#include <QApplication>
#include "utils/array.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
