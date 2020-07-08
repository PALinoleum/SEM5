#include "viewwidget.h"
#include <GL/glu.h>


ViewWidget::ViewWidget(QWidget *parent)
    : QGLWidget(parent){
    currentObject = Object();
    isInitialized = false;
    globalScale = 0.1f;
    texture = new QOpenGLTexture(QImage(QString("C:/GitHub/lab/cg/models/t.png")).mirrored());
}

void ViewWidget::initializeGL(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    resetModelView();
    resetProjection();
    setupLightning();
    loadTexture("D:/GitHub/labs/cg/models/t.png");
}

void ViewWidget::loadTexture(QString path){
    QImage image = QImage(path);
    image = QGLWidget::convertToGLFormat(image);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, (GLuint)tex, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
}

void ViewWidget::setupLightning(){
    glEnable(GL_LIGHTING);

    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat MaterialAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat MaterialDiffuse[] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat MaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat MaterialShininess[] = {50.0f};
    GLfloat AmbientLightPosition[] = {100.0f, 100.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPosition);
    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, LightAmbient);

    GLfloat light1Diffuse[] = {0.0f, 1.0f, 0.0f};
    GLfloat light1Position[] = {100.0f, 100.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);

    GLfloat light2Diffuse[] = {0.7f, 0.1f, 0.1f};
    GLfloat light2Position[] = {-200.0f, -200.0f, 100.0f, 0.0f};
    GLfloat light2SpotDirection[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2SpotDirection);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void ViewWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    resetProjection();
}

void ViewWidget::changeLights(bool enable, int lightNum){
    switch (lightNum) {
        case 0:
            if (enable)
                glEnable(GL_LIGHT0);
            else glDisable(GL_LIGHT0);
        break;
        case 1:
            if (enable)
                glEnable(GL_LIGHT1);
            else glDisable(GL_LIGHT1);
        break;
        case 2:
            if (enable)
                glEnable(GL_LIGHT2);
            else glDisable(GL_LIGHT2);
        break;
    }
    repaint();
}

void ViewWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (isInitialized){
        currentObject.draw();
    }
    glPushMatrix();
        glRotatef(xAngle * 2, 1, 0, 0);
        glRotatef(yAngle * 2, 0, 1, 0);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, tex);
    currentObject.draw();
}

void ViewWidget::resetProjection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (float)width() / height(), 0.1, 20);
}

void ViewWidget::resetModelView(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -zoffset);
    glMultMatrixf(rotationMatrix.inverted().data());
    glScalef(globalScale, globalScale, globalScale);
}

void ViewWidget::changeRotationMatrix(float dx, float dy){
    rotationMatrix.rotate(-dx, 0, 1, 0);
    rotationMatrix.rotate(-dy, 1, 0, 0);
}

void ViewWidget::mouseMoveEvent(QMouseEvent * event){
    QPoint newPos = event->pos();
    float dx = newPos.x() - pos.x();
    float dy = newPos.y() - pos.y();
    changeRotationMatrix(dx / 2, dy / 2);
    pos = newPos;
    resetModelView();
    repaint();
}

void ViewWidget::wheelEvent(QWheelEvent * event){
    zoffset -= event->delta() / 1000.0f;
    resetProjection();
    resetModelView();
    repaint();
}

void ViewWidget::mousePressEvent(QMouseEvent * event){
    pos = event->pos();
    repaint();
}

void ViewWidget::keyPressEvent(QKeyEvent * event){
    if (event->key() == Qt::Key_Escape){
        close();
    }
}

void ViewWidget::loadObject(QString filename){
    isInitialized = false;
    if (currentObject.read(filename))
        isInitialized = true;
}
