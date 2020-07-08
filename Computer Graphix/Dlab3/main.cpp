#include <QtWidgets>

#include "draw.h"

int main(int argc, char *argv[])

{

    QApplication a(argc, argv);

    DrawArea* drawArea = new DrawArea;

    drawArea->show();

    return a.exec();

}
