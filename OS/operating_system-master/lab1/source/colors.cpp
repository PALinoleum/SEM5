#include "colors.hpp"

void SystemColors::set_color1(){
    QColor color = QColorDialog::getColor();
    QT_SetSysColor(COLOR_3DSHADOW,color);
    c_3DShadow.setColor(QPalette::Background,color);
    v_3DShadow->setPalette(c_3DShadow);
    this->update();
};
void SystemColors::set_color2(){
    QColor color = QColorDialog::getColor();
    QT_SetSysColor(COLOR_INFOBK,color);
    c_infobk.setColor(QPalette::Background,color);
    v_infobk->setPalette(c_infobk);
    this->update();
};
void SystemColors::set_color3(){
    QColor color = QColorDialog::getColor();
    QT_SetSysColor(COLOR_MENU,color);
    c_menu.setColor(QPalette::Background,color);
    v_menu->setPalette(c_menu);
    this->update();
};
void SystemColors::s_reset(){

    QT_SetSysColor(COLOR_3DSHADOW,default_3DShadow.color(QPalette::Background));
    QT_SetSysColor(COLOR_INFOBK,default_infobk.color(QPalette::Background));
    QT_SetSysColor(COLOR_MENU,default_menu.color(QPalette::Background));

    c_3DShadow = default_3DShadow;
    v_3DShadow->setPalette(c_3DShadow);

    c_infobk = default_infobk;
    v_infobk->setPalette(c_infobk);

    c_menu = default_menu;
    v_menu->setPalette(c_menu);
    this->update();
};

QColor QT_GetSysColor(int index){
    QColor color;
    DWORD WIN_color;
    WIN_color = GetSysColor(index);
    int WIN_colorRed = GetRValue(WIN_color);
    int WIN_colorBlue = GetBValue(WIN_color);
    int WIN_colorGreen = GetGValue(WIN_color);
    color.setRgb(WIN_colorRed,WIN_colorGreen,WIN_colorBlue);
    return color;
};

void QT_SetSysColor(int index,QColor color){
    int red,green,blue;
    red = color.red();
    green = color.green();
    blue = color.blue();
    DWORD WIN_color = RGB(red,green,blue);
    SetSysColors(1,&index,&WIN_color);
};

SystemColors::SystemColors(){
    default_3DShadow.setColor(QPalette::Background,QT_GetSysColor(COLOR_3DSHADOW));
    default_infobk.setColor(QPalette::Background,QT_GetSysColor(COLOR_INFOBK));
    default_menu.setColor(QPalette::Background,QT_GetSysColor(COLOR_MENU));
    c_3DShadow = default_3DShadow;
    c_infobk = default_infobk;
    c_menu = default_menu;

    layout = new QVBoxLayout;
    
    l_3DShadow = new QHBoxLayout;
    l_infobk = new QHBoxLayout;
    l_menu = new QHBoxLayout;

    reset = new QPushButton("Сброс");
    b_3DShadow = new QPushButton("Выбор цвета");
    b_infobk = new QPushButton("Выбор цвета");
    b_menu = new QPushButton("Выбор цвета");

    n_3DShadow = new QLabel;
    n_infobk = new QLabel;
    n_menu = new QLabel;
    v_3DShadow = new QLabel;
    v_infobk = new QLabel;
    v_menu = new QLabel;
    
    v_3DShadow->setAutoFillBackground(true);
    v_3DShadow->setPalette(c_3DShadow); 
    
    v_infobk->setAutoFillBackground(true); 
    v_infobk->setPalette(c_infobk); 
    
    v_menu->setAutoFillBackground(true); 
    v_menu->setPalette(c_menu); 
    
    n_3DShadow->setText("COLOR 3DSHADOW");
    n_infobk->setText("COLOR INFOBK");
    n_menu->setText("COLOR MENU");
    
    v_3DShadow->setText("3DSHADOW");
    v_3DShadow->setAlignment(Qt::AlignVCenter);
    v_infobk->setText("INFOBK");
    v_infobk->setAlignment(Qt::AlignVCenter);
    v_menu->setText("MENU");
    v_menu->setAlignment(Qt::AlignVCenter);
    
    l_3DShadow->addWidget(n_3DShadow);
    l_3DShadow->addWidget(v_3DShadow);
    l_infobk->addWidget(n_infobk);
    l_infobk->addWidget(v_infobk);
    l_menu->addWidget(n_menu);
    l_menu->addWidget(v_menu);

    layout->addLayout(l_3DShadow);
    layout->addWidget(b_3DShadow);
    layout->addLayout(l_infobk);
    layout->addWidget(b_infobk);
    layout->addLayout(l_menu);
    layout->addWidget(b_menu);
    layout->addWidget(reset);
    this->setLayout(layout);
    connect(b_3DShadow,SIGNAL(pressed()),this,SLOT(set_color1()));
    connect(b_infobk,SIGNAL(pressed()),this,SLOT(set_color2()));
    connect(b_menu,SIGNAL(pressed()),this,SLOT(set_color3()));
    connect(reset,SIGNAL(pressed()),this,SLOT(s_reset()));
};
