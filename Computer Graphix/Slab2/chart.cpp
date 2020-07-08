#include "chart.h"
#include "math.h"
#include <QApplication>
#include <QDesktopWidget>
#include "QPainter"
#include "axis.h"
#include "coords.h"
#include "mainwindow.h"
#include <QDebug>
using namespace std;

Chart::Chart(QWidget *parent) : QWidget(parent)
{
}

void Chart::redraw()
{

}

void Chart::paintEvent(QPaintEvent *p_event)
{
    this->resize(srcwidgetsize.width() * this->parentWidget()->width()/srcwindowsize.width(),
                 srcwidgetsize.height() * this->parentWidget()->height()/srcwindowsize.height());

    this->Chart::coords_converter.X1 = this->x();
    this->Chart::coords_converter.Y1 = this->y();
    this->Chart::coords_converter.X2 = this->rect().bottomRight().x()-30;
    this->Chart::coords_converter.Y2 = this->rect().bottomRight().y()-30;

    this->Chart::coords_converter.x1 = 0;
    this->Chart::coords_converter.y1 = 0;
    this->Chart::coords_converter.x2 = 10;
    this->Chart::coords_converter.y2 = 10;

    AbscissaAxis absaxis;
    OrdinateAxis ordaxis;

    globMAX=0;
    float globMIN=0;
    for (float i=this->a;i<this->b;i+=0.1) {
        if((curves[0]->F(i))>globMAX) globMAX = (curves[0]->F(i));
        if((curves[0]->F(i))<globMIN) globMIN = (curves[0]->F(i));
    }
    qDebug()<<globMAX<<" "<<globMIN;

    WorldCoords wc(a+offsetx,b+offsetx,globMIN,globMAX);
    ScreenCoords sc(coords_converter.X1,coords_converter.X2,coords_converter.Y1,coords_converter.Y2);

    vector<QPoint> points;
    for (int i=0;i<curves.length();i++) {
        for (float j=this->a; j<b; j+=0.0005){
            QPoint monitorcoord = Converter::worldToScreen(QPointF(j,curves[i]->F(j)),wc,sc).toPoint();

            points.push_back(monitorcoord);
        }
    }


    QPainter painter(this);
    this->painter.begin(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    QRect a = this->rect();

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawPoints(&points[0],points.size());

    absaxis.draw(sc, wc, painter);
    ordaxis.draw(sc, wc, painter);

    this->painter.end();
    redraw();
    update();
}

void Chart::resizeEvent(QResizeEvent *r_event)
{
    srcwidgetsize.setCoords(0,0,this->size().width(),this->size().height());
    srcwindowsize.setCoords(0,0,this->parentWidget()->size().width(),this->parentWidget()->size().height());

}
