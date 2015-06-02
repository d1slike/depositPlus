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

private:
    Ui::DepositForm *ui;

private slots:
    void validFields();
};

#endif // DEPOSITFORM_H
