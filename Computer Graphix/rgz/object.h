#ifndef OBJECT_H
#define OBJECT_H

#include <QVector>
#include <QVector3D>
#include <QtOpenGL>
#include <QOpenGLWidget>

class CustomPolygon{
    QVector <QVector3D> positions;
    QVector <QVector3D> normals;
    QVector <QVector2D> texture;
    GLenum drawMode;
public:
    CustomPolygon(){};
    CustomPolygon(QVector <QVector3D> positions);
    CustomPolygon(QVector <QVector3D> positions, QVector <QVector3D> normals);
    CustomPolygon(QVector <QVector3D> positions, QVector <QVector3D> normals, QVector <QVector2D> texture);
    void pushPolygon(QVector3D position, QVector3D normal, QVector2D texture);
    void draw();
    void setDrawMode(GLenum mode);
    void addPosition(QVector3D newPosition);
    void addNormal(QVector3D newNormal);
    void addTexture(QVector2D newTexture);
    void translatePositions(QVector3D center);
    QVector <QVector3D> getPositions() {return positions;}
};

class Object{
private:
    QVector <CustomPolygon> p;
    QVector <uint> indicies;
    QVector3D center;
public:
    Object();
    ~Object();
    void init();
    bool read(QString filename);
    QVector <uint> getIndicies(){return indicies;}
    QVector3D getCenter();
    void translate();
    void draw();

};




#endif // OBJECT_H
