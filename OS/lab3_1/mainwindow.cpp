#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("lab3_1");
    connect(ui->proc_name_line, SIGNAL(returnPressed()), this, SLOT(on_enter_button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::getProcIDByName(QString pr_name, DWORD *ID){
    DWORD len = 1000, size_needed, ID_arr[len];
    HANDLE h;
    WCHAR w_name[255];
    QString name;
    EnumProcesses(ID_arr, len*sizeof(DWORD), &size_needed);
    for (uint i = 0; i < size_needed/sizeof(DWORD); i++){
        h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ID_arr[i]);
        if (!GetModuleBaseNameW(h, NULL, w_name, 255)) name = "";
        else name = QString::fromWCharArray(w_name);
        if (name.toLower() == pr_name.toLower()){
            CloseHandle(h);
            if (ID != nullptr) *ID = ID_arr[i];
            return true;
        }
        CloseHandle(h);
    }
    return false;
}

bool MainWindow::waitStartProc(QString pr_name){
    if (getProcIDByName(pr_name, nullptr)) return true;
    ui->status_label->setStyleSheet("color: rgb(255, 128, 0)");
    ui->status_label->setText("Процесс " + pr_name + " не запущен");
    repaint();
    return false;
}

void MainWindow::waitEndProc(QString pr_name){
    if (!waitStartProc(pr_name)) return;
    DWORD waiting_time = 1000*ui->time_spin->value();
    ui->status_label->setStyleSheet("color: rgb(100, 100, 200)");
    ui->status_label->setText("Ожидание завершения процесса " + pr_name);
    repaint();
    DWORD pr_ID;
    getProcIDByName(pr_name, &pr_ID);
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | SYNCHRONIZE, false, pr_ID);
    QTime t; t.start();
    DWORD r_value = WaitForSingleObject(h, waiting_time);
    double time = (t.elapsed()/100)/10.0;
    CloseHandle(h);
    switch (r_value) {
        case WAIT_OBJECT_0:
            ui->status_label->setStyleSheet("color: rgb(100, 150, 100)");
            ui->status_label->setText("Процесс " + pr_name + " завершён");
            ui->time_label->setText("Время ожидания: " + QString::number(time) + " сек.");
            break;
        case WAIT_TIMEOUT:
            ui->status_label->setStyleSheet("color: rgb(255, 128, 0)");
            ui->status_label->setText("Истекло время ожидания завершения процесса " + pr_name);
            ui->time_label->setText("Время ожидания: " + QString::number(waiting_time/1000.0) + " сек.");
            break;
        case WAIT_FAILED:
            ui->status_label->setStyleSheet("color: rgb(255, 100, 100)");
            ui->status_label->setText("Произошла ошибка");
    }
    repaint();
}

void MainWindow::on_enter_button_clicked(){
    ui->status_label->clear();
    ui->time_label->clear();
    waitEndProc(ui->proc_name_line->text());
}
