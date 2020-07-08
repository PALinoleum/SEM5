#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    showProcesesNT();
    showDrivers();
    showProcesses();
    tmr = new QTimer(this);
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTables()));
    tmr->start();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showProcesesNT(){
    // установка привелегий
    HANDLE curProcess = GetCurrentProcess();
    TOKEN_PRIVILEGES tp;
    LUID sdv;
    HANDLE hToken;
    OpenProcessToken(curProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_READ | TOKEN_QUERY, &hToken );
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sdv );
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = sdv;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof(tp), (PTOKEN_PRIVILEGES)NULL, 0 );

    ui->pr_table_NT->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QTableWidgetItem *item;
    DWORD len = 1000;
    DWORD size_needed, mod_size_needed;
    DWORD ID_arr[len];
    HANDLE h;
    HMODULE h_m;
    WCHAR w_name[255];
    QString name;
    EnumProcesses(ID_arr, len*sizeof(DWORD), &size_needed);
    ui->pr_table_NT->setRowCount(size_needed/sizeof(DWORD));
    for (uint i = 0; i < size_needed/sizeof(DWORD); i++){
        item = new QTableWidgetItem(QString::number(ID_arr[i]));
        ui->pr_table_NT->setItem(i, 0, item);
        h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ID_arr[i]);
        if (!GetModuleBaseNameW(h, NULL, w_name, 255)) name = "<нет доступа>";
        else name = QString::fromWCharArray(w_name);
        item = new QTableWidgetItem(name);
        ui->pr_table_NT->setItem(i, 1, item);
        CloseHandle(h);
    }
}

void MainWindow::showThreadsNT(){

}

void MainWindow::showDrivers(){
    ui->drivers_table_NT->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QTableWidgetItem *item;
    DWORD len = 1000;
    DWORD size_needed, name_size_needed;
    WCHAR w_name[255];
    QString name;
    LPVOID dr_arr[len];
    EnumDeviceDrivers(dr_arr, sizeof(dr_arr), &size_needed);
    ui->drivers_table_NT->setRowCount(size_needed/sizeof(dr_arr[0]));
    for (uint i = 0; i < size_needed/sizeof(dr_arr[0]); i++){
        item = new QTableWidgetItem("0x" + QString::number((long long)(dr_arr[i]), 16));
        ui->drivers_table_NT->setItem(i, 0, item);
        name_size_needed = GetDeviceDriverBaseName(dr_arr[i], w_name, 255);
        w_name[name_size_needed] = '\0';
        if (name_size_needed == 0) name = "<нет доступа>";
        else name = QString::fromWCharArray(w_name);
        item = new QTableWidgetItem(name);
        ui->drivers_table_NT->setItem(i, 1, item);
    }
}

void MainWindow::updateTables(){
    ui->pr_table_NT->clearContents();
    ui->pr_table_NT->setRowCount(0);
    showProcesesNT();
    ui->drivers_table_NT->clearContents();
    ui->drivers_table_NT->setRowCount(0);
    showDrivers();
    //Win 9x
    ui->proc_table->clearContents();
    ui->proc_table->setRowCount(0);
    showProcesses();
}

void MainWindow::showModulesNT(DWORD proc_ID, QString proc_name){
    window = new Form();
    window->setWindowTitle(proc_name);
    QTableWidget *table = window->getTable();
    table->setColumnCount(5);
    QTableWidgetItem *item = new QTableWidgetItem(QString("Имя модуля"));
    table->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem(QString("Путь к модулю"));
    table->setHorizontalHeaderItem(1, item);
    item = new QTableWidgetItem(QString("Адрес загрузки модуля"));
    table->setHorizontalHeaderItem(2, item);
    item = new QTableWidgetItem(QString("Размер модуля"));
    table->setHorizontalHeaderItem(3, item);
    item = new QTableWidgetItem(QString("Точка входа модуля"));
    table->setHorizontalHeaderItem(4, item);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    HANDLE h;
    HMODULE h_m[100];
    WCHAR w_name[255];
    QString name;
    DWORD h_m_needed;
    MODULEINFO m_inf;
    h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, proc_ID);
    EnumProcessModules(h, h_m, 100*sizeof(DWORD), &h_m_needed);
    table->setRowCount(h_m_needed/sizeof(HMODULE));
    for (int i = 0; i < h_m_needed/sizeof(HMODULE); i++){
        if (!GetModuleBaseNameW(h, h_m[i], w_name, 255)) name = "<нет доступа>";
        else name = QString::fromWCharArray(w_name);
        item = new QTableWidgetItem(name);
        table->setItem(i, 0, item);
        if (!GetModuleFileName(h_m[i], w_name, 255)) name = "<нет доступа>";
        else name = QString::fromWCharArray(w_name);
        item = new QTableWidgetItem(name);
        table->setItem(i, 1, item);
        GetModuleInformation(h, h_m[i], &m_inf, sizeof(MODULEINFO));
        item = new QTableWidgetItem("0x" + QString::number((long long)m_inf.lpBaseOfDll, 16));
        table->setItem(i, 2, item);
        item = new QTableWidgetItem(QString::number((long long)m_inf.SizeOfImage));
        table->setItem(i, 3, item);
        item = new QTableWidgetItem("0x" + QString::number((long long)m_inf.EntryPoint, 16));
        table->setItem(i, 4, item);
    }
    window->setModal(false);
    window->exec();
}

void MainWindow::on_pr_table_NT_cellClicked(int row, int column){
    DWORD ID = ui->pr_table_NT->item(row, 0)->text().toULong();
    showModulesNT(ID, ui->pr_table_NT->item(row, 1)->text());
}


//////////////////////////////////////

void MainWindow::showProcesses(){
    ui->proc_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if ((long long)snap == -1){
        QMessageBox::warning(this, "Ошибка!", "Не удалось сделать снимок процессов системы!");
        ui->proc_table->clearContents();
    }
    PROCESSENTRY32W proc;
    proc.dwSize = sizeof(PROCESSENTRY32W);
    bool f = Process32First(snap, &proc);
    while (f){
        int count = ui->proc_table->rowCount();
        ui->proc_table->insertRow(count);
        ui->proc_table->setItem(count, 0, new QTableWidgetItem(QString::number(proc.th32ProcessID)));
        ui->proc_table->setItem(count, 1, new QTableWidgetItem(QString::fromWCharArray(proc.szExeFile)));
        ui->proc_table->setItem(count, 2, new QTableWidgetItem(QString::number(proc.cntThreads)));
        ui->proc_table->setItem(count, 3, new QTableWidgetItem(QString::number(proc.th32ParentProcessID)));
        ui->proc_table->setItem(count, 4, new QTableWidgetItem(QString::number(proc.pcPriClassBase)));
        f = Process32Next(snap, &proc);
    }
    CloseHandle(snap);
}

void MainWindow::showThreadsAndModules(DWORD proc_ID, QString name){
    window1 = new Form1();
    window1->setWindowTitle(name);
    QTableWidget *table = window1->getThTable();
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if ((long long)snap == -1)
        QMessageBox::warning(this, "Ошибка!", "Не удалось сделать снимок потоков системы!");
    THREADENTRY32 thr;
    thr.dwSize = sizeof(THREADENTRY32);
    bool f = Thread32First(snap, &thr);
    while (f){
        if (thr.th32OwnerProcessID == proc_ID){
            int count = table->rowCount();
            table->insertRow(count);
            table->setItem(count, 0, new QTableWidgetItem(QString::number(thr.th32ThreadID)));
            table->setItem(count, 1, new QTableWidgetItem(QString::number(thr.th32OwnerProcessID)));
            table->setItem(count, 2, new QTableWidgetItem(QString::number(thr.tpBasePri)));
        }
        f = Thread32Next(snap, &thr);
    }
    CloseHandle(snap);

    table = window1->getModTable();
    snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc_ID);
    if ((long long)snap == -1)
        QMessageBox::warning(this, "Ошибка!", "Не удалось сделать снимок модулей процесса!");
    MODULEENTRY32 mod;
    mod.dwSize = sizeof(MODULEENTRY32);
    f = Module32FirstW(snap, &mod);
    while (f){
        int count = table->rowCount();
        table->insertRow(count);
        table->setItem(count, 0, new QTableWidgetItem(QString::number(mod.th32ProcessID)));
        table->setItem(count, 1, new QTableWidgetItem(QString::fromWCharArray(mod.szModule)));
        table->setItem(count, 2, new QTableWidgetItem(QString::fromWCharArray(mod.szExePath)));
        table->setItem(count, 3, new QTableWidgetItem("0x"+QString::number((long long)mod.modBaseAddr, 16)));
        table->setItem(count, 4, new QTableWidgetItem(QString::number(mod.modBaseSize)));
        table->setItem(count, 5, new QTableWidgetItem("0x"+QString::number((long long)mod.hModule, 16)));
        f = Module32NextW(snap, &mod);
    }
    CloseHandle(snap);

    window1->setModal(false);
    window1->exec();
}

void MainWindow::on_proc_table_cellClicked(int row, int column){
    DWORD ID = ui->proc_table->item(row, 0)->text().toULong();
    showThreadsAndModules(ID, ui->proc_table->item(row, 1)->text());
}
