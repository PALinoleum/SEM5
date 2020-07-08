#include "task1.hpp"


Task1::Task1(){
        layout = new QVBoxLayout;

        handle = new QLabel("<адрес дескриптора>");
        name = new QLabel("<имя модуля>");
        path = new QLabel("<путь к файлу>");

        handleLabel = new QLabel("Дескриптор");
        nameLabel = new QLabel("Имя модуля");
        pathLabel = new QLabel("Полный путь к файлу");
        
        handleLayout = new QHBoxLayout;
        pathLayout = new QHBoxLayout;
        nameLayout = new QHBoxLayout;

        handleEdit = new QLineEdit;
        pathEdit = new QLineEdit;
        nameEdit = new QLineEdit;

        handleButton = new QPushButton("Ввод");
        nameButton = new QPushButton("Ввод");
        pathButton = new QPushButton("Ввод");

        pathLayout->addWidget(pathEdit);
        pathLayout->addWidget(pathButton);
        
        handleLayout->addWidget(handleEdit);
        handleLayout->addWidget(handleButton);

        nameLayout->addWidget(nameEdit);
        nameLayout->addWidget(nameButton);

        layout->addWidget(handleLabel);
        layout->addLayout(handleLayout);
        layout->addWidget(handle);

        layout->addWidget(nameLabel);
        layout->addLayout(nameLayout);
        layout->addWidget(name);

        layout->addWidget(pathLabel);
        layout->addLayout(pathLayout);
        layout->addWidget(path);

        this->setLayout(layout);

        int length,moduleLength;
        TCHAR filePath[MAX_PATH];
        TCHAR moduleName[MAX_PATH];
        processID = GetCurrentProcessId();
        handleProcess = OpenProcess(PROCESS_QUERY_INFORMATION,TRUE,processID);
        length = GetModuleFileNameEx(handleProcess,NULL,filePath,MAX_PATH);
        handleModule = GetModuleHandle(filePath);
        moduleLength = GetModuleFileName(handleModule, moduleName, MAX_PATH);
        filename  = QString::fromWCharArray(filePath);
        processName  = QString::fromWCharArray(moduleName);
        processName.remove(0, processName.lastIndexOf("\\") + 1);
        handle->setText("0x"+QString::number((int)handleModule,16));
        path->setText(filename);
        name->setText(processName);
        CloseHandle(handleProcess);

        connect(handleButton,SIGNAL(pressed()),this,SLOT(setInfoByHandle()));
        connect(nameButton,SIGNAL(pressed()),this,SLOT(setInfoByName()));
        connect(pathButton,SIGNAL(pressed()),this,SLOT(setInfoByPath()));
};

void Task1::setInfoByHandle(){
    name->setText("");
    nameEdit->setText("");
    path->setText("");
    pathEdit->setText("");
    HMODULE moduleHandle = (HMODULE)(this->handleEdit->text().toInt(0,0));
    int pathLength;
    TCHAR filePath[MAX_PATH];
    pathLength = GetModuleFileName(moduleHandle, filePath, MAX_PATH);
    if(pathLength){
        QString pathStr = QString::fromWCharArray(filePath);
        path->setText(pathStr);
        name->setText(pathStr.remove(0, pathStr.lastIndexOf("\\") + 1));
    }else{
        QMessageBox *err = new QMessageBox;
        err->setText("Некорректный дескриптор.");
        err->show(); 
        name->setText("ОШИБКА");
        path->setText("ОШИБКА");

    }
};
void Task1::setInfoByName(){
    path->setText("");
    pathEdit->setText("");
    handle->setText("");
    handleEdit->setText("");
    HMODULE moduleHandle;
    TCHAR moduleName[MAX_PATH];
    
    
    int moduleLength = nameEdit->text().toWCharArray(moduleName);
    moduleName[moduleLength] = 0;

    moduleHandle = GetModuleHandle(moduleName);
    if(moduleHandle==NULL){
        QMessageBox *err = new QMessageBox;
        err->setText("Некорректное имя модуля.");
        err->show(); 
        path->setText("ОШИБКА");
        handle->setText("ОШИБКА");
    }else{
        TCHAR pathName[MAX_PATH];
        int pathLength = GetModuleFileName(moduleHandle, pathName, MAX_PATH);;

        path->setText(QString::fromWCharArray(pathName));
        handle->setText("0x"+QString::number((int)moduleHandle,16));
    };
};
void Task1::setInfoByPath(){
    name->setText("");
    nameEdit->setText("");
    handle->setText("");
    handleEdit->setText("");
    HMODULE moduleHandle;
    TCHAR moduleName[MAX_PATH];
    QString nameStr = pathEdit->text();
    nameStr = nameStr.remove(0, nameStr.lastIndexOf("\\") + 1);
    
    
    int moduleLength = nameStr.toWCharArray(moduleName);
    moduleName[moduleLength] = 0;

    moduleHandle = GetModuleHandle(moduleName);
    if(moduleHandle==NULL){
        QMessageBox *err = new QMessageBox;
        err->setText("Некорректный путь.");
        err->show(); 
        name->setText("ОШИБКА");
        handle->setText("ОШИБКА");
    }else{
        name->setText(nameStr);
        handle->setText("0x"+QString::number((int)moduleHandle,16));
    };
};