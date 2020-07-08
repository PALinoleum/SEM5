#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    showInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showInfo(){
    //Идентификатор текущего процесса
    DWORD id = GetCurrentProcessId();
    ui->ID_line->setText(QString::number(id));
    //Псевдодескрпитор текущего процесса
    HANDLE cp = GetCurrentProcess();
    ui->p_handle_line->setText("0x" + QString::number((long long)(cp), 16));
    //Дескриптор псевдодескриптора по псевдодескриптору псевдодескриптора дескриптора
    HANDLE handle;
    DuplicateHandle(cp, cp, cp, &handle, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, NULL);
    ui->d_handle_line->setText("0x" + QString::number((long long)(handle), 16));
    //Копия дескриптора текущего процесса
    HANDLE op = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, id);
    ui->op_handle_line->setText("0x" + QString::number((long long)(op), 16));
    //Закрытие дескриптора по псевдодескриптору
    bool fd = CloseHandle(handle);
    ui->close_d_handle_line->setText("0x" + QString::number((long long)(handle), 16) + " - " + QString(fd==false?"false":"true"));
    if (!fd) QMessageBox::warning(this, "Ошибка", "Ошибка закрытия дескриптора по псевдодескриптору");
    //Закрытие копии дескриптора текущего процесса
    bool fo = CloseHandle(op);
    ui->close_op_handle_line->setText("0x" + QString::number((long long)(handle), 16) + " - " + QString(fo==false?"false":"true"));
    if (!fo) QMessageBox::warning(this, "Ошибка", "Ошибка закрытия копии дескриптора");
}
