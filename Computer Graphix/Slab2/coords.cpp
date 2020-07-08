#include "coords.h"
#include <QtCore>



double Coords::Xbeg()
{
    return xbeg;
}

double Coords::Xend()
{
    return xend;
}

double Coords::Ybeg()
{
    return ybeg;
}

double Coords::Yend()
{
    return yend;
}

void Coords::setXbeg(double xbeg_)
{
    xbeg = xbeg_;
}

void Coords::setXend(double xend_)
{
    xend = xend_;
}

void Coords::setYbeg(double ybeg_)
{
    ybeg = ybeg_;
}

void Coords::setYend(double yend_)
{
    yend = yend_;
}


QPointF Converter::screenToWorld(QPointF scrPoint, ScreenCoords scr, WorldCoords world)
{
    QPointF res;
    double coeff1 = (world.xend - world.xbeg)/(scr.xend - scr.xbeg);
    double coeff2 = (world.yend - world.ybeg)/(scr.yend - scr.ybeg);
    res.setX(world.xbeg + coeff1*(scrPoint.x() - scr.xbeg));
    res.setY(world.yend - coeff2*(scrPoint.y() - scr.ybeg));
    return res;
}

QPointF Converter::worldToScreen(QPointF worldPoint, WorldCoords world, ScreenCoords scr)
{
    QPointF res;
    double coeff1 = (scr.xend - scr.xbeg)/(world.xend - world.xbeg);
    double coeff2 = (scr.yend - scr.ybeg)/(world.yend - world.ybeg);

    res.setX(scr.xbeg + coeff1*(worldPoint.x() - world.xbeg));
    res.setY(scr.yend - coeff2*(worldPoint.y() - world.ybeg));
    return res;
}


