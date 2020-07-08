#include "matrix.h"

Vectorx3::Vectorx3(){
    this->vector[0] = 0;
    this->vector[1] = 0;
    this->vector[2] = 0;
};
Vectorx3::Vectorx3(qreal e1,qreal e2, qreal e3){
    this->vector[0] = e1;
    this->vector[1] = e2;
    this->vector[2] = e3;
};
Vectorx3::Vectorx3(QVector<qreal> vect){
    this->vector[0] = vect[0];
    this->vector[1] = vect[1];
    this->vector[2] = vect[2];
};
QVector<qreal> Vectorx3::qVector(){
    return QVector<qreal> {
        this->vector[0],
        this->vector[1],
        this->vector[2]
    };
};

Vectorx3::Vectorx3(QPointF point){
    this->vector[0]=point.x();
    this->vector[1]=point.y();
    this->vector[2]=1;
};


void Vectorx3::fromQVector(QVector<qreal> vectx3){
    this->vector[0] = vectx3[0];
    this->vector[1] = vectx3[1];
    this->vector[2] = vectx3[2];
};
void Vectorx3::fromQReal(qreal e1,qreal e2,qreal e3){
    this->vector[0] = e1;
    this->vector[1] = e2;
    this->vector[2] = e3;
};

qreal Vectorx3::x(){
    return this->vector[0];
};
qreal Vectorx3::y(){
    return this->vector[1];
};
qreal Vectorx3::k(){
    return this->vector[2];
};

QPointF Vectorx3::qPointF(){
    return QPointF(x(),y());
};
void Vectorx3::fromQPointF(QPointF point){
    Vectorx3(point.x(),point.y(),1);
};

Matrix3x3 mirrorMatrix3x3(bool mirrorX=false,bool mirrorY=false){
    qreal xMul = 1,yMul = 1;
    if(mirrorX) xMul = -1;
    if(mirrorY) yMul = -1;
    return Matrix3x3(
        xMul,0,0,
        0,yMul,0,
        0,0,1
    );
};
Matrix3x3 rotateMatrix3x3(qreal alpha=0){
    return Matrix3x3(
        qCos(alpha),-qSin(alpha),0,
        qSin(alpha),qCos(alpha),0,
        0,0,1
    );
};
Matrix3x3 scaleMatrix3x3(qreal scaleX=1,qreal scaleY=1){
    return Matrix3x3(
        scaleX,0,0,
        0,scaleY,0,
        0,0,1
    );
};
Matrix3x3 moveMatrix3x3(qreal deltaX=0,qreal deltaY=0){
    return Matrix3x3(
        1,0,deltaX,
        0,1,deltaY,
        0,0,1
    );
};

Matrix3x3::Matrix3x3(qreal e1,qreal e2,qreal e3,
            qreal e4,qreal e5,qreal e6,
            qreal e7,qreal e8,qreal e9)
{
    matrix[0][0] = e1;
    matrix[0][1] = e2;
    matrix[0][2] = e3;
    matrix[1][0] = e4;
    matrix[1][1] = e5;
    matrix[1][2] = e6;
    matrix[2][0] = e7;
    matrix[2][1] = e8;
    matrix[2][2] = e9;
};

