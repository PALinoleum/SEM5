#include <QtWidgets>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#pragma once

class Task1 : public QWidget{
    Q_OBJECT
    private:
        QString filename;
        QString processName;

        DWORD processID;
        HMODULE handleModule;
        HANDLE handleProcess;

        QVBoxLayout *layout;
        QLabel *handle,*name,*path;
        QLabel *handleLabel,*nameLabel,*pathLabel;
        QHBoxLayout *handleLayout,*nameLayout,*pathLayout;
        QLineEdit *handleEdit,*nameEdit,*pathEdit;
        QPushButton *handleButton,*nameButton,*pathButton;
    public slots:
        void setInfoByHandle();
        void setInfoByName();
        void setInfoByPath();
    public:
        Task1();        
};

