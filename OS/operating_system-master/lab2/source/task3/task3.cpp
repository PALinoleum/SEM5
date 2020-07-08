#include "task3.hpp"

QString processNameFromId(DWORD processID){
    QString result;
    DWORD length = MAX_PATH+1;
    wchar_t processName[1024];
    //Создаем HANDLE процесса по id с правами чтения памяти процесса и информации о нем.
    HANDLE handleProcess = OpenProcess((PROCESS_QUERY_INFORMATION|PROCESS_VM_READ),FALSE, processID );
    //Получаем имя процесса
    if (NULL != handleProcess ){
        HMODULE handleModule;
        DWORD moduleArrSize;
        //Получаем массив дескрипторов модулей процесса, и по первому модулю получаем его имя.
        if(EnumProcessModules(handleProcess,&handleModule,sizeof(handleModule),&moduleArrSize)){
            length = GetModuleBaseNameW(handleProcess, handleModule, processName,sizeof(processName)/sizeof(TCHAR) );
        }
    }
    //Закрываем созданный дескриптор процесса.
    CloseHandle(handleProcess);
    //Конвертируем wChar в QString
    if(length){
        processName[length+1] = 0;
        result = QString::fromWCharArray(processName);
        return result;
    }else{
        return QString("Ошибка чтения имени процесса");
    }
}

int processToQTable(QTableWidget *table){
    table->setRowCount(0);
    table->setColumnCount(2);
    table->setColumnWidth(0,128);
    table->setColumnWidth(1,300);
    table->setHorizontalHeaderLabels({"ID процесса","Название процесса"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    DWORD processArr[1024], processArrSize, processCount,realProcessCount;
    //Получаем массив всех ID процессов processArr.
    
    QString systemProcessName = processNameFromId(4);
    
    if (!EnumProcesses( processArr, sizeof(processArr), &processArrSize)){
        return 1;
    }
    //Вычисляем кол-во полученных процессов.
    processCount = processArrSize / sizeof(DWORD);
    table->setRowCount(processCount);
    realProcessCount = processCount;
    //Заполняем таблицу
    int j = 0;
    for (int i = 0; i < processCount; i++ ){
        if(processArr[i] == 0 ){
            realProcessCount--;
            table->setRowCount(realProcessCount);
        }
        else{    
            QString processName = processNameFromId(processArr[i]);
            if(!processName.isEmpty()){
                QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(processArr[i]));
                table->setItem(j,0,idItem);
                QTableWidgetItem* nameItem = new QTableWidgetItem(processName);
                table->setItem(j,1,nameItem);
                j++;
            };
        };
    };
    return 0;
};


ProcessPage::ProcessPage(){        
    layout = new QVBoxLayout;
    table = new QTableWidget;
    refreshButton = new QPushButton("Обновить");
    processToQTable(table);
    layout->addWidget(table);
    connect(table,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(showModules(int,int)));
     connect(refreshButton,SIGNAL(pressed()),
            this,SLOT(refreshTable()));        
    layout->addWidget(refreshButton);
    this->setLayout(layout);
};

void ProcessPage::showModules(int row, int column){
    unsigned processId = this->table->item(row,0)->text().toInt();
    ModulesTable *modules = new ModulesTable(processId);
    modules->show();
};

ModulesTable::ModulesTable(int processId){
    QVBoxLayout *layout = new QVBoxLayout;
    QTableWidget* table = new QTableWidget;
    modulesToQTable(processId,table);
    layout->addWidget(table);
    this->setLayout(layout);
}; 

void modulesToQTable(DWORD processID,QTableWidget* table){
    table->setRowCount(0);    
    HMODULE hMods[1024];
    HANDLE processHandle;
    HANDLE hProcess;
    DWORD cbNeeded;

    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Путь к модулю","Точка загрузки","Размер модуля","Точка входа"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    //Открытие дескриптора потока
    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID );
    if (NULL == hProcess){
        QMessageBox msgBox;
        msgBox.setText("Дескриптор потока не был получен");
        msgBox.exec();
        return 0;
    }

    if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)){
        int modulesCount = cbNeeded / sizeof(HMODULE);
        QMessageBox msgBox1;
        msgBox1.setText("Кол-во модулей: "+QString::number(modulesCount));
        msgBox1.exec();
        table->setRowCount(modulesCount);
        int realModulesCount = modulesCount;
        for (int i = 0,j=0; i < (modulesCount); i++ ){
            wchar_t szModName[MAX_PATH];
            if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
                                        sizeof(szModName) / sizeof(TCHAR)))
            {
                QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromWCharArray(szModName));
                table->setItem(j,0,nameItem);
                
                MODULEINFO moduleInfo;
                QTableWidgetItem *baseItem,*sizeItem,*entryItem;
                if(GetModuleInformation(hProcess,hMods[i],&moduleInfo,sizeof(moduleInfo))){
                    baseItem = new QTableWidgetItem(
                        "0x"+QString::number((int)moduleInfo.lpBaseOfDll,16));
                    sizeItem = new QTableWidgetItem(
                        QString::number(moduleInfo.SizeOfImage)+" байт(а)");
                    entryItem = new QTableWidgetItem(
                        "0x"+QString::number((int)moduleInfo.EntryPoint,16));
                }else{
                    baseItem = new QTableWidgetItem("Не удалось получить структуру");
                    sizeItem = new QTableWidgetItem("Не удалось получить структуру");
                    entryItem = new QTableWidgetItem("Не удалось получить структуру");
                };

                table->setItem(j,1,baseItem);
                table->setItem(j,2,sizeItem);
                table->setItem(j,3,entryItem);

                j++;

            }else{
                realModulesCount--;
                table->setRowCount(realModulesCount);
            };
        }
    }else{
        QMessageBox msgBox2;
        msgBox2.setText("Не удалось считать список модулей");
        msgBox2.exec();
    };

    //Закрытие дескриптора потока
    CloseHandle(hProcess);
};

void driversToQTable(QTableWidget* table){
    table->setRowCount(0);    
    table->setColumnCount(2);
    table->setColumnWidth(0,128);
    table->setColumnWidth(1,300);
    table->setHorizontalHeaderLabels({"Адрес загрузки драйвера","Название драйвера"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    LPVOID drivers[1024];
    DWORD cbNeeded;
    int cDrivers;
    if( EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers)){ 
      char szDriver[1024];
      cDrivers = cbNeeded / sizeof(drivers[0]);
      table->setRowCount(cDrivers);
      for (int i=0; i < cDrivers; i++ ){
        QTableWidgetItem *addressItem = new QTableWidgetItem(
                        "0x"+QString::number((int)drivers[i],16));
        table->setItem(i,0,addressItem);
        if(GetDeviceDriverBaseNameA(drivers[i], szDriver,sizeof(szDriver)/sizeof(szDriver[0]))){
            QTableWidgetItem *nameItem = new QTableWidgetItem(
                        QString(szDriver));
            table->setItem(i,1,nameItem);
        };
      };
    };
};

DriversPage::DriversPage(){
    layout = new QVBoxLayout;
    table = new QTableWidget;
    refreshButton = new QPushButton("Обновить");
    driversToQTable(table);
    layout->addWidget(table);
    layout->addWidget(refreshButton);
    connect(refreshButton,SIGNAL(pressed()),
            this,SLOT(refreshTable())); 
    this->setLayout(layout);
};         

Th32Page::Th32Page(){
    layout = new QVBoxLayout;
    tableProcess = new QTableWidget;
    refreshButton = new QPushButton("Обновить");
    th32SnapToQTable(tableProcess);
    layout->addWidget(tableProcess);
    connect(tableProcess,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(showSubTables(int,int)));
    connect(refreshButton,SIGNAL(pressed()),
            this,SLOT(refreshTable())); 
    layout->addWidget(refreshButton);
    this->setLayout(layout);
};

void th32SnapToQTable(QTableWidget* table){
    table->setRowCount(0);    
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Id процесса","Название процесса","Кол-во потоков","Id родитеского процесса","Приоритет"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int i=0;
    // Получаем снимок
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE ){
        QMessageBox boxError1;
        boxError1.setText("Ошибка получения снимка.");
        boxError1.exec();
    }

    // Устанавливаем размер структуры
    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Получаем информацию о первом процессе в списке
    // при неудаче завершаем работу.
    if( !Process32First( hProcessSnap, &pe32 ) ){
        QMessageBox boxError2;
        boxError2.setText("Ошибка получения информации о процессе.");
        boxError2.exec();
        CloseHandle( hProcessSnap );
    }
    do{
        i++;
    }
    while(Process32Next( hProcessSnap, &pe32 ));
    table->setRowCount(i);
    Process32First( hProcessSnap, &pe32);
    i=0;
    // Заносим информацию о процессах в таблицу
    do{
        i++;
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromWCharArray(pe32.szExeFile));
        table->setItem(i,1,nameItem);

        QTableWidgetItem* idItem;
        QTableWidgetItem* threadCountItem;
        QTableWidgetItem* parentIdItem;
        QTableWidgetItem* idPriorityBaseItem;

        idItem = new QTableWidgetItem("0x"+QString::number(i,16));
        table->setItem(i,0,idItem);

        threadCountItem = new QTableWidgetItem(QString::number(pe32.cntThreads));
        table->setItem(i,2,threadCountItem);

        parentIdItem = new QTableWidgetItem("0x"+QString::number(pe32.th32ParentProcessID,16));
        table->setItem(i,3,parentIdItem);

        idPriorityBaseItem = new QTableWidgetItem(QString::number(pe32.pcPriClassBase));
        table->setItem(i,4,idPriorityBaseItem);

    } while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );

};

void Th32Page::showSubTables(int row, int column){
    unsigned processId = this->tableProcess->item(row,0)->text().toInt();    
    Th32SubTable *subTable = new Th32SubTable(processId);
    subTable->show();
};

Th32SubTable::Th32SubTable(int processId){
    layout = new QVBoxLayout;
    tabs = new QTabWidget;
    tableModules = new QTableWidget;
    th32ModulesToQTable(processId,tableModules);
    tableThreads = new QTableWidget;
    th32ThreadsToQTable(processId,tableThreads);
    tabs->addTab(tableModules,"Модули");
    tabs->addTab(tableThreads,"Потоки");
    layout->addWidget(tabs);
    this->setLayout(layout);
}

void th32ThreadsToQTable(int processId,QTableWidget* table){
    table->setRowCount(0);    
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Id потока","Базовый приоритет"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
    THREADENTRY32 te32; 
    hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, processId ); 
    if( hThreadSnap == INVALID_HANDLE_VALUE ){ 
        return; 
    };
    
    te32.dwSize = sizeof(THREADENTRY32 ); 
    
    if(!Thread32First( hThreadSnap, &te32 )){ 
        CloseHandle( hThreadSnap  );
        return; 
    };

    int i = 0;
    do i++; while( Thread32Next( hThreadSnap, &te32 ) );
    table->setRowCount(i);    
    i=0;

    QTableWidgetItem* idItem;
    QTableWidgetItem* priorityItem;

    Thread32First( hThreadSnap, &te32 );
    do { 
        idItem = new QTableWidgetItem(
            QString::number(te32.th32ThreadID )
        );
        priorityItem = new QTableWidgetItem(
            QString::number(te32.tpBasePri )
        );
        
        table->setItem(i,0,idItem);
        table->setItem(i,1,priorityItem);
        i++;
    } while( Thread32Next( hThreadSnap, &te32 ) ); 
    CloseHandle( hThreadSnap ); 
};

void th32ModulesToQTable(int processId,QTableWidget* table){
    table->setRowCount(0);    
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Название модуля","Путь","Id процесса","Размер"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE; 
    MODULEENTRY32 me32; 
    hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, processId ); 

    if( hModuleSnap == INVALID_HANDLE_VALUE ){ 
        return; 
    };
    
    me32.dwSize = sizeof( MODULEENTRY32 ); 
    
    if(!Module32First( hModuleSnap, &me32)){ 
        CloseHandle( hModuleSnap );     // Must clean up the snapshot object! 
        return; 
    };

    int i = 0;
    do i++; while( Module32Next( hModuleSnap, &me32 ) );
    table->setRowCount(i);    
    i=0;

    QTableWidgetItem* nameItem;
    QTableWidgetItem* pathItem;
    QTableWidgetItem* processIdItem;
    QTableWidgetItem* sizeItem;

    Module32First( hModuleSnap, &me32);
    do { 
        nameItem = new QTableWidgetItem(
            QString::fromWCharArray(me32.szModule)
        );
        pathItem = new QTableWidgetItem(
            QString::fromWCharArray(me32.szExePath)
        );
        processIdItem = new QTableWidgetItem(
            "0x"+QString::number(me32.th32ProcessID,16)
        );
        sizeItem = new QTableWidgetItem(
            QString::number(me32.modBaseSize)+" байт(а)"
        );

        table->setItem(i,0,nameItem);
        table->setItem(i,1,pathItem);
        table->setItem(i,2,processIdItem);
        table->setItem(i,3,sizeItem);
        i++;
    } while( Module32Next( hModuleSnap, &me32 ) ); 
    CloseHandle( hModuleSnap ); 
};


void ProcessPage::refreshTable(){
    processToQTable(table);
};

void DriversPage::refreshTable(){
    driversToQTable(table);
};

void Th32Page::refreshTable(){
    th32SnapToQTable(tableProcess);
};