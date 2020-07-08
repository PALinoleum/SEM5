#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "matrix.h"
#include "math.h"

#define M_PI   3.14159265358979323846

// Возвращает точку point повернутую вокруг центра center на dgr градусов по часовой стрелке
QPointF rotatePoint(QPointF center, QPointF point, double dgr){
    QPointF p;
    double px = point.x() - center.x();
    double py = point.y() - center.y();
    double sn = sin((dgr * M_PI)/180),
           cs = cos((dgr * M_PI)/180);
    p.setX(center.x() + px * cs - py * sn);
    p.setY(center.y() + py * cs + px * sn);
    return p;
}

QPointF movePoint(QPointF point,qreal deltaX,qreal deltaY){
    return (moveMatrix3x3(deltaX,deltaY)*Vectorx3(point)).qPointF();
};
QPointF rotatePoint(QPointF point,qreal angle){
    return (rotateMatrix3x3(angle)*Vectorx3(point)).qPointF();
};
QPointF scalePoint(QPointF point,qreal scaleX,qreal scaleY){
    return (scaleMatrix3x3(scaleX,scaleY)*Vectorx3(point)).qPointF();
};
QPointF mirrorPoint(QPointF point,bool x,bool y){
    return (mirrorMatrix3x3(x,y)*Vectorx3(point)).qPointF();
};

QPolygonF rotateQPolygonF(QPolygonF poly,qreal angle){
    QPolygonF result;
    for(auto i=poly.begin();i!=poly.end();i++){
        result<<rotatePoint(*i,angle);
    };
    return result;
};

QPolygonF moveQPolygonF(QPolygonF poly,qreal deltaX,qreal deltaY){
    QPolygonF result;
    for(auto i=poly.begin();i!=poly.end();i++){
        result<<movePoint(*i,deltaX,deltaY);
    };
    return result;
};
QPolygonF mirrorQPolygonF(QPolygonF poly,bool x,bool y){
    QPolygonF result;
    for(auto i=poly.begin();i!=poly.end();i++){
        result<<mirrorPoint(*i,x,y);
    };
    return result;
};
QPolygonF scaleQPolygonF(QPolygonF poly,qreal scaleX,qreal scaleY){
    QPolygonF result;
    for(auto i=poly.begin();i!=poly.end();i++){
        result<<scalePoint(*i,scaleX,scaleY);
    };
    return result;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{

    QPainter painter(this); // Создаём объект-живописец

    QColor Yelow(255, 255, 0); // Желтый цвет
    QColor White(255, 255, 255); // Белый цвет
    QColor Black(0, 0, 0); // Черный цвет

    // Основной радиус
    double rad;

    // Координаты центра окна
    QPointF center = QPointF(width()*0.5, height()*0.5);

    // Координаты левого верхнего и правого нижнего углов окна
    QPointF topLeft = QPoint(0, 0);
    QPointF bottomRight = QPoint(width(), height());

    // Задаем параметры фона
    QRectF backgrnd = QRectF(topLeft, bottomRight);

    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
    rad = (height() - 20) / 5;
    else rad = (width() - 20) / 5;

    // Если размеры окна маленькие, ничего не выводить
    if (width() < 30 || height() < 30)
    return;

    // Задаем
    QPolygonF ray;
        ray<<(QPointF(center.x(),center.y()-rad*2))
           <<(QPointF(center.x()+rad/8,center.y()))
           <<(QPointF(center.x()-rad/8,center.y()));

    // Рисуем лучи
    int dgr = 0;
    for(int i = 0; i < 120; i++){
        painter.setBrush(Yelow);
        painter.setPen(Yelow);

        //ray = moveQPolygonF(ray, 10, -10);
        ray = rotateQPolygonF(ray, 100);

        painter.drawPolygon(ray);

        dgr += 3;
    }

    // Задаём область прорисовки круга
    QRectF rectForEllipse = QRectF(center.x() - rad, center.y() - rad, rad*2, rad*2);

    // Рисуем желтый круг круг
    painter.setBrush(Yelow);
    painter.setPen(Yelow);
    painter.drawEllipse(rectForEllipse);

}

// Обработчик события прокрутки колеса мыши
void MainWindow::wheelEvent(QWheelEvent* wheelevent)
{
    angle -= wheelevent->delta() / 10;
    repaint(); // Обновляем окно
}


