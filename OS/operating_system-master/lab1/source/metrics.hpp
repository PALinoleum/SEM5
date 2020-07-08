#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#pragma once

#define SM_SWAPBUTTON 23
#define SM_CLEANBOOT 67
#define SM_CMONITORS 80
#define SM_CMOUSEBUTTONS 43
#define SM_CXBORDER 5
#define SM_CXCURSOR 13
#define SM_CXDLGFRAME 7
#define SM_CXDOUBLECLK 36
#define SM_CXDRAG 68
#define SM_CXEDGE 45
#define SM_CXFOCUSBORDER 83
#define SM_CXFRAME 32
#define SM_CXFULLSCREEN 16
#define SM_CXHSCROLL 21
#define SM_CXHTHUMB 10
#define SM_CXICON 11
#define SM_CXICONSPACING 38
#define SM_CXMAXIMIZED 61
#define SM_CXMAXTRACK 59
#define SM_CXMENUCHECK 71
#define SM_CXMENUSIZE 54
#define SM_CXMIN 28
#define SM_CXMINIMIZED 57
#define SM_CXMINSPACING 47
#define SM_CXMINTRACK 34
#define SM_CXSCREEN 0
#define SM_CXSIZE 30
#define SM_CXSMICON 49
#define SM_CXSMSIZE 52
#define SM_CXVIRTUALSCREEN 78
#define SM_CXVSCROLL 2
#define SM_CYBORDER 6
#define SM_CYCAPTION 4
#define SM_CYCURSOR 14
#define SM_CYDLGFRAME 8
#define SM_CYDOUBLECLK 37
#define SM_CYDRAG 69
#define SM_CYEDGE 46
#define SM_CYFOCUSBORDER 84
#define SM_CYFRAME 33
#define SM_CYFULLSCREEN 17
#define SM_CYHSCROLL 3
#define SM_CYICON 12
#define SM_CYICONSPACING 39
#define SM_CYMAXIMIZED 62
#define SM_CYMAXTRACK 60
#define SM_CYMENU 15
#define SM_CYMENUCHECK 72


void QT_GetSystemMetrics(QTableWidget* table,int row,int index,QString header,QString suffix);
void QT_GetSystemMetricsBool(QTableWidget* table,int row,int index,QString header);
void QT_GetSystemMetricBoot(QTableWidget* table,int row);

class SystemMetrics : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QTableWidget* table;
    public:
        SystemMetrics(); 
};