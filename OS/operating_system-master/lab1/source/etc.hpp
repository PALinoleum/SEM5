#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#include "systemInfo.hpp"
#pragma once

#define LANG_RUS 0x0419
#define LANG_ENG 0x0409

SHORT GetLanguageShort(HKL key);

QString codePages(int id);

QString languageId(SHORT languageId);

class SystemEtc : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QLineEdit *scomputerName;
        QPushButton *bcomputerName,*reset;
        QLabel *computerName,*ACP,*keyboardLayout;
        QLabel *nComputerName, *nACP,*nKeyboardLayout;      
        QHBoxLayout *lComputerName,*lSetComputerName,*lKeyboardLayout,*lACP;
        QPushButton *bSetComputerName;
        QLineEdit *vSetComputerName;
        QString DefaultComputerName;
        QString CurrentComputerName;
    public slots:
        void setComputerName();
        void s_reset();
    public:
        SystemEtc(); 
};

class PowerStatus:public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QHBoxLayout *lACLine,*lBatteryFlag,*lBatteryLifePercent,
                    *lSystemStatusFlag,*lBatteryLifeTime,*lBatteryFullLifeTime;
        QLabel *nACLine,*nBatteryFlag,*nBatteryLifePercent,
                    *nSystemStatusFlag,*nBatteryLifeTime,*nBatteryFullLifeTime;
        QLabel *ACLine,*BatteryFlag,*BatteryLifePercent,
                    *SystemStatusFlag,*BatteryLifeTime,*BatteryFullLifeTime;
    public:
        PowerStatus();
};
