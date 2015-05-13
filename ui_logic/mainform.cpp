#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
   // ui->fullMenu->setEnabled(false);
}

MainForm::~MainForm()
{
    delete ui;
}
