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

    QColor White(255, 255, 255); // Белый цвет
    QColor Black(0, 0, 0); // Черный цвет

    // Координаты центра окна
    QPointF center = QPointF(width()*0.5, height()*0.5);

    // Задаем основной радиус
    double radius;

    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
    radius = (height() - 20) / 2;
    else radius = (width() - 20) / 2;

    // Если размеры окна маленькие, ничего не выводить
    if (width() < 30 || height() < 30)
    return;

    // Задаем массив радиусов
    double rad[4] = {radius, radius - radius*0.25, radius - radius*0.5, radius - radius*0.75};

    // Задаём область прорисовки окружности
    QRectF rectForEllipse;

    // Рисуем направляющие окружности
    painter.setBrush(White);
    painter.setPen(Black);

    for(int i = 0; i < 4; i++){
          rectForEllipse = QRectF(center.x() - rad[i], center.y() - rad[i], rad[i] * 2, rad[i] * 2);
          painter.drawEllipse(rectForEllipse);
    }

    // Количество квадратов
    int sqr = 5;

    // Задаем параметры для квадратов
    QRectF Square = QRectF(center.x() - rad[3]*0.375, center.y() - rad[3]*1.85, rad[3]*0.75, rad[3]*0.75);

    QRectF SquareR =  QRectF(-rad[3]*0.375, -rad[3]*0.375, rad[3]*0.75, rad[3]*0.75);

    // Рисуем квадраты
    int dgrS = 0;
    for(int i = 0; i < sqr; i++){
        QColor Green(0, dgrS, 0);
        painter.setBrush(Green);
        painter.setPen(Green);
        painter.save();
        painter.translate(rotatePoint(center, Square.center(), dgrS));
        painter.rotate(dgrS);
        painter.drawRect(SquareR);
        painter.restore();

        dgrS += 45;
    }

    // Количество треугольников
    int trg = 15;

    // Задаем параметры треугольников
    QRectF RectForT = QRectF(center.x() - rad[3]*0.375, center.y() - rad[3]*2.85, rad[3]*0.75, rad[3]*0.75);

    QRectF RectForTR =  QRectF(-rad[3]*0.375, -rad[3]*0.375, rad[3]*0.75, rad[3]*0.75);

    QPolygonF Triangle;
    Triangle << QPointF(RectForTR.left(), RectForTR.bottom())
             << QPointF(RectForTR.center().x(), RectForTR.top())
             << QPointF(RectForTR.right(), RectForTR.bottom());

    // Рисуем треугольники
    int dgrT = angle;
    for(int i = 0; i < trg; i++){
        QColor Color = QColor::fromHsv((abs(dgrT + angle))%360, 255 , 255);
        Color.toHsv();
        painter.setBrush(Color);
        painter.setPen(Color);
        painter.save();
        painter.translate(rotatePoint(center, RectForT.center(), dgrT));
        painter.rotate(dgrT);
        painter.drawPolygon(Triangle);
        painter.restore();

        dgrT += 30;
    }

    // Количество окружностей
    int rnd = 25;

    // Задаем параметры для окружностей
    QRectF Round = QRectF(center.x() - rad[3]*0.375, center.y() - rad[3]*3.85, rad[3]*0.75, rad[3]*0.75);

    QRectF RoundR =  QRectF(-rad[3]*0.375, -rad[3]*0.375, rad[3]*0.75, rad[3]*0.75);

    // Рисуем окружности
    int dgrR = -15;
    for(int i = 0; i < rnd; i++){
        QColor Color = QColor::fromHsv(dgrR, 255 , 255);
        Color.toHsv();
        painter.setBrush(Color);
        painter.setPen(Color);
        painter.save();
        painter.translate(rotatePoint(center, Round.center(), dgrR));
        painter.rotate(dgrR);
        painter.drawEllipse(RoundR);
        painter.restore();

        dgrR += 15;
    }

}

// Обработчик события прокрутки колеса мыши
void MainWindow::wheelEvent(QWheelEvent* wheelevent)
{
    angle -= wheelevent->delta() / 10;
    repaint(); // Обновляем окно
}
