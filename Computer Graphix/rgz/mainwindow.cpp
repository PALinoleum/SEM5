#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle(" ");
    this->resize(1200, 700);
    openFileAction = new QAction("Открыть", this);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));


    ui->menu->addAction(openFileAction);
    ui->view->loadObject(QString("D:/git/labs/cg/rgz/models/Звезда.obj"));

    l1Enabled = true; l2Enabled = true; l3Enabled = true;

    setupLight1Action = new QAction("Включить источник света 1", this);
    setupLight2Action = new QAction("Включить источник света 2", this);
    setupLight3Action = new QAction("Включить источник света 3", this);
    ui->lightSettings->addAction(setupLight1Action);
    ui->lightSettings->addAction(setupLight2Action);
    ui->lightSettings->addAction(setupLight3Action);

    connect(setupLight1Action, SIGNAL(triggered()), this, SLOT(light1()));
    connect(setupLight2Action, SIGNAL(triggered()), this, SLOT(light2()));
    connect(setupLight3Action, SIGNAL(triggered()), this, SLOT(light3()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::openFile(){

    filename = QFileDialog::getOpenFileName(this, "", "*.obj");
    ui->view->loadObject(filename);
}

void MainWindow::light1(){
    if (l1Enabled){
        setupLight1Action->setText("Отключить источник света 1");
        l1Enabled = false;
    } else {
        setupLight1Action->setText("Включить источник света 1");
        l1Enabled = true;        
    }
    ui->view->changeLights(!l1Enabled, 0);
}

void MainWindow::light2(){
    if (l2Enabled){
        setupLight2Action->setText("Отключить источник света 2");
        l2Enabled = false;
    } else {
        setupLight2Action->setText("Включить источник света 2");
        l2Enabled = true;
    }
    ui->view->changeLights(!l2Enabled, 1);
}

void MainWindow::light3(){
    if (l3Enabled){
        setupLight3Action->setText("Отключить источник света 3");
        l3Enabled = false;
    } else {
        setupLight3Action->setText("Включить источник света 3");
        l3Enabled = true;
    }
    ui->view->changeLights(!l3Enabled, 2);
}
