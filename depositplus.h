#ifndef DEPOSITPLUS_H
#define DEPOSITPLUS_H

#include <QMainWindow>

namespace Ui {
class DepositPlus;
}

class DepositPlus : public QMainWindow
{
    Q_OBJECT

public:
    explicit DepositPlus(QWidget *parent = 0);
    ~DepositPlus();

private:
    Ui::DepositPlus *ui;
};

#endif // DEPOSITPLUS_H
