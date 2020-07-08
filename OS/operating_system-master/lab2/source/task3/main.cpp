#include <QtWidgets>
#include <windows.h>
#include <wchar.h>
#include "task3.hpp"
int main (int argc,char* argv[]){
    QApplication* app = new QApplication (argc,argv);
    QTabWidget* tabs = new QTabWidget;
    ProcessPage* p1 = new ProcessPage;
    DriversPage* p2 = new DriversPage;
    Th32Page* p3 = new Th32Page;
    
    tabs->addTab(p1,"Процессы");
    tabs->addTab(p2,"Драйверы");
    tabs->addTab(p3,"Снимок th32");
    tabs->setFixedSize(500,700);
    tabs->setWindowTitle("Лабораторная работа №2. Задание 3.");
    tabs->show();
    return app->exec();
}
