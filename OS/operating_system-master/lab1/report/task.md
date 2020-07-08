Разработать программное обеспечение приложения, обеспечивающего получение следующей системной информации:

* Имя компьютера, имя пользователя;

* Пути к системным каталогам Windows;

* Версия операционной системы;

* Системные метрики (не менее 50 метрик);

* Системные параметры:
  * **SPI_GETFONTSMOOTHING**
  * **SPI_GETMOUSEHOVERTIME**
  * **SPI_GETTOGGLEKEYS**
  * **SPI_SETDOUBLECLICKTIME**
  * **SPI_SETKEYBOARDDELAY**
  * **SPI_SETNONCLIENTMETRICS**
* Системные цвета (*определить цвет для следующих символьных констант и изменить его на любой другой*):
  * **COLOR_3DSHADOW**
  * **COLOR_INFOBK**
  * **COLOR_MENU**
* Функции для работы со временем:
  * **GetSystemTime**
  * **GetTimeZonelnformation**
  * **SetLocalTime**
* Дополнительные API-функции:
  * **GetACP, GetKeyboardLayout**
  * **GetSystemPowerStatus**
  * **SetComputerName**