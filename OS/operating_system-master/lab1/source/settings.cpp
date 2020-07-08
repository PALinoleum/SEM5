#include "settings.hpp"

void SystemSettings::setKeyboardDelay(){
    CurrentKeyboardDelay = SetKeyboardDelay->value();
    SystemParametersInfoA(SPI_SETKEYBOARDDELAY,CurrentKeyboardDelay,0,0);
    KeyboardDelay->setText(QString::number(CurrentKeyboardDelay));
};
void SystemSettings::setDoubleClickTime(){
    CurrentDoubleClickTime = SetDoubleClickDelay->value();
    SystemParametersInfoA(SPI_SETDOUBLECLICKTIME,CurrentDoubleClickTime,0,0);
    DoubleClickTime->setText(QString::number(CurrentDoubleClickTime)+" мс");
};
void SystemSettings::s_reset(){
    CurrentDoubleClickTime = DefaultDoubleClickTime;
    CurrentKeyboardDelay = DefaultKeyboardDelay;
    SystemParametersInfoA(SPI_SETKEYBOARDDELAY,CurrentKeyboardDelay,0,0);
    SystemParametersInfoA(SPI_SETDOUBLECLICKTIME,CurrentDoubleClickTime,0,0);
    SetKeyboardDelay->setValue(DefaultDoubleClickTime);
    SetDoubleClickDelay->setValue(DefaultKeyboardDelay);
    DoubleClickTime->setText(QString::number(CurrentDoubleClickTime)+" мс");
    KeyboardDelay->setText(QString::number(CurrentKeyboardDelay));
};

QString QT_GetFontSmoothing(){
    QString result;
    BOOL flag;
    SystemParametersInfo(SPI_GETFONTSMOOTHING,0,&flag,0);
    if(flag == TRUE){
        result = "Включено";
    }
    else{
        result = "Выключено";
    }
    return result;
};

QString QT_GetMouseOvertime(){
    QString result;
    UINT value;
    SystemParametersInfo(SPI_GETMOUSEHOVERTIME,0,&value,0);
    result = QString::number(value)+" мс";
    return result;
};

QString QT_GetToggleKeys(){
    QString result;
    TOGGLEKEYS value;
    SystemParametersInfo(SPI_GETTOGGLEKEYS,0,&value,0);
    bool flag = ( ((value.dwFlags) & ( 0x1 << (0x00000002) )) !=0 );
    if(flag){
        result = "Включено";
    }
    else{
        result = "Выключено";
    }
    return result;
};

SystemSettings::SystemSettings(){
    QVBoxLayout *layout = new QVBoxLayout;
    
    lFontSmoothing = new QHBoxLayout;
    lMouseOvertime = new QHBoxLayout;
    lToggleKeys = new QHBoxLayout;
    lDoubleClickDelay = new QHBoxLayout;
    lKeyboardDelay = new QHBoxLayout;
    lSetDoubleClickTime = new QHBoxLayout;
    lSetKeyboardDelay = new QHBoxLayout;

    nFontSmoothing = new QLabel;
    nMouseOvertime = new QLabel;
    nToggleKeys = new QLabel;
    nDoubleClickTime = new QLabel;
    nKeyboardDelay = new QLabel;
    
    FontSmoothing = new QLabel;
    MouseOvertime = new QLabel;
    ToggleKeys = new QLabel;
    DoubleClickTime = new QLabel;
    KeyboardDelay = new QLabel;

    ButtonKeyboardDelay = new QPushButton("Установить");
    ButtonDoubleClickDelay = new QPushButton("Установить");
    reset = new QPushButton("Сброс");

    SetDoubleClickDelay = new QSpinBox;
    SetDoubleClickDelay->setSuffix(" мс");
    SetDoubleClickDelay->setSingleStep(10);
    SetDoubleClickDelay->setMinimum(10);
    SetDoubleClickDelay->setMaximum(5000); 

    SetKeyboardDelay = new QSpinBox;
    SetKeyboardDelay->setMinimum(0);
    SetKeyboardDelay->setMaximum(3);

    DefaultDoubleClickTime = GetDoubleClickTime();
    CurrentDoubleClickTime = DefaultDoubleClickTime;

    SystemParametersInfoA(SPI_GETKEYBOARDDELAY,0,&DefaultKeyboardDelay,0);
    CurrentKeyboardDelay = DefaultKeyboardDelay;

    nFontSmoothing->setText("Сглаживание шрифтов: ");
    nMouseOvertime->setText("Mouse Overtime: ");
    nToggleKeys->setText("Звуковое оповещение о включении lock-клавиш: ");
    nDoubleClickTime->setText("Промежуток срабатывания двойного клика: ");
    nKeyboardDelay->setText("Задержка клавиатуры (0-3) (0 - 250мс, 1 ед. - 250мс): ");

    FontSmoothing->setText(QT_GetFontSmoothing());
    MouseOvertime->setText(QT_GetMouseOvertime());
    ToggleKeys->setText(QT_GetToggleKeys());
    DoubleClickTime->setText(QString::number(CurrentDoubleClickTime)+" мс");
    KeyboardDelay->setText(QString::number(CurrentKeyboardDelay));

    lFontSmoothing->addWidget(nFontSmoothing);
    lFontSmoothing->addWidget(FontSmoothing);
    lMouseOvertime->addWidget(nMouseOvertime);
    lMouseOvertime->addWidget(MouseOvertime);
    lToggleKeys->addWidget(nToggleKeys);
    lToggleKeys->addWidget(ToggleKeys);
    lDoubleClickDelay->addWidget(nDoubleClickTime);
    lDoubleClickDelay->addWidget(DoubleClickTime);
    lKeyboardDelay->addWidget(nKeyboardDelay);
    lKeyboardDelay->addWidget(KeyboardDelay);
    lSetDoubleClickTime->addWidget(SetDoubleClickDelay);
    lSetDoubleClickTime->addWidget(ButtonDoubleClickDelay);
    lSetKeyboardDelay->addWidget(SetKeyboardDelay);
    lSetKeyboardDelay->addWidget(ButtonKeyboardDelay);

    layout->addLayout(lFontSmoothing);
    layout->addLayout(lMouseOvertime);
    layout->addLayout(lToggleKeys);
    layout->addLayout(lDoubleClickDelay);
    layout->addLayout(lSetDoubleClickTime);
    layout->addLayout(lKeyboardDelay);
    layout->addLayout(lSetKeyboardDelay);
    layout->addWidget(reset);

    this->setLayout(layout);

    connect(reset,SIGNAL(clicked()),this,SLOT(s_reset()));
    connect(ButtonKeyboardDelay,SIGNAL(pressed()),this,SLOT(setKeyboardDelay()));
    connect(ButtonDoubleClickDelay,SIGNAL(pressed()),this,SLOT(setDoubleClickTime()));
};
