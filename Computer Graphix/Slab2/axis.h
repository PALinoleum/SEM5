#ifndef AXIS_H
#define AXIS_H


#include <QPainter>

#include <cmath>

#include "coords.h"

#define PREFER_H 45

class Axis

{

public:

static void step(double &k, double &H, int &m, int &n);

};

class AbscissaAxis: public Axis

{
public:

void draw( ScreenCoords scr, WorldCoords w, QPainter &p);

};

class OrdinateAxis: public Axis

{

public:

void draw(ScreenCoords scr, WorldCoords w, QPainter &p);

};

#endif // AXIS_H
