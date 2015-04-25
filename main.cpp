#include "depositplus.h"
#include <QApplication>
#include "utils/array.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DepositPlus w;
    w.show();

    return a.exec();
}
