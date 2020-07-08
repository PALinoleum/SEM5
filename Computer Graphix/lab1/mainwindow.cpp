#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QColor Red(255, 0, 0); // Красный цвет
    QColor White(255, 255, 255); // Белый цвет
    QColor Black(0, 0, 0); // Черный цвет

    // Координаты центра окна
    QPointF center = QPointF(width()*0.5, height()*0.5);

    // Координаты левого верхнего и правого нижнего углов окна
    QPointF topLeft = QPoint(0, 0);
    QPointF bottomRight = QPoint(width(), height());

    // Задаем параметры фона
    QRectF backgrnd = QRectF(topLeft, bottomRight);

    // Рисуем красный фон
    painter.setBrush(Red);
    painter.setPen(Red);
    painter.drawRect(backgrnd);

    // Радиус окружности
    double radius;

    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
    radius = (height() - 20) / 2.7;
    else radius = (width() - 20) / 2.7;

    // Если размеры окна маленькие, ничего не выводить
    if (width() < 30 || height() < 30)
    return;

    // Задаём область прорисовки круга
    QRectF rectForEllipse = QRectF(center.x() - radius, center.y() - radius, radius*2, radius*2);

    // Рисуем белый круг
    painter.setBrush(White);
    painter.setPen(White);
    painter.drawEllipse(rectForEllipse);

    // Вспомогательные радиусы
    double Rsmall = radius / 10;
    double Rbig = radius / 1.7;

    // Задаем параметры креста
    QRectF CrossVert = QRectF(-Rsmall, -Rbig, Rsmall*2, Rbig*2);
    QRectF CrossHori = QRectF(-Rbig, -Rsmall, Rbig*2, Rsmall*2);

    //Задаем параметры лепестков
    QRectF Top = QRectF(center.x() - Rsmall, center.y() - Rbig, Rbig + Rsmall, 2 * Rsmall);
    QRectF Right = QRectF(center.x() + Rbig - 2 * Rsmall, center.y() - Rsmall, 2 * Rsmall, Rbig + Rsmall);
    QRectF Bottom = QRectF(center.x() - Rbig, center.y() + Rbig - 2 * Rsmall,  Rbig + Rsmall, 2 * Rsmall);
    QRectF Left = QRectF(center.x() - Rbig, center.y() - Rbig, 2 * Rsmall, Rbig + Rsmall);

    QRectF Vert = QRectF(-Rsmall, -(Rbig + Rsmall)*0.5, Rsmall*2, Rbig + Rsmall);
    QRectF Hori = QRectF(-(Rbig + Rsmall)*0.5, -Rsmall,  Rbig + Rsmall, Rsmall*2);

    // Рисуем крест и лепестки
    painter.setBrush(Black);
    painter.setPen(Black);

    painter.save();
    painter.translate(center);
    painter.rotate(angle);
    painter.drawRect(CrossVert);
    painter.drawRect(CrossHori);
    painter.restore();

    QRectF DrawRect;
    QRectF DrawRectR;

    for (int i = 0; i < 4; i++){
        if(i%2 == 0)
            DrawRectR = Hori;
        else
            DrawRectR = Vert;
        if(i == 0)
            DrawRect = Top;
        else
            if(i == 1)
                DrawRect = Right;
            else
                if(i == 2)
                    DrawRect = Bottom;
                else
                    DrawRect = Left;
        painter.save();
        painter.translate(rotatePoint(center, DrawRect.center(), angle));
        painter.rotate(angle);
        painter.drawRect(DrawRectR);
        painter.restore();
    }

}

// Обработчик события прокрутки колеса мыши
void MainWindow::wheelEvent(QWheelEvent* wheelevent)
{
    angle -= wheelevent->delta() / 10;
    repaint(); // Обновляем окно
}


