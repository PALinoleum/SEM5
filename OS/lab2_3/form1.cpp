#include "form1.h"
#include "ui_form1.h"

Form1::Form1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}

QTableWidget* Form1::getThTable(){
    return ui->th_table;
}

QTableWidget* Form1::getModTable(){
    return ui->mod_table;
}
