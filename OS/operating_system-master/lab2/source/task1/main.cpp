#include <QtWidgets>
#include <windows.h>
#include <wchar.h>
#include "task1.hpp"

int main (int argc,char* argv[]){
    QApplication* app = new QApplication (argc,argv);
    Task1 *t1 =new Task1;
    t1->setWindowTitle("Лабораторная работа №2. Задание 1.");
    t1->show();
    return app->exec();
}
