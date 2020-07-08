#ifndef MATRIX_H
#define MATRIX_H

#include <QtWidgets>
#include <QtMath>
class Vectorx3{
    private:
        qreal vector[3];
    public:
        Vectorx3();
        Vectorx3(qreal e1,qreal e2, qreal e3);
        Vectorx3(QVector<qreal> vect);
        Vectorx3(QPointF point);
        QVector<qreal> qVector();
        QPointF qPointF();
        void fromQPointF(QPointF point);
        void fromQVector(QVector<qreal> vectx3);
        void fromQReal(qreal e1,qreal e2,qreal e3);
        qreal operator [](int index){
            return vector[index];
        };
        qreal x();
        qreal y();
        qreal k();
};

class Matrix3x3{
    private:
        qreal matrix[3][3];
    public:
        Matrix3x3();
        Matrix3x3(qreal e1,qreal e2,qreal e3,
                  qreal e4,qreal e5,qreal e6,
                  qreal e7,qreal e8,qreal e9);

        QVector<qreal> operator *(QVector<qreal> m2){
            return QVector<qreal>({
                this->matrix[0][0]*m2[0]+this->matrix[0][1]*m2[1]+this->matrix[0][2]*m2[2],
                this->matrix[1][0]*m2[0]+this->matrix[1][1]*m2[1]+this->matrix[1][2]*m2[2],
                this->matrix[2][0]*m2[0]+this->matrix[2][1]*m2[1]+this->matrix[2][2]*m2[2]
            });
        };

        Vectorx3 operator *(Vectorx3 m2){
            return Vectorx3(
                this->matrix[0][0]*m2[0]+this->matrix[0][1]*m2[1]+this->matrix[0][2]*m2[2],
                this->matrix[1][0]*m2[0]+this->matrix[1][1]*m2[1]+this->matrix[1][2]*m2[2],
                this->matrix[2][0]*m2[0]+this->matrix[2][1]*m2[1]+this->matrix[2][2]*m2[2]
            );
        };

        qreal* operator [](int index){
            return matrix[index];
        };
};


Matrix3x3 mirrorMatrix3x3(bool mirrorX,bool mirrorY);
Matrix3x3 rotateMatrix3x3(qreal alpha);
Matrix3x3 scaleMatrix3x3(qreal scaleX,qreal scaleY);
Matrix3x3 moveMatrix3x3(qreal deltaX,qreal deltaY);

#endif // MATRIX_H
