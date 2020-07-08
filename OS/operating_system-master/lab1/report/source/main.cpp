#include <QtWidgets>
#include <windows.h>
#include <wchar.h>
#include "systemInfo.hpp"
#include "colors.hpp"
#include "metrics.hpp"
#include "settings.hpp"
#include "settings2.hpp"
#include "clock.hpp"
#include "etc.hpp"

int main (int argc,char* argv[]){
    QApplication* app = new QApplication (argc,argv);
    QTabWidget* tabs = new QTabWidget;
    SystemInfo* p1 = new SystemInfo();
    SystemMetrics* p2 = new SystemMetrics();
    SystemSettings* p3 = new SystemSettings();
    SystemSettings2* p3_1 = new SystemSettings2();
    SystemColors* p4 = new SystemColors();
    SystemClock* p5 = new SystemClock();
    SystemEtc* p6 = new SystemEtc();


    tabs->addTab(p1,"Информация");
    tabs->addTab(p2,"Метрики");
    tabs->addTab(p3,"Параметры");
    tabs->addTab(p3_1,"NonClient метрики");
    tabs->addTab(p4,"Цвета");
    tabs->addTab(p5,"Время");
    tabs->addTab(p6,"Прочее");
    tabs->setFixedSize(440,490);
    tabs->setWindowTitle("Лабораторная работа №1");
    tabs->show();
    return app->exec();
}
