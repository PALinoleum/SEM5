#include "chart.h"
#include "coords.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDesktopWidget>
#include <QDebug>

class x3CurveData : public Chart::CurveData
{
public:
    double F(double x) override
    {
        return 3*x+2;
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->rangeEdit->text();

    ui->mychar->curves.push_back(new x3CurveData());
    chartlink = ui->mychar;
    //ui->mychar->;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showCOORDS()));
    timer->start(60); //time specified in ms

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCOORDS()
{
    QPoint globalCursorPos = QCursor::pos();
    int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);

    QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
    QPoint localCursorPos = globalCursorPos - mouseScreenGeometry.topLeft();

    this->parentWidget()->mapToGlobal(this->pos());


    QPointF mouse_coord = QPoint(localCursorPos.x()-ui->mychar->mapToGlobal(ui->mychar->pos()).x(),((ui->mychar->mapToGlobal(ui->mychar->pos()).y())-localCursorPos.y())+(ui->mychar->coords_converter.Y2-ui->mychar->coords_converter.Y1));
            WorldCoords wc(ui->mychar->coords_converter.x1,ui->mychar->coords_converter.x2,ui->mychar->coords_converter.y1,ui->mychar->coords_converter.y2);
            ScreenCoords sc(0,(ui->mychar->coords_converter.X2-ui->mychar->coords_converter.X1),0,(ui->mychar->coords_converter.Y2-ui->mychar->coords_converter.Y1));
            QPointF monitorcoord = Converter::screenToWorld(mouse_coord, sc,wc);
            monitorcoord.setY(ui->mychar->coords_converter.y2+ui->mychar->offsety-monitorcoord.y());
            monitorcoord.setX(monitorcoord.x()+ui->mychar->offsetx);
}

void MainWindow::resizeEvent(QResizeEvent *r_event)
{

}

void MainWindow::on_horizontalSlider1_valueChanged(int value)
{
   // ui->mychar->offsetx = (value-50)*ui->lineEdit->text().toFloat();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
   // ui->mychar->offsety = (value-50)*ui->lineEdit->text().toFloat();
}

void MainWindow::on_rangeEdit_textEdited(const QString &arg1)
{
    ui->mychar->a = arg1.split(",")[0].toFloat();
    ui->mychar->b = arg1.split(",")[1].toFloat();
}
