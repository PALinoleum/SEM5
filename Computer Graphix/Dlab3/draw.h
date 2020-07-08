#ifndef DRAW_H
#define DRAW_H

#include <QtWidgets>
#include "matrix.h"

#pragma once

static qreal mainRadius;

QPointF movePoint(QPointF point,qreal deltaX,qreal deltaY);
QPointF rotatePoint(QPointF point,qreal angle);
QPointF scalePoint(QPointF point,qreal scaleX,qreal scaleY);
QPointF mirrorPoint(QPointF point,bool x,bool y);

QPolygonF rotateQPolygonF(QPolygonF poly,qreal angle);
QPolygonF moveQPolygonF(QPolygonF poly,qreal deltaX,qreal deltaY);
QPolygonF mirrorQPolygonF(QPolygonF poly,bool x,bool y);
QPolygonF scaleQPolygonF(QPolygonF poly,qreal scaleX,qreal scaleY);

QRectF getCircleArea(QPointF center,qreal radius);
bool pointInPolygon(QPolygonF poly,QPointF point);
qreal to_rad(qreal angle);

class Flash{
    private:
        int _state;
        QPointF _point;
        int red;
        int green;
        int blue;
        int scale;
    public:
        Flash(QPointF point){
            _point = point;
            _state = 100;
            red = (QRandomGenerator::global()->generate())%255;
            blue = (QRandomGenerator::global()->generate())%255;
            green = (QRandomGenerator::global()->generate())%255;
        };
        QPointF point(){return _point;};
        int state(){return _state;};
        void operator() (QPainter* painter,bool mirror){
            if(_state != 0){
                QColor color(red,green,blue,255-_state);
                scale = _state*mainRadius*0.001;
                QBrush flashBrush = QBrush(color);
                QPen flashPen = QPen(color);
                flashPen.setWidth(3);
                QPointF drawPoint(0,0);

                if(mirror){
                    drawPoint = movePoint(drawPoint,-_point.x(),_point.y());
                    drawPoint = mirrorPoint(drawPoint,0,1);
                    drawPoint = movePoint(drawPoint,2*_point.x(),1);
                }else{
                    drawPoint = movePoint(drawPoint,_point.x(),_point.y());
                };

                QBrush tempBrush = painter->brush();
                QPen tempPen = painter->pen();
                painter->setBrush(flashBrush);
                painter->setPen(flashPen);
                painter->drawEllipse(getCircleArea(drawPoint,scale));
                painter->setBrush(tempBrush);
                painter->setPen(tempPen);

                _state--;
            };
        };
};

class DrawArea:public QWidget{
Q_OBJECT
public:
    private:
        unsigned state = 0;
        QList<Flash> flashList;
        QList<Flash> mirrorFlashList;
    public slots:
        void animate();
    public:
    DrawArea();
    void paintEvent(QPaintEvent* event);
};




#endif // DRAW_H
