#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#pragma once

QString QT_GetUserName();
QString QT_GetComputerName();
QString QT_GetSystemDirectory();
QString QT_GetSystemWindowsDirectory();
QString QT_GetTempPath();
QString QT_GetVersionExA();

class SystemInfo : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QLabel *computerName,*userName,*systemDirectory,
            *systemWindowsDirectory,*tempPath,*version;
        QHBoxLayout *lComputerName,*lUserName,*lSystemDirectory,
            *lSystemWindowsDirectory,*lTempPath,*lVersion;
        QLabel *nComputerName,*nUserName,*nSystemDirectory,
            *nSystemWindowsDirectory,*nTempPath,*nVersion;      
    public:
        SystemInfo(); 
};