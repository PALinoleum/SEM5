#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include "math.h"
#include <QPen>
#include <QPainter>
using namespace std;



class Chart : public QWidget
{
    Q_OBJECT
public:
    explicit Chart(QWidget *parent = nullptr);
    float globMAX=0;
    float a=3.777,b=3.99,step=0.0001;
    float offsetx=0, offsety=0;
    class CurveData
    {
        QColor curveColor; 	// Цвет кривой
        QPen curvePen;		// Стиль пера
    public:
        virtual double F(double x) { return 0; }; // Функция для рисования
    };

    // Массив указателей на структуры, содержащие информацию о функциях f(x)
    QVector<CurveData*> curves;

    // Функция устанавливает область определения графика функции
    void setRangeX(double x1, double x2);


    class SinCurveData : public CurveData
    {
    public:
        double F(double x) override
        {
            return sin(x);
        }
    };

    void redraw();


    class WorldToScreenConverter
    {
    public:
        // Экранная система координат
        double X1, X2, Y1, Y2;
        // Мировая система координат
        double x1, x2, y1, y2;
        // Функция преобразует координаты точки (x, y) из мировой системы координат в экранную
        QPoint convert(double x, double y);
        // Функция преобразует значение ординаты Y из экранной системы координат в мировую
        double y(int Y);
        // Функция возвращает значение абсциссы в мировой системе координат по её значению X в экранной
        double x(int X);
    };
    WorldToScreenConverter coords_converter;

private:
    QPainter painter;
    QRect srcwidgetsize, srcwindowsize;
    // Объект для преобразования мировых координат в экранные и наоборот
    void paintEvent(QPaintEvent* p_event);
    void resizeEvent(QResizeEvent* r_event);
signals:

public slots:
};

#endif // CHART_H


