#ifndef FORM1_H
#define FORM1_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class Form1;
}

class Form1 : public QDialog
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = nullptr);
    ~Form1();
    QTableWidget* getThTable();
    QTableWidget* getModTable();

private:
    Ui::Form1 *ui;
};

#endif // FORM1_H
