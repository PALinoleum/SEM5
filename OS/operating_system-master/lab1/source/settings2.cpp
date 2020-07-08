#include "settings2.hpp"

void SystemSettings2::s_set(){
    CurrentNonClientMetrics.iBorderWidth = bBorderWidth->value();
    CurrentNonClientMetrics.iScrollWidth = bScrollWidth->value();
    CurrentNonClientMetrics.iScrollHeight = bScrollHeight->value();
    CurrentNonClientMetrics.iCaptionWidth = bCaptionWidth->value();
    CurrentNonClientMetrics.iCaptionHeight = bCaptionHeight->value();
    CurrentNonClientMetrics.iSmCaptionWidth = bSmCaptionWidth->value();
    CurrentNonClientMetrics.iSmCaptionHeight = bSmCaptionHeight->value();
    CurrentNonClientMetrics.iMenuWidth = bMenuWidth->value();
    CurrentNonClientMetrics.iMenuHeight = bMenuHeight->value();
    SystemParametersInfoA(SPI_SETNONCLIENTMETRICS,0,&CurrentNonClientMetrics,0);
};

void SystemSettings2::s_reset(){
    SystemParametersInfoA(SPI_SETNONCLIENTMETRICS,0,&DefaultNonClientMetrics,0);
    CurrentNonClientMetrics.iBorderWidth = DefaultNonClientMetrics.iBorderWidth;
    CurrentNonClientMetrics.iScrollWidth = DefaultNonClientMetrics.iScrollWidth;
    CurrentNonClientMetrics.iScrollHeight = DefaultNonClientMetrics.iScrollHeight;
    CurrentNonClientMetrics.iCaptionWidth = DefaultNonClientMetrics.iCaptionWidth;
    CurrentNonClientMetrics.iCaptionHeight = DefaultNonClientMetrics.iCaptionHeight;
    CurrentNonClientMetrics.iSmCaptionWidth = DefaultNonClientMetrics.iSmCaptionWidth;
    CurrentNonClientMetrics.iSmCaptionHeight = DefaultNonClientMetrics.iSmCaptionHeight;
    CurrentNonClientMetrics.iMenuWidth = DefaultNonClientMetrics.iMenuWidth;
    CurrentNonClientMetrics.iMenuHeight = DefaultNonClientMetrics.iMenuHeight;
    bBorderWidth->setValue(CurrentNonClientMetrics.iBorderWidth);
    bScrollWidth->setValue(CurrentNonClientMetrics.iScrollWidth);
    bScrollHeight->setValue(CurrentNonClientMetrics.iScrollHeight);
    bCaptionWidth->setValue(CurrentNonClientMetrics.iCaptionWidth);
    bCaptionHeight->setValue(CurrentNonClientMetrics.iCaptionHeight);
    bSmCaptionWidth->setValue(CurrentNonClientMetrics.iSmCaptionWidth);
    bSmCaptionHeight->setValue(CurrentNonClientMetrics.iSmCaptionHeight);
    bMenuWidth->setValue(CurrentNonClientMetrics.iMenuWidth);
    bMenuHeight->setValue(CurrentNonClientMetrics.iMenuHeight);
};

SystemSettings2::SystemSettings2(){
    QVBoxLayout *layout = new QVBoxLayout;
    SystemParametersInfoA(SPI_GETNONCLIENTMETRICS,0,&DefaultNonClientMetrics,0);
    DefaultNonClientMetrics.cbSize=sizeof(NONCLIENTMETRICSA);
    CurrentNonClientMetrics.cbSize=sizeof(NONCLIENTMETRICSA);


    set = new QPushButton("Установить");
    reset = new QPushButton("Сброс");

    CurrentNonClientMetrics.iBorderWidth = DefaultNonClientMetrics.iBorderWidth;
    CurrentNonClientMetrics.iScrollWidth = DefaultNonClientMetrics.iScrollWidth;
    CurrentNonClientMetrics.iScrollHeight = DefaultNonClientMetrics.iScrollHeight;
    CurrentNonClientMetrics.iCaptionWidth = DefaultNonClientMetrics.iCaptionWidth;
    CurrentNonClientMetrics.iCaptionHeight = DefaultNonClientMetrics.iCaptionHeight;
    CurrentNonClientMetrics.iSmCaptionWidth = DefaultNonClientMetrics.iSmCaptionWidth;
    CurrentNonClientMetrics.iSmCaptionHeight = DefaultNonClientMetrics.iSmCaptionHeight;
    CurrentNonClientMetrics.iMenuWidth = DefaultNonClientMetrics.iMenuWidth;
    CurrentNonClientMetrics.iMenuHeight = DefaultNonClientMetrics.iMenuHeight;

    lBorderWidth = new QHBoxLayout;
    lScrollWidth = new QHBoxLayout;
    lScrollHeight = new QHBoxLayout;
    lCaptionWidth = new QHBoxLayout;
    lCaptionHeight = new QHBoxLayout;
    lSmCaptionWidth = new QHBoxLayout;
    lSmCaptionHeight = new QHBoxLayout;
    lMenuWidth = new QHBoxLayout;
    lMenuHeight = new QHBoxLayout;
    lButton = new QHBoxLayout;
    
    nBorderWidth = new QLabel;      nBorderWidth->setText("BorderWidth");
    nScrollWidth = new QLabel;      nScrollWidth->setText("ScrollWidth");
    nScrollHeight = new QLabel;     nScrollHeight->setText("ScrollHeight");
    nCaptionWidth = new QLabel;     nCaptionWidth->setText("CaptionWidth");
    nCaptionHeight = new QLabel;    nCaptionHeight->setText("CaptionHeight");
    nSmCaptionWidth = new QLabel;   nSmCaptionWidth->setText("SmCaptionWidth");
    nSmCaptionHeight = new QLabel;  nSmCaptionHeight->setText("SmCaptionHeight");
    nMenuWidth = new QLabel;        nMenuWidth->setText("MenuWidth");
    nMenuHeight = new QLabel;       nMenuHeight->setText("MenuHeight");

    bBorderWidth = new QSpinBox;
    bBorderWidth->setRange(1,100);
    bBorderWidth->setValue(CurrentNonClientMetrics.iBorderWidth);
    bScrollWidth = new QSpinBox;
    bScrollWidth->setRange(1,100);
    bScrollWidth->setValue(CurrentNonClientMetrics.iScrollWidth);
    bScrollHeight = new QSpinBox;
    bScrollHeight->setRange(1,100);
    bScrollHeight->setValue(CurrentNonClientMetrics.iScrollHeight);
    bCaptionWidth = new QSpinBox;
    bCaptionWidth->setRange(1,100);
    bCaptionWidth->setValue(CurrentNonClientMetrics.iCaptionWidth);
    bCaptionHeight = new QSpinBox;
    bCaptionHeight->setRange(1,100);
    bCaptionHeight->setValue(CurrentNonClientMetrics.iCaptionHeight);
    bSmCaptionWidth = new QSpinBox;
    bSmCaptionWidth->setRange(1,100);
    bSmCaptionWidth->setValue(CurrentNonClientMetrics.iSmCaptionWidth);
    bSmCaptionHeight = new QSpinBox;
    bSmCaptionHeight->setRange(1,100);
    bSmCaptionHeight->setValue(CurrentNonClientMetrics.iSmCaptionHeight);
    bMenuWidth = new QSpinBox;
    bMenuWidth->setRange(1,100);
    bMenuWidth->setValue(CurrentNonClientMetrics.iMenuWidth);
    bMenuHeight = new QSpinBox;
    bMenuHeight->setRange(1,100);
    bMenuHeight->setValue(CurrentNonClientMetrics.iMenuHeight);
    
    lBorderWidth->addWidget(nBorderWidth);         lBorderWidth->addWidget(bBorderWidth);
    lScrollWidth->addWidget(nScrollWidth);         lScrollWidth->addWidget(bScrollWidth);
    lScrollHeight->addWidget(nScrollHeight);       lScrollHeight->addWidget(bScrollHeight);
    lCaptionWidth->addWidget(nCaptionWidth);       lCaptionWidth->addWidget(bCaptionWidth);
    lCaptionHeight->addWidget(nCaptionHeight);     lCaptionHeight->addWidget(bCaptionHeight);
    lSmCaptionWidth->addWidget(nSmCaptionWidth);   lSmCaptionWidth->addWidget(bSmCaptionWidth);
    lSmCaptionHeight->addWidget(nSmCaptionHeight); lSmCaptionHeight->addWidget(bSmCaptionHeight);
    lMenuWidth->addWidget(nMenuWidth);             lMenuWidth->addWidget(bMenuWidth);
    lMenuHeight->addWidget(nMenuHeight);           lMenuHeight->addWidget(bMenuHeight);
    lButton->addWidget(set);
    lButton->addWidget(reset);

    layout->addLayout(lBorderWidth);
    layout->addLayout(lScrollWidth);
    layout->addLayout(lScrollHeight);
    layout->addLayout(lCaptionWidth);
    layout->addLayout(lCaptionHeight);
    layout->addLayout(lSmCaptionWidth);
    layout->addLayout(lSmCaptionHeight);
    layout->addLayout(lMenuWidth);
    layout->addLayout(lMenuHeight);
    layout->addLayout(lButton);

    this->setLayout(layout);

    connect(set,SIGNAL(pressed()),this,SLOT(s_set()));
    connect(reset,SIGNAL(pressed()),this,SLOT(s_reset()));
};
