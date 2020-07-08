#include "object.h"

CustomPolygon::CustomPolygon(QVector <QVector3D> positions) : positions(positions){};
CustomPolygon::CustomPolygon(QVector <QVector3D> positions, QVector <QVector3D> normals)
    : positions(positions), normals(normals) {};
CustomPolygon::CustomPolygon(QVector <QVector3D> positions, QVector <QVector3D> normals, QVector <QVector2D> texture)
    : positions(positions), normals(normals), texture(texture) {};

void CustomPolygon::draw(){
    bool textureAvailable = false;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (texture.size() != 0) textureAvailable = true;
    glBegin(GL_POLYGON);
        if (normals.size() != 0)
            glNormal3f(normals[0].x(), normals[0].y(), normals[0].z());
        for (int i = 0; i < positions.size(); i++){
            if (textureAvailable)
                glTexCoord2f(texture[i].x(), texture[i].y());
            glVertex3f(positions[i].x(), positions[i].y(), positions[i].z());

        }
    glEnd();
}

void CustomPolygon::setDrawMode(GLenum mode){
    drawMode = mode;
}

void CustomPolygon::pushPolygon(QVector3D position, QVector3D normal, QVector2D texture){
    this->positions.push_back(position);
    this->normals.push_back(normal);
    this->texture.push_back(texture);
}

void CustomPolygon::addPosition(QVector3D newPosition){
    positions.push_back(newPosition);
}

void CustomPolygon::addNormal(QVector3D newNormal){
    normals.push_back(newNormal);
}

void CustomPolygon::addTexture(QVector2D newTexture){
    texture.push_back(newTexture);
}

void CustomPolygon::translatePositions(QVector3D center){
    for (int i = 0; i < positions.size(); i++){
        positions[i].setX(positions[i].x() - center.x());
        positions[i].setY(positions[i].y() - center.y());
        positions[i].setZ(positions[i].z() - center.z());
    }
}

Object::Object(){}

bool Object::read(QString filename){
    p.clear();
    indicies.clear();
    QFile f(filename);
    if (!f.exists()) {
        qDebug() << "Такого файла нет!";
        return false;
    }
    if (!f.open(QIODevice::ReadOnly)){
        qDebug() << "Не могу открыть файл!";
        return false;
    }
    QTextStream istream(&f);
    QVector<QVector3D> _v;
    QVector<QVector2D> _t;
    QVector<QVector3D> _n;
    QString tmp;
    QStringList list, indiciesList;
    while (!istream.atEnd()){
        tmp = istream.readLine();
        list = tmp.split(" ");
        if (list[0] == "v"){
            _v.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if (list[0] == "vt"){
            _t.append(QVector2D(list[1].toFloat(), list[2].toFloat()));
            continue;
        }
        if (list[0] == "vn"){
            _n.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if (list[0] == "f"){
            CustomPolygon newPolygon;
            if (list[1].contains("/")){
                for (int i = 1; i < list.size(); i++){
                    indiciesList = list[i].split("/");
                    newPolygon.addPosition(_v[indiciesList[0].toLong() - 1]);
                    if (indiciesList[2].size() != 0){
                        newPolygon.addNormal(_n[indiciesList[2].toLong()-1]);
                    }
                    if (indiciesList[1].size() != 0){
                        newPolygon.addTexture(_t[indiciesList[1].toLong()-1]);
                    }
                }
            } else {
                for (int i = 1; i < list.size(); i++){
                    if (list[i] != "")
                        newPolygon.addPosition(_v[list[i].toLong() - 1]);
                }
            }
            p.push_back(newPolygon);
        }
    }
    f.close();
    translate();
    return true;
}

void Object::translate(){
    center = getCenter();  
    for (int i = 0; i < p.size(); i++){
        p[i].translatePositions(center);
    }
}

void Object::draw(){
    for (int i = 0; i < p.size(); i++)
        p[i].draw();
}

QVector3D Object::getCenter(){
    QVector3D result(0, 0, 0);
    int totalSize = 0;
    for (int i = 0; i < p.size(); i++){
        QVector <QVector3D> currentPositions = p[i].getPositions();
        totalSize += currentPositions.size();
        for (int j = 0; j < currentPositions.size(); j++){
            result.setX(result.x() + currentPositions[j].x());
            result.setY(result.y() + currentPositions[j].y());
            result.setZ(result.z() + currentPositions[j].z());
        }
    }
    result.setX(result.x() / totalSize);
    result.setY(result.y() / totalSize);
    result.setZ(result.z() / totalSize);
    return result;
}

Object::~Object() {}
