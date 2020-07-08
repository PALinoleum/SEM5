#include "etc.hpp"

void QT_SetComputerName(QString str){
    BOOL result;
    char char_str[str.length()];
    for(int i = 0; i < str.length(); i++)
        char_str[i] = str.at(i).toLatin1();
    result = SetComputerNameA(char_str);
    if(result == ERROR_INVALID_PARAMETER){
        QMessageBox msgBox;
        msgBox.setText("Превышена длина строки или строка содержит неподдерживаемые символы ");
        msgBox.exec();
    };
}

void SystemEtc::setComputerName(){
    CurrentComputerName = vSetComputerName->text();
    QT_SetComputerName(CurrentComputerName);
    this->computerName->setText(CurrentComputerName);
    QMessageBox msgBox;
    msgBox.setText(CurrentComputerName);
    msgBox.exec();
}

void SystemEtc::s_reset(){
    QT_SetComputerName(DefaultComputerName);
    this->computerName->setText(DefaultComputerName);
    QMessageBox msgBox;
    msgBox.setText(DefaultComputerName);
    msgBox.exec();
}

QString languageId(SHORT languageId){
    QString result;
    switch(languageId){
        case LANG_RUS:
            result = "Русская";
            break;
        case LANG_ENG:
            result = "Английская";
            break;
    };
    return result;
}

SHORT GetLanguageShort(HKL key){
    return (LOWORD(key));
};

QString codePages(int id){
    QString result;
    switch(id){
        case 437:
            result = "OEM United States";
            break;
        case 1201:
            result = "Unicode UTF-16, big endian";
            break;  
        case 1200:
            result = "Unicode UTF-16, little endian";
            break;
        case 1251:
            result = "ANSI Cyrillic; Cyrillic (Windows)";
            break;
        case 866:
            result = "OEM Russian; Cyrillic (DOS)";
            break;
        case 65000:
            result = "Unicode (UTF-7)";
            break;
        case 65001:
            result = "Unicode (UTF-8)";
            break;
    };
    return result;
};

PowerStatus::PowerStatus(){
    SYSTEM_POWER_STATUS power_status;
    GetSystemPowerStatus(&power_status);

    QString vACLineStatus;
    QString vBatteryFlag;
    QString vBatteryLifePercent;
    QString vBatteryLifeTime;
    QString vBatteryFullLifeTime;

    switch(power_status.ACLineStatus){
        case 0:
            vACLineStatus = "От батареи";
            break;
        case 1:
            vACLineStatus = "От сети";            
            break;
        case 255:
            vACLineStatus = "Неизвестно";            
            break;
    };

    switch(power_status.BatteryFlag){
        case 1:
            vBatteryFlag = "Больше 66%";
            break;
        case 2:
            vBatteryFlag = "Меньше 33%";
            break;
        case 4:
            vBatteryFlag = "Меньше 5%";
            break;
        case 8:
            vBatteryFlag = "Заряжается";
            break;
        case 128:
            vBatteryFlag = "Нет батареи";
            break;
        case 255:
            vBatteryFlag = "Неизвестный статус";
            break;
    };
    
    if(power_status.BatteryLifePercent != 255){
        vBatteryLifePercent = QString::number(power_status.BatteryLifePercent)+" %";
    }
    else{
        vBatteryLifePercent = "Неизвестно";
    };
    
    if(power_status.BatteryLifeTime != -1){
        vBatteryLifeTime = QString::number(power_status.BatteryLifeTime)+" секунд";
    }
    else{
        vBatteryLifeTime = "Неизвестно";
    };
    
    if(power_status.BatteryFullLifeTime != -1){
        vBatteryFullLifeTime = QString::number(power_status.BatteryFullLifeTime)+" секунд";
    }
    else{
        vBatteryFullLifeTime = "Неизвестно";
    };

    layout = new QVBoxLayout;

    lACLine = new QHBoxLayout;
    lBatteryFlag = new QHBoxLayout;
    lBatteryLifePercent = new QHBoxLayout;
    lBatteryLifeTime = new QHBoxLayout;
    lBatteryFullLifeTime = new QHBoxLayout;

    ACLine = new QLabel;
    BatteryFlag = new QLabel;
    BatteryLifePercent = new QLabel;
    BatteryLifeTime = new QLabel;
    BatteryFullLifeTime = new QLabel;

    nACLine = new QLabel;
    nBatteryFlag = new QLabel;
    nBatteryLifePercent = new QLabel;
    nBatteryLifeTime = new QLabel;
    nBatteryFullLifeTime = new QLabel;

    nACLine->setText("Питание от сети: ");
    nBatteryFlag->setText("Состояние аккумулятора: ");
    nBatteryLifePercent->setText("Процент заряда аккумулятора: ");
    nBatteryLifeTime->setText("Осталось времени работы: ");
    nBatteryFullLifeTime->setText("Времени работы от полного заряда: ");
    

    ACLine->setText(vACLineStatus);
    BatteryFlag->setText(vBatteryFlag);
    BatteryLifePercent->setText(vBatteryLifePercent);
    BatteryLifeTime->setText(vBatteryLifeTime);
    BatteryFullLifeTime->setText(vBatteryFullLifeTime);
    
    lACLine->addWidget(nACLine);
    lACLine->addWidget(ACLine);
    lBatteryFlag->addWidget(nBatteryFlag);
    lBatteryFlag->addWidget(BatteryFlag);
    lBatteryLifePercent->addWidget(nBatteryLifePercent);
    lBatteryLifePercent->addWidget(BatteryLifePercent);
    lBatteryLifeTime->addWidget(nBatteryLifeTime);
    lBatteryLifeTime->addWidget(BatteryLifeTime);
    lBatteryFullLifeTime->addWidget(nBatteryFullLifeTime);
    lBatteryFullLifeTime->addWidget(BatteryFullLifeTime);

    layout->addLayout(lACLine);
    layout->addLayout(lBatteryFlag);
    layout->addLayout(lBatteryLifePercent);
    layout->addLayout(lBatteryLifeTime);
    layout->addLayout(lBatteryFullLifeTime);

    this->setLayout(layout);
};


SystemEtc::SystemEtc(){
    DefaultComputerName = QT_GetComputerName();
    CurrentComputerName = DefaultComputerName;
    PowerStatus* ps = new PowerStatus;

    QVBoxLayout *layout = new QVBoxLayout;
    reset = new QPushButton("Сброс");


    lComputerName = new QHBoxLayout;
    lSetComputerName = new QHBoxLayout;
    lACP = new QHBoxLayout;
    lKeyboardLayout = new QHBoxLayout;

    ACP = new QLabel;
    nACP = new QLabel;
    computerName = new QLabel;
    nComputerName = new QLabel;
    keyboardLayout = new QLabel;
    nKeyboardLayout = new QLabel;

    vSetComputerName = new QLineEdit(); 
    bSetComputerName = new QPushButton("Установить имя");

    nComputerName->setText("Имя ПК: ");
    nACP->setText("Кодовая страница: ");
    nKeyboardLayout->setText("Раскладка клавиатуры: ");

    computerName->setText(CurrentComputerName);
    ACP->setText(codePages(GetACP()));
    keyboardLayout->setText(languageId(
                            GetLanguageShort(
                            GetKeyboardLayout(0))));

    lComputerName->addWidget(nComputerName);
    lComputerName->addWidget(computerName);
    
    lACP->addWidget(nACP);
    lACP->addWidget(ACP);
    
    lSetComputerName->addWidget(vSetComputerName);
    lSetComputerName->addWidget(bSetComputerName);

    lKeyboardLayout->addWidget(nKeyboardLayout);
    lKeyboardLayout->addWidget(keyboardLayout);

    layout->addLayout(lACP);
    layout->addLayout(lKeyboardLayout);
    layout->addWidget(ps);
    layout->addLayout(lComputerName);
    layout->addLayout(lSetComputerName);
    layout->addWidget(reset);
    this->setLayout(layout);
    QWidget::connect(reset,SIGNAL(pressed()),this,SLOT(s_reset()));
    QWidget::connect(bSetComputerName,SIGNAL(pressed()),this,SLOT(setComputerName()));
};
