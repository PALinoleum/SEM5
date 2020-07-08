#include "draw.h"

void DrawArea::paintEvent(QPaintEvent* event)
{
    //проверка полей
    if (this->width() < 40 || this->height() < 40) return;

    bool newFlash = (QRandomGenerator::global()->generate() % 100) < 3;

    QPainter *painter = new QPainter(this);

    //установка параметров от таймера
    qreal angle = to_rad(state%360);

    //антиалиасинг
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    //установка радиусов
    if(this->height()>this->width()){
        mainRadius = this->width()/5;
    }
    else{
        mainRadius = this->height()/5;
    };
    qreal outRadius = mainRadius+mainRadius/5;
    qreal helpPointRadius = outRadius/5;


    QPointF center(0,0); // center(this->width()/2,this->height()/2)
    QPointF mirrorCenter(0,0);
    center = movePoint(center,this->width()/4,this->height()/2);
    mirrorCenter = movePoint(mirrorCenter,3*this->width()/4,this->height()/2);

    QPolygonF bird;
    QPolygonF mirrorBird;
    bird<<(QPointF(0,0))<<(QPointF(3,1))<<(QPointF(4,0))<<(QPointF(4,2))
        <<(QPointF(2,2))<<(QPointF(2,5))<<(QPointF(1,4))<<(QPointF(0,6))
        <<(QPointF(-1,2))<<(QPointF(-2,2))<<(QPointF(-5,-1))<<(QPointF(-2,1));
    bird = scaleQPolygonF(bird,helpPointRadius/2,helpPointRadius/2);
    bird = mirrorQPolygonF(bird,0,1);
    bird = moveQPolygonF(bird,1,-outRadius);
    bird = rotateQPolygonF(bird,angle);
    mirrorBird = bird;
    mirrorBird = mirrorQPolygonF(mirrorBird,1,1);
    mirrorBird = moveQPolygonF(mirrorBird,3*this->width()/4,this->height()/2);
    bird = moveQPolygonF(bird,this->width()/4,this->height()/2);

    //Задание на защиту
    QPolygonF birdTask;
    QPolygonF mirrorBirdTask;
    birdTask<<(QPointF(0,0))<<(QPointF(3,1))<<(QPointF(4,0))<<(QPointF(4,2))
        <<(QPointF(2,2))<<(QPointF(2,5))<<(QPointF(1,4))<<(QPointF(0,6))
        <<(QPointF(-1,2))<<(QPointF(-2,2))<<(QPointF(-5,-1))<<(QPointF(-2,1));
    birdTask = scaleQPolygonF(birdTask,helpPointRadius/2,helpPointRadius/2);
    birdTask = mirrorQPolygonF(birdTask,1,0);
    birdTask = moveQPolygonF(birdTask,1,outRadius);
    birdTask = rotateQPolygonF(birdTask,angle);
    mirrorBirdTask = birdTask;
    mirrorBirdTask = mirrorQPolygonF(mirrorBirdTask,1,1);
    mirrorBirdTask = moveQPolygonF(mirrorBirdTask,3*this->width()/4,this->height()/2);
    birdTask = moveQPolygonF(birdTask,this->width()/4,this->height()/2);



    QPolygonF land1;
    QPolygonF mirrorLand1;
    land1<<QPointF(2,-3)<<QPointF(2,-5)<<QPointF(-1,-6)
         <<QPointF(-5,-6)<<QPointF(-6,-3)<<QPointF(-3,-1)
         <<QPointF(-3,-1)<<QPointF(-1,-4);
    land1 = scaleQPolygonF(land1,helpPointRadius/2,helpPointRadius/2);
    land1 = mirrorQPolygonF(land1,1,0);
    mirrorLand1 = land1;
    mirrorLand1 = mirrorQPolygonF(mirrorLand1,1,1);
    mirrorLand1 = moveQPolygonF(mirrorLand1,3*this->width()/4,this->height()/2);
    land1 = moveQPolygonF(land1,this->width()/4,this->height()/2);

    QPolygonF land2;
    QPolygonF mirrorLand2;
    land2<<QPointF(0,7)<<QPointF(0,-3)<<QPointF(3,-4);
    land2 = scaleQPolygonF(land2,helpPointRadius/3,helpPointRadius/3);
    mirrorLand2 = land2;
    mirrorLand2 = mirrorQPolygonF(mirrorLand2,1,1);
    mirrorLand2 = moveQPolygonF(mirrorLand2,3*this->width()/4,this->height()/2);
    land2 = moveQPolygonF(land2,this->width()/4,this->height()/2);

    QPolygonF land3;
    QPolygonF mirrorLand3;
    land3<<QPointF(5,-6)<<QPointF(6,-9)<<QPointF(9,-8)
         <<QPointF(7,-5)<<QPointF(6,-3)<<QPointF(6,-2)
         <<QPointF(5,-1);
    land3 = scaleQPolygonF(land3,helpPointRadius/3,helpPointRadius/3);
    land3 = mirrorQPolygonF(land3,1,0);
    mirrorLand3 = land3;
    mirrorLand3 = mirrorQPolygonF(mirrorLand3,1,1);
    mirrorLand3 = moveQPolygonF(mirrorLand3,3*this->width()/4,this->height()/2);
    land3 = moveQPolygonF(land3,this->width()/4,this->height()/2);

    QPolygonF land4;
    QPolygonF mirrorLand4;
    land4<<QPointF(5,-1)<<QPointF(3,1)<<QPointF(3,3)<<QPointF(2,5)
         <<QPointF(7,5)<<QPointF(8,4)<<QPointF(9,4)<<QPointF(10,1)
         <<QPointF(5,-1);
    land4 = scaleQPolygonF(land4,helpPointRadius/3,helpPointRadius/3);
    land4 = mirrorQPolygonF(land4,1,0);
    mirrorLand4 = land4;
    mirrorLand4 = mirrorQPolygonF(mirrorLand4,1,1);
    mirrorLand4 = moveQPolygonF(mirrorLand4,3*this->width()/4,this->height()/2);
    land4 = moveQPolygonF(land4,this->width()/4,this->height()/2);

    QPolygonF flashPoints;
    QPolygonF mirrorFlashPoints;
    flashPoints<<QPointF(1,-4)<<QPointF(-5,-3)<<QPointF(-3,-4)<<QPointF(-3,-2)
               <<QPointF(7,0)<<QPointF(4,6)<<QPointF(9,3)<<QPointF(2,2);
    flashPoints = scaleQPolygonF(flashPoints,helpPointRadius/3,helpPointRadius/3);
    flashPoints = mirrorQPolygonF(flashPoints,1,0);
    mirrorFlashPoints = flashPoints;
    mirrorFlashPoints = mirrorQPolygonF(mirrorFlashPoints,1,1);
    mirrorFlashPoints = moveQPolygonF(mirrorFlashPoints,3*this->width()/4,this->height()/2);
    flashPoints = moveQPolygonF(flashPoints,this->width()/4,this->height()/2);

    if(newFlash){
        int flashPos = (QRandomGenerator::global()->generate() % flashPoints.size());
        flashList.append(Flash(QPointF(flashPoints[flashPos])));
        mirrorFlashList.append(Flash(QPointF(mirrorFlashPoints[flashPos])));
    }


    //кисть для обводки
    QPen strokePen = QPen(QColor(0,0,0));
    strokePen.setWidth(3);
    //кисть воды
    QBrush waterBrush = QBrush(QColor(3,119,252),Qt::Dense1Pattern);
    QBrush whiteBrush = QBrush(QColor(255,255,255));
    QBrush greenBrush = QBrush(QColor(64, 179, 77),Qt::Dense2Pattern);
    QBrush desertBrush = QBrush(QColor(235, 198, 52),Qt::Dense1Pattern);

    painter->setPen(strokePen);
    painter->setBrush(waterBrush);
    painter->drawEllipse(getCircleArea(center,mainRadius));
    painter->drawEllipse(getCircleArea(mirrorCenter,mainRadius));

    painter->setBrush(whiteBrush);
    painter->drawPolygon(bird);
    painter->drawPolygon(birdTask);
    painter->drawPolygon(mirrorBird);
    painter->drawPolygon(mirrorBirdTask);

    painter->setBrush(greenBrush);
    painter->drawPolygon(land4);
    painter->drawPolygon(land3);
    painter->drawPolygon(land1);
    painter->drawPolygon(mirrorLand4);
    painter->drawPolygon(mirrorLand3);
    painter->drawPolygon(mirrorLand1);

    painter->setBrush(desertBrush);
    painter->drawPolygon(mirrorLand2);
    painter->drawPolygon(land2);

    for(auto i = flashList.begin();i!=flashList.end();i++){
        (*i)(painter,0);
        if((*i).state() == 0) flashList.erase(i);
    };
    for(auto i = mirrorFlashList.begin();i!=mirrorFlashList.end();i++){
        (*i)(painter,0);
        if((*i).state() == 0) mirrorFlashList.erase(i);
    }
    painter->end();
};

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

QRectF getCircleArea(QPointF center,qreal radius){
    QRectF area = QRectF(center.x() - radius, center.y() - radius, radius*2, radius*2);
    return area;
};

void DrawArea::animate(){
    state++;
    repaint();
};

DrawArea::DrawArea(){
        QTimer* timer = new QTimer;
        QWidget::connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
        timer->start(1);
        this->setWindowTitle("Лабораторная работа №3");
};

qreal to_rad(qreal angle){
    return angle*M_PI/180;
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
