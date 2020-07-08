#include <QtWidgets>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#pragma once

QString processNameFromId(DWORD processID);
int processToQTable(QTableWidget *table);
void modulesToQTable(DWORD processId,QTableWidget* table);
void driversToQTable(QTableWidget* table);
void th32SnapToQTable(QTableWidget* table);
void th32ThreadsToQTable(int processId,QTableWidget* table);
void th32ModulesToQTable(int processId,QTableWidget* table);

class ModulesTable:public QWidget{
    Q_OBJECT
    public:
        ModulesTable(int processId); 
};

class ProcessPage : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QTableWidget* table;
        QPushButton* refreshButton;
    public slots:
        void refreshTable();     
        void showModules(int row, int column);
    public:
        ProcessPage();         
};

class DriversPage : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QTableWidget* table;
        QPushButton* refreshButton;
    public slots:
        void refreshTable();     
    public:
        DriversPage();         
};

class Th32Page : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QTableWidget* tableProcess;
        QPushButton* refreshButton;
    public slots:
        void showSubTables(int row, int column);        
        void refreshTable();        
    public:
        Th32Page();         
};


class Th32SubTable : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QTabWidget* tabs;
        QTableWidget* tableModules;
        QTableWidget* tableThreads;
    public:
        Th32SubTable(int processId);         
};