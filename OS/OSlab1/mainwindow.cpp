#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

#include "windows.h"
#include "base.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    char* computerName;
    computerName = getComputerNameMY();

    QLabel lLabel;
    lLabel.setText ("ПОМОГИТЕ");
    // lLabel.setGeometry ( 200, 200, 300, 150 );
    lLabel.setAlignment (Qt::AlignHCenter | Qt::AlignVCenter );
    QFont lBlackFont(" Arial Black ", 12);
    lLabel.setFont(lBlackFont);
    lLabel.show();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


