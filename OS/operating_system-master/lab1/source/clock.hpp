#include <QtWidgets>
#include <windows.h>
#include <wchar.h>

class SystemTime: public QWidget{
    Q_OBJECT
    private:
        bool editLock;
        SYSTEMTIME current_time,default_time;
        QVBoxLayout *layout;
        QHBoxLayout *lDate,*lTime,*lDayOfWeek,*lButtons;
        QLabel *nDate,*nTime,*nDayOfWeek;
        QComboBox *vDayOfWeek,*vMonth;
        QSpinBox *vYear,*vDay,*vHour,*vMinute;
        QPushButton *reset,*set;
    public slots:
        void s_set();
        void s_reset();
    public:
        SystemTime(bool editLock,SYSTEMTIME time);
};

class TimezoneInfo: public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QHBoxLayout *lCurrentBias,*lStandartBias,*lDaylightBias;
        QLabel *nCurrentBias,*nStandartBias,*nDaylightBias,
               *vCurrentBias,*vStandartBias,*vDaylightBias;
    public:
        TimezoneInfo();
};

class SystemClock: public QWidget{
    Q_OBJECT
    private:
        SYSTEMTIME system_time;
        SYSTEMTIME local_time;
        SYSTEMTIME default_local_time;
        QVBoxLayout *layout;
        SystemTime *systemTime,*localTime;
        TimezoneInfo *timeZone;
    public:
        SystemClock();
};
