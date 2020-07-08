#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    QTableWidget* getTable();

private:
    Ui::Form *ui;
};

#endif // FORM_H
