#ifndef DEPOSITFORM_H
#define DEPOSITFORM_H

#include <QDialog>

namespace Ui {
class DepositForm;
}

class DepositForm : public QDialog
{
    Q_OBJECT

public:
    explicit DepositForm(QWidget *parent = 0);
    ~DepositForm();
    Ui::DepositForm* getUI()
    {
        return ui;
    }

public: // WTF
    Ui::DepositForm *ui;


};

#endif // DEPOSITFORM_H
