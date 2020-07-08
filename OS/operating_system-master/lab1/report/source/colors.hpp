#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#pragma once

#define COLOR_INFOBK 24
#define COLOR_MENU 4

QColor QT_GetSysColor(int index);
void QT_SetSysColor(int index,QColor color);

class SystemColors : public QWidget{
    Q_OBJECT
    private:
    QVBoxLayout *layout;
    QHBoxLayout *l_3DShadow,*l_infobk,*l_menu;
    QLabel *color1,color2,color3;
    QPalette default_3DShadow,default_infobk,default_menu;
    QPalette c_3DShadow,c_infobk,c_menu;
    QLabel *n_3DShadow,*n_infobk,*n_menu,
           *v_3DShadow,*v_infobk,*v_menu;
    QPushButton *b_3DShadow,*b_infobk,*b_menu,*reset;
    public:
        SystemColors(); 
    public slots:
        void set_color1();
        void set_color2();
        void set_color3();
        void s_reset();
};
