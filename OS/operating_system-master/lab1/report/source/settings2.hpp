#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

#pragma once

#define SPI_SETNONCLIENTMETRICS 0x002A
#define SPI_GETNONCLIENTMETRICS 0x0029

class SystemSettings2 : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        NONCLIENTMETRICSA DefaultNonClientMetrics;
        NONCLIENTMETRICSA CurrentNonClientMetrics;
        QHBoxLayout *lBorderWidth,*lScrollWidth,*lScrollHeight,
                    *lCaptionWidth,*lCaptionHeight,*lSmCaptionWidth,
                    *lSmCaptionHeight,*lMenuWidth,*lMenuHeight,*lButton;
        QLabel *nBorderWidth,*nScrollWidth,*nScrollHeight,
               *nCaptionWidth,*nCaptionHeight,*nSmCaptionWidth,
               *nSmCaptionHeight,*nMenuWidth,*nMenuHeight;
        QSpinBox *bBorderWidth,*bScrollWidth,*bScrollHeight,
                 *bCaptionWidth,*bCaptionHeight,*bSmCaptionWidth,
                 *bSmCaptionHeight,*bMenuWidth,*bMenuHeight;
        QPushButton *set,*reset;
    public slots:
        void s_set();
        void s_reset();
    public:
        SystemSettings2(); 
};
