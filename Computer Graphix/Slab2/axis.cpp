#include "axis.h"

#include <QtCore>

void Axis::step(double &k, double &H, int &m, int &n)

{

    double p = H/k;

    double n1 = log10(p);

    double n2 = log10(p/2);

    double n5 = log10(p/5);

    m = 1; n = int(floor(n1));

    double min_ = p - pow(10, floor(n1));

    if (p - 2*pow(10, floor(n2)) < min_)

    {

        min_ = p - 2*pow(10, floor(n2));

        m = 2; n = int(floor(n2));

    }

    if (p - 5*pow(10, floor(n5)) < min_)

    {

        min_ = p - 5*pow(10, floor(n5));

        m = 5; n = int(floor(n5));

    }

    if (pow(10, ceil(n1)) - p < min_)

    {

        min_ = pow(10, ceil(n1)) - p;

        m = 1; n = int(ceil(n1));

    }

    if (2*pow(10, ceil(n2)) - p < min_)

    {

        min_ = 2*pow(10, ceil(n2)) - p;

        m = 2; n = int(ceil(n2));

    }

    if (5*pow(10, ceil(n5)) - p < min_)

    {

        min_ = 5*pow(10, ceil(n5)) - p;

        m = 5; n = int(ceil(n5));

    }

    double h = m*pow(10, n);

    H = h*k;

    k = h;

}

void AbscissaAxis::draw(ScreenCoords s, WorldCoords w, QPainter &p)

{

    double k = (s.xend - s.xbeg)/(w.xend - w.xbeg);

    double H = PREFER_H;

    int m = 0, n = 0;

    step(k, H, m, n);

    QPointF a(s.xbeg, s.yend);

    QPointF b(s.xend, s.yend);

    p.setPen(QPen(Qt::black, 100));
    p.setBrush(Qt::black);
    p.drawLine(a, b);

    double xWorld0 = (floor(w.xbeg/k) + 1)*k;

    while (xWorld0 <= w.xend)
    {
        QPointF serif = Converter::worldToScreen(QPointF(xWorld0, w.ybeg), w, s);
        serif.setY(serif.y() - 10);
        QPointF serifEnd = serif;
        serifEnd.setY(serif.y() + 10);

        p.drawLine(serif, serifEnd);

        QString s = QString::number(xWorld0);
        p.drawText(serifEnd.x() - 5, serifEnd.y() + 15, s);
        xWorld0 += k;

    }

}

void OrdinateAxis::draw(ScreenCoords s, WorldCoords w, QPainter &p)
{
    double k = (s.yend - s.ybeg)/(w.yend - w.ybeg);
    double H = PREFER_H;
    int m = 0, n = 0;
    step(k, H, m, n);

    QPointF a(s.xbeg, s.yend);
    QPointF b(s.xbeg, s.ybeg);
    p.setPen(QPen(Qt::green, 100));
    p.setBrush(QBrush(Qt::green));

    p.drawLine(a, b);

    double yWorld0 = (floor(w.ybeg/k) + 1)*k;
    while (yWorld0 <= w.yend)
    {
        QPointF serif = Converter::worldToScreen(QPointF(w.xbeg, yWorld0), w, s);
        serif.setX(serif.x() + 10);
        QPointF serifEnd = serif;

        serifEnd.setX(serif.x() - 10);

        p.drawLine(serif, serifEnd);

        QString s = QString::number(yWorld0);

        p.drawText(serifEnd.x() - 20, serifEnd.y() + 5, s);

        yWorld0 += k;

    }

}
