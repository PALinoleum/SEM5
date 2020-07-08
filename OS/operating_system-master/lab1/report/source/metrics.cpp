#include "metrics.hpp"

void QT_GetSystemMetrics(QTableWidget* table,int row,int index,QString header,QString suffix){
    int result = GetSystemMetrics(index);
    QTableWidgetItem* nameItem = new QTableWidgetItem(header);
    QTableWidgetItem* valueItem;
    table->setItem(row,0,nameItem);
    if (result==0){
        valueItem = new QTableWidgetItem(QString("Ошибка чтения"));
        table->setItem(row,1,valueItem);
    }
    else{
        valueItem = new QTableWidgetItem(QString::number(result)+" "+suffix);
        table->setItem(row,1,valueItem);
    }
};

void QT_GetSystemMetricBoot(QTableWidget* table,int row){
    int result = GetSystemMetrics(SM_CLEANBOOT);
    QTableWidgetItem* nameItem = new QTableWidgetItem(QString("Режим загрузки"));
    QTableWidgetItem* valueItem;
    table->setItem(row,0,nameItem);
    switch (result){
        case 0:
            valueItem = new QTableWidgetItem(QString("Нормальная загрузка"));
            break;
        case 1:
            valueItem = new QTableWidgetItem(QString("Безопасная загрузка"));
            break;
        case 2:
            valueItem = new QTableWidgetItem(QString("Безопасная загрузка с поддержкой сетевых драйверов"));
            break;
        };
    table->setItem(row,1,valueItem);
}; 

void QT_GetSystemMetricsBool(QTableWidget* table,int row,int index,QString header){
    int result = GetSystemMetrics(index);
    QTableWidgetItem* nameItem = new QTableWidgetItem(header);
    QTableWidgetItem* valueItem;
    table->setItem(row,0,nameItem);
    if (result==0){
        valueItem = new QTableWidgetItem(QString("Нет"));
        table->setItem(row,1,valueItem);
    }
    else{
        valueItem = new QTableWidgetItem(QString("Да"));
        table->setItem(row,1,valueItem);
    }
};
SystemMetrics::SystemMetrics(){
    QVBoxLayout *layout = new QVBoxLayout;
    table = new QTableWidget;
    table->setRowCount(50);
    table->setColumnCount(2);
    table->setColumnWidth(0,230);
    table->setColumnWidth(1,145);
    table->setHorizontalHeaderLabels({"Название метрики","Значение"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QT_GetSystemMetricsBool(table,0,SM_SWAPBUTTON,QString("Замена назначения клавиш мыши"));
    QT_GetSystemMetricBoot(table,1);
    QT_GetSystemMetrics(table,2,SM_CMONITORS,QString("Количество мониторов"),QString("scr"));
    QT_GetSystemMetrics(table,3,SM_CMOUSEBUTTONS,QString("Количество кнопок мыши"),QString("btn"));
    QT_GetSystemMetrics(table,4,SM_CXBORDER,QString("Ширина рамки окна"),QString("px"));
    QT_GetSystemMetrics(table,5,SM_CXCURSOR,QString("Ширина курсора"),QString("px"));
    QT_GetSystemMetrics(table,6,SM_CXDLGFRAME,QString("Ширина рамки вокруг окна"),QString("px"));
    QT_GetSystemMetrics(table,7,SM_CXDOUBLECLK,QString("Ширина области двойного нажатия"),QString("px"));
    QT_GetSystemMetrics(table,8,SM_CXDRAG,QString("Ширина области Drag and drop"),QString("px"));
    QT_GetSystemMetrics(table,9,SM_CXEDGE,QString("Ширина 3D рамки окна"),QString("px"));
    QT_GetSystemMetrics(table,10,SM_CXFIXEDFRAME,QString("Ширина рамки вокруг окна (альтернативная метрика)"),QString("px"));
    QT_GetSystemMetrics(table,11,SM_CXFOCUSBORDER,QString("Ширина Focus Border"),QString("px"));
    QT_GetSystemMetrics(table,12,SM_CXFRAME,QString("Ширина полосы маштибирования окна"),QString("px"));
    QT_GetSystemMetrics(table,13,SM_CXFULLSCREEN,QString("Ширина основного экрана в режиме полного экрана"),QString("px"));
    QT_GetSystemMetrics(table,14,SM_CXHSCROLL,QString("Ширина кнопки полосы прокрутки"),QString("px"));
    QT_GetSystemMetrics(table,15,SM_CXHTHUMB,QString("Ширина полосы прокрутки"),QString("px"));
    QT_GetSystemMetrics(table,16,SM_CXICON,QString("Ширина иконки"),QString("px"));
    QT_GetSystemMetrics(table,17,SM_CXICONSPACING,QString("Ширина ячейки сетки иконок"),QString("px"));
    QT_GetSystemMetrics(table,18,SM_CXMAXIMIZED,QString("Ширина развернутого окна"),QString("px"));
    QT_GetSystemMetrics(table,19,SM_CXMAXTRACK,QString("Максимальная ширина окна с учетом рамок"),QString("px"));
    QT_GetSystemMetrics(table,20,SM_CXMENUCHECK,QString("Ширина контекстного меню"),QString("px"));
    QT_GetSystemMetrics(table,21,SM_CXMENUSIZE,QString("Ширина кнопок меню"),QString("px"));
    QT_GetSystemMetrics(table,22,SM_CXMIN,QString("Минимальная ширина окна"),QString("px"));
    QT_GetSystemMetrics(table,23,SM_CXMINIMIZED,QString("Ширина минимизированного окна"),QString("px"));
    QT_GetSystemMetrics(table,24,SM_CXMINSPACING,QString("Ширина сетки минимизированного окна"),QString("px"));
    QT_GetSystemMetrics(table,25,SM_CXMINTRACK,QString("Минимальная ширина для перетаскивания окна"),QString("px"));
    QT_GetSystemMetrics(table,26,SM_CXSCREEN,QString("Ширина основного экрана"),QString("px"));
    QT_GetSystemMetrics(table,27,SM_CXSIZE,QString("Ширина кнопки в заголовке окна"),QString("px"));
    QT_GetSystemMetrics(table,28,SM_CXSIZEFRAME,QString("Ширина полосы маштибирования окна (альтернативная метрика)"),QString("px"));
    QT_GetSystemMetrics(table,29,SM_CXSMICON,QString("Рекомендованная ширина иконки (иконка в заголовке окна)"),QString("px"));
    QT_GetSystemMetrics(table,30,SM_CXSMSIZE,QString("Ширина кнопок управления окном"),QString("px"));
    QT_GetSystemMetrics(table,31,SM_CXVIRTUALSCREEN,QString("Сумма ширины всех экранов"),QString("px"));
    QT_GetSystemMetrics(table,32,SM_CXVSCROLL,QString("Ширина полосы прокрутки"),QString("px"));
    QT_GetSystemMetrics(table,33,SM_CYBORDER,QString("Высота рамки окна"),QString("px"));
    QT_GetSystemMetrics(table,34,SM_CYCAPTION,QString("Высота заголовка окна"),QString("px"));
    QT_GetSystemMetrics(table,35,SM_CYCURSOR,QString("Высота курсора"),QString("px"));
    QT_GetSystemMetrics(table,36,SM_CYDLGFRAME,QString("Высота рамки вокруг окна"),QString("px"));
    QT_GetSystemMetrics(table,37,SM_CYDOUBLECLK,QString("Высота области двойного нажатия"),QString("px"));
    QT_GetSystemMetrics(table,38,SM_CYDRAG,QString("Высота области Drag and drop"),QString("px"));
    QT_GetSystemMetrics(table,39,SM_CYEDGE,QString("Высота 3D рамки окна"),QString("px"));
    QT_GetSystemMetrics(table,40,SM_CYFIXEDFRAME,QString("Высота рамки вокруг окна (альтернативная метрика)"),QString("px"));
    QT_GetSystemMetrics(table,41,SM_CYFOCUSBORDER,QString("Высота Focus Border"),QString("px"));
    QT_GetSystemMetrics(table,42,SM_CYFRAME,QString("Высота полосы маштибирования окна"),QString("px"));
    QT_GetSystemMetrics(table,43,SM_CYFULLSCREEN,QString("Высота основного экрана в режиме полного экрана"),QString("px"));
    QT_GetSystemMetrics(table,44,SM_CYMENUCHECK,QString("Высота контекстного меню"),QString("px"));
    QT_GetSystemMetrics(table,45,SM_CYHSCROLL,QString("Высота кнопки полосы прокрутки"),QString("px"));
    QT_GetSystemMetrics(table,46,SM_CYICON,QString("Высота иконки"),QString("px"));
    QT_GetSystemMetrics(table,47,SM_CYICONSPACING,QString("Высота ячейки сетки иконок"),QString("px"));
    QT_GetSystemMetrics(table,48,SM_CYMAXIMIZED,QString("Высота развернутого окна"),QString("px"));
    QT_GetSystemMetrics(table,49,SM_CYMAXTRACK,QString("Максимальная высота окна с учетом рамок"),QString("px"));
    table->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    layout->addWidget(table);
    this->setLayout(layout);
};