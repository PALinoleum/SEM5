#include "clock.hpp"

void SystemTime::s_set(){
    current_time.wYear = vYear->value();
    current_time.wMonth = vMonth->currentIndex()-1;
    current_time.wDay = vDay->value();
    current_time.wHour = vHour->value();
    current_time.wMinute = vMinute->value();
    current_time.wDayOfWeek = vDayOfWeek->currentIndex();
    SetLocalTime(&current_time);
};

void SystemTime::s_reset(){
    current_time.wYear = default_time.wYear;
    current_time.wMonth = default_time.wMonth;
    current_time.wDay = default_time.wDay;
    current_time.wHour = default_time.wHour;
    current_time.wMinute = default_time.wMinute;
    current_time.wDayOfWeek = default_time.wDayOfWeek;
    vYear->setValue(current_time.wYear);
    vMonth->setCurrentIndex(current_time.wMonth-1);
    vDay->setValue(current_time.wDay);
    vHour->setValue(current_time.wHour);
    vMinute->setValue(current_time.wMinute);
    vDayOfWeek->setCurrentIndex(current_time.wDayOfWeek);
    SetLocalTime(&current_time);
};

SystemTime::SystemTime(bool editLock,SYSTEMTIME time){

    default_time.wYear = time.wYear;
    default_time.wMonth = time.wMonth;
    default_time.wDay = time.wDay;
    default_time.wHour = time.wHour;
    default_time.wMinute = time.wMinute;
    default_time.wDayOfWeek = time.wDayOfWeek;

    current_time.wYear = default_time.wYear;
    current_time.wMonth = default_time.wMonth;
    current_time.wDay = default_time.wDay;
    current_time.wHour = default_time.wHour;
    current_time.wMinute = default_time.wMinute;
    current_time.wDayOfWeek = default_time.wDayOfWeek;

    this->editLock = editLock;

    layout = new QVBoxLayout;

    lDate = new QHBoxLayout;
    lTime = new QHBoxLayout;
    lDayOfWeek = new QHBoxLayout;
    lButtons = new QHBoxLayout;

    nDate = new QLabel;
    nTime = new QLabel;
    nDayOfWeek = new QLabel;

    vDayOfWeek = new QComboBox;
    vMonth = new QComboBox;

    vYear = new QSpinBox;
    vDay = new QSpinBox;
    vHour = new QSpinBox;
    vMinute = new QSpinBox;

    reset = new QPushButton("Сброс");
    set = new QPushButton("Установить время");

    nDate->setText("Дата: ");
    vYear->setRange(1601,30827);
    vYear->setValue(current_time.wYear);
    vMonth->addItem(QString("Январь"),QVariant(1));
    vMonth->addItem(QString("Февраль"),QVariant(2));
    vMonth->addItem(QString("Март"),QVariant(3));
    vMonth->addItem(QString("Апрель"),QVariant(4));
    vMonth->addItem(QString("Май"),QVariant(5));
    vMonth->addItem(QString("Июнь"),QVariant(6));
    vMonth->addItem(QString("Июль"),QVariant(7));
    vMonth->addItem(QString("Август"),QVariant(8));
    vMonth->addItem(QString("Сентябрь"),QVariant(9));
    vMonth->addItem(QString("Октябрь"),QVariant(10));
    vMonth->addItem(QString("Ноябрь"),QVariant(11));
    vMonth->addItem(QString("Декабрь"),QVariant(12));
    vMonth->setCurrentIndex(current_time.wMonth-1);
    vDay->setRange(1,31);
    vDay->setValue(current_time.wDay);

    nTime->setText("Время: ");
    vHour->setRange(0,23);
    vHour->setValue(current_time.wHour);
    vMinute->setRange(0,59);
    vMinute->setValue(current_time.wMinute);

    nDayOfWeek->setText("День недели: ");
    vDayOfWeek->addItem(QString("Воскресенье"),QVariant(0));
    vDayOfWeek->addItem(QString("Понедельник"),QVariant(1));
    vDayOfWeek->addItem(QString("Вторник"),QVariant(2));
    vDayOfWeek->addItem(QString("Среда"),QVariant(3));
    vDayOfWeek->addItem(QString("Четверг"),QVariant(4));
    vDayOfWeek->addItem(QString("Пятница"),QVariant(5));
    vDayOfWeek->addItem(QString("Суббота"),QVariant(6));
    vDayOfWeek->setCurrentIndex(current_time.wDayOfWeek);

    lDate->addWidget(vYear);
    lDate->addWidget(vMonth);
    lDate->addWidget(vDay);

    lTime->addWidget(vHour);
    lTime->addWidget(vMinute);

    lDayOfWeek->addWidget(nDayOfWeek);
    lDayOfWeek->addWidget(vDayOfWeek);

    lButtons->addWidget(set);
    lButtons->addWidget(reset);

    layout->addWidget(nDate);
    layout->addLayout(lDate);
    layout->addWidget(nTime);
    layout->addLayout(lTime);
    layout->addLayout(lDayOfWeek);
    if(editLock){
        vMonth->setEnabled(false);
        vDayOfWeek->setEnabled(false);
        vYear->setEnabled(false);
        vDay->setEnabled(false);
        vHour->setEnabled(false);
        vMinute->setEnabled(false);
    }
    else{
        layout->addLayout(lButtons);
    }
    this->setLayout(layout);

    connect(set,SIGNAL(pressed()),this,SLOT(s_set()));
    connect(reset,SIGNAL(pressed()),this,SLOT(s_reset()));
};

TimezoneInfo::TimezoneInfo(){
    TIME_ZONE_INFORMATION timeZone;
    DWORD CurrentBias = GetTimeZoneInformation(&timeZone);
    layout = new QVBoxLayout;
    
    lCurrentBias = new QHBoxLayout;
    lStandartBias = new QHBoxLayout;
    lDaylightBias = new QHBoxLayout;

    nCurrentBias = new QLabel("Текущее смещение (относительно UTC):");
    nStandartBias = new QLabel("Величина стандартного смещения:");
    nDaylightBias = new QLabel("Величина смещения после перевода часов:");
    vCurrentBias = new QLabel;
    vStandartBias = new QLabel;
    vDaylightBias = new QLabel;
    
    switch(CurrentBias){
        case TIME_ZONE_ID_UNKNOWN:
            vCurrentBias->setText("Перевод времени не используется");
            break;
        case TIME_ZONE_ID_STANDARD:
            vCurrentBias->setText("Часы без перевода");
            break;
        case TIME_ZONE_ID_DAYLIGHT:
            vCurrentBias->setText("Часы с переводом");
            break;        
    }
    vStandartBias->setText(QString::number(timeZone.StandardBias)+" мин.");
    vDaylightBias->setText(QString::number(timeZone.DaylightBias)+" мин.");
    
    lCurrentBias->addWidget(nCurrentBias);
    lCurrentBias->addWidget(vCurrentBias);
    lStandartBias->addWidget(nStandartBias);
    lStandartBias->addWidget(vStandartBias);
    lDaylightBias->addWidget(nDaylightBias);
    lDaylightBias->addWidget(vDaylightBias);
    layout->addLayout(lCurrentBias);
    layout->addLayout(lStandartBias);
    layout->addLayout(lDaylightBias);
    this->setLayout(layout);
};

SystemClock::SystemClock(){
    layout = new QVBoxLayout;

    GetSystemTime(&system_time); 
    GetLocalTime(&local_time); 
    
    systemTime = new SystemTime(true,system_time);
    localTime = new SystemTime(false,local_time);
    timeZone = new TimezoneInfo();

    layout->addWidget(new QLabel("Системное время: "));
    layout->addWidget(systemTime);
    layout->addWidget(new QLabel("Часовой пояс: "));
    layout->addWidget(timeZone);
    layout->addWidget(new QLabel("Локальное время: "));
    layout->addWidget(localTime);
    
    this->setLayout(layout);
};
