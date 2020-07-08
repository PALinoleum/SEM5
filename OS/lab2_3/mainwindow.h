#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <QTimer>
#include "form.h"
#include "form1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Win NT
    void showProcesesNT();
    void showThreadsNT();
    void showDrivers();
    void showModulesNT(DWORD proc_ID, QString proc_name);
    //Win 9x
    void showProcesses();
    void showThreadsAndModules(DWORD proc_ID, QString name);
public slots:
    void updateTables();

private slots:
    void on_pr_table_NT_cellClicked(int row, int column);
    void on_proc_table_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    Form* window;
    Form1* window1;
};
#endif // MAINWINDOW_H
