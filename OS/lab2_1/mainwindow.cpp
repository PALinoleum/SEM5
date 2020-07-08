#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    showBase();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showBase(){
    HMODULE handle_m = GetModuleHandleA(NULL);
    showInfoByHandle(handle_m);
}

bool MainWindow::showInfoByHandle(HMODULE h){
    WCHAR c_name[255];
    QString f_name(""), name("");
    bool f = true;
    int size = GetModuleFileName(h, c_name, 255);
    if (size > 0) {
        f_name = QString::fromWCharArray(c_name);
        name = f_name;
        name.remove(0, name.lastIndexOf("\\") + 1);
        f = false;
    }
    ui->descriptor_line->setText("0x" + QString::number((long long)h, 16));
    ui->module_line->setText(name);
    ui->full_module_line->setText(f_name);
    return f;
}

bool MainWindow::showInfoByName(QString name){
    HMODULE h;
    WCHAR wname[255], f_name[255];
    bool f = true;
    int size = name.toWCharArray(wname);
    wname[size] = 0;
    h = GetModuleHandle(wname);
    if (h != NULL){
        GetModuleFileName(h, f_name, 255);
        f = false;
    }else {
        name = "";
        f_name[0] = '\0';
    }
    ui->descriptor_line->setText("0x" + QString::number((long long)h, 16));
    ui->module_line->setText(name);
    ui->full_module_line->setText(QString::fromWCharArray(f_name));
    return f;
}

void MainWindow::on_descriptor_button_clicked(){
    long long h = ui->descriptor_line->text().toInt(0,16);
    if (showInfoByHandle(HMODULE(h)))
        QMessageBox::warning(this, "Ошибка", "Неверное значение");
}

void MainWindow::on_module_button_clicked(){
    QString name = ui->module_line->text();
    if (showInfoByName(name))
        QMessageBox::warning(this, "Ошибка", "Неверное значение");
}

void MainWindow::on_full_module_button_clicked(){
    QString name = ui->full_module_line->text();
    name.remove(0, name.lastIndexOf("\\") + 1);
    if (showInfoByName(name))
        QMessageBox::warning(this, "Ошибка", "Неверное значение");
}
