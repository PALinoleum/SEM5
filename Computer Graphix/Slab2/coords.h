#ifndef COORDS_H
#define COORDS_H
#include <QPoint>

class Coords
{
public:
    double xbeg=0, xend=0, ybeg=0, yend=0;

    //Coords(double xbeg_, double xend_, double ybeg_, double yend_);
    QPointF topLeft();
    QPointF topRight();
    QPointF bottomLeft();
    QPointF bottomRight();
    double Xbeg();
    double Xend();
    double Ybeg();
    double Yend();
    virtual void setXbeg(double);
    virtual void setXend(double);
    virtual void setYbeg(double);
    virtual void setYend(double);
    virtual ~Coords(){}
};

class ScreenCoords: public Coords
{
public:
    double xbeg=0, xend=0, ybeg=0, yend=0;
    ScreenCoords(double xbeg_, double xend_, double ybeg_, double yend_)
    {
        xbeg = xbeg_;
        xend = xend_;
        ybeg = ybeg_;
        yend = yend_;
    }
    QPointF topLeft();
    QPointF topRight();
    QPointF bottomLeft();
    QPointF bottomRight();
};

//xbeg, ybeg matching to left bottom corner

class WorldCoords: public Coords
{
public:
    double xbeg=0, xend=0, ybeg=0, yend=0;
    WorldCoords(double xbeg_, double xend_, double ybeg_, double yend_)
    {
        xbeg = xbeg_;
        xend = xend_;
        ybeg = ybeg_;
        yend = yend_;
    }
    QPointF topLeft();
    QPointF topRight();
    QPointF bottomLeft();
    QPointF bottomRight();
};

class Converter
{
public:
    static QPointF screenToWorld(QPointF scrPoint, ScreenCoords scr, WorldCoords world);
    static QPointF worldToScreen(QPointF worldPoint, WorldCoords world, ScreenCoords scr);
    static QPointF worldToWorld(QPointF w1Point, WorldCoords world1, WorldCoords world2);
    static QPointF screenToScreen(QPointF s1Point, ScreenCoords screen1, ScreenCoords screen2);
};
#endif // COORDS_H
