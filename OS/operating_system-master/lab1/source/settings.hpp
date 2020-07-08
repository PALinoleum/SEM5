#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#pragma once

#define SPI_GETFONTSMOOTHING 0x004A
#define SPI_GETMOUSEHOVERTIME 0x0066
#define SPI_GETTOGGLEKEYS 0x0034
#define SPI_SETDOUBLECLICKTIME 0x0020
#define SPI_SETKEYBOARDDELAY 0x0017
#define SPI_GETKEYBOARDDELAY 0x0016


QString QT_GetFontSmoothing();
QString QT_GetMouseOvertime();
QString QT_GetToggleKeys();

class SystemSettings : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QHBoxLayout *lFontSmoothing,*lMouseOvertime,*lToggleKeys,
                    *lDoubleClickDelay,*lKeyboardDelay,
                    *lSetDoubleClickTime,*lSetKeyboardDelay;
        QLabel *nFontSmoothing,*nMouseOvertime,*nToggleKeys,
               *nDoubleClickTime,*nKeyboardDelay;
        QLabel *FontSmoothing,*MouseOvertime,*ToggleKeys,
               *DoubleClickTime,*KeyboardDelay;
        QSpinBox *SetDoubleClickDelay,*SetKeyboardDelay;
        QPushButton *ButtonDoubleClickDelay,*ButtonKeyboardDelay,*reset;
        UINT DefaultDoubleClickTime;
        int DefaultKeyboardDelay;
        UINT CurrentDoubleClickTime;
        int CurrentKeyboardDelay;
    public:
        SystemSettings(); 
    public slots:
        void setKeyboardDelay();
        void setDoubleClickTime();
        void s_reset();
};
