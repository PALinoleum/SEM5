#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();

public slots:
    void showCOORDS();

private slots:
    void on_horizontalSlider1_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_rangeEdit_textEdited(const QString &arg1);

private:
    QTimer *timer;

    Chart* chartlink;
    void resizeEvent(QResizeEvent* r_event);

};

#endif // MAINWINDOW_H
