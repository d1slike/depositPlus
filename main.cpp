#include "ui_logic/mainform.h"
#include <QApplication>
#include "utils/array.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.show();

    return a.exec();
}
