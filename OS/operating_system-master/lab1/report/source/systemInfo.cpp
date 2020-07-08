#include "system_info.hpp"

QString QT_GetUserName(){
    wchar_t str[4096];
    DWORD size = 4096;
    QString result_str;
    if(GetUserNameW(str, &size)){
        result_str.fromWCharArray(str,size);
    }
    else{
        result_str = "GET_ERROR";
    }
    return result_str;
};

QString QT_GetComputerName(){
    char str[4096];
    DWORD size = 4096;
    QString result_str;
    if(GetComputerNameA(str, &size)){
        result_str = str;
    }
    else{
        result_str = "GET_ERROR";
    }
    return result_str;
};

QString QT_GetSystemDirectory(){
    char str[4096];
    UINT size = 4096;
    QString result_str;
    if(GetSystemDirectoryA(str, size)){
        result_str = str;
    }
    else{
        result_str = "GET_ERROR";
    }
    return result_str;
};

QString QT_GetSystemWindowsDirectory(){
    char str[4096];
    UINT size = 4096;
    QString result_str;
    if(GetSystemWindowsDirectoryA(str, size)){
        result_str = str;
    }
    else{
        result_str = "GET_ERROR";
    }
    return result_str;
};

QString QT_GetTempPath(){
    char str[4096];
    DWORD size = 4096;
    QString result_str;
    if(GetTempPathA(size, str)){
        result_str = str;
    }
    else{
        result_str = "GET_ERROR";
    }
    return result_str;
};

QString QT_GetVersionExA(){
    OSVERSIONINFOA osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&osvi);
    QString result_str = QString::number(osvi.dwMajorVersion) +"."
                        +QString::number(osvi.dwMinorVersion) +" ("
                        +QString::number(osvi.dwBuildNumber)  +")";
    return result_str;
};

SystemInfo::SystemInfo(){
    QVBoxLayout *layout = new QVBoxLayout;
    
    QHBoxLayout *lComputerName = new QHBoxLayout;
    QHBoxLayout *lUserName = new QHBoxLayout;
    QHBoxLayout *lSystemDirectory = new QHBoxLayout;
    QHBoxLayout *lSystemWindowsDirectory = new QHBoxLayout;
    QHBoxLayout *lTempPath = new QHBoxLayout;
    QHBoxLayout *lVersion = new QHBoxLayout;

    QLabel *computerName = new QLabel;
    QLabel *userName = new QLabel;
    QLabel *systemDirectory = new QLabel;
    QLabel *systemWindowsDirectory = new QLabel;
    QLabel *tempPath = new QLabel;
    QLabel *version = new QLabel;
    
    QLabel *nComputerName = new QLabel;
    QLabel *nUserName = new QLabel;
    QLabel *nSystemDirectory = new QLabel;
    QLabel *nSystemWindowsDirectory = new QLabel;
    QLabel *nTempPath = new QLabel;
    QLabel *nVersion = new QLabel;

    nComputerName->setText("Имя ПК: ");
    nUserName->setText("Имя пользователя: ");
    nSystemDirectory->setText("Путь к системной папке: ");
    nSystemWindowsDirectory->setText("Путь к папке Windows: ");
    nTempPath->setText("Путь к папке temp: ");
    nVersion->setText("Версия OC: ");

    computerName->setText(QT_GetComputerName());
    userName->setText(QT_GetUserName());
    systemDirectory->setText(QT_GetSystemDirectory());
    systemWindowsDirectory->setText(QT_GetSystemWindowsDirectory());
    tempPath->setText(QT_GetTempPath());
    version->setText(QT_GetVersionExA());

    lComputerName->addWidget(nComputerName);
    lComputerName->addWidget(computerName);
    lUserName->addWidget(nUserName);
    lUserName->addWidget(userName);
    lSystemDirectory->addWidget(nSystemDirectory);
    lSystemDirectory->addWidget(systemDirectory);
    lSystemWindowsDirectory->addWidget(nSystemWindowsDirectory);
    lSystemWindowsDirectory->addWidget(systemWindowsDirectory);
    lTempPath->addWidget(nTempPath);
    lTempPath->addWidget(tempPath);
    lVersion->addWidget(nVersion);
    lVersion->addWidget(version);

    layout->addLayout(lComputerName);
    layout->addLayout(lUserName);
    layout->addLayout(lSystemDirectory);
    layout->addLayout(lSystemWindowsDirectory);
    layout->addLayout(lTempPath);
    layout->addLayout(lVersion);

    this->setLayout(layout);
};