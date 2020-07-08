#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QImage>
#include <QOpenGLTexture>
#include <object.h>
#include <QMatrix4x4>
#include <GL/glu.h>

class ViewWidget : public QGLWidget{
    Q_OBJECT
private:
    float zoffset = 3, xAngle = 90, yAngle = 0, globalScale;
    QPoint pos;
    QString filename;
    Object currentObject;
    QMatrix4x4 rotationMatrix, textureMatrix;
    QString texPath;
    QOpenGLTexture * texture;
    unsigned tex;
public:
    ViewWidget(QWidget *parent = nullptr);
    ~ViewWidget(){};
    bool isInitialized;
    void loadObject(QString filename);

    void changeLights(bool enable, int lightNum);

    void loadTexture(QString path);
    void setupLightning();
    void resetProjection();
    void resetModelView();
    void changeRotationMatrix(float dx, float dy);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent * event);
};
#endif // VIEWWIDGET_H

