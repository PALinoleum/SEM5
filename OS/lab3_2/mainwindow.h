#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    HANDLE h;   //десриптор ждущего таймера
    QTimer tmr;
    bool flag;

private slots:
    void on_create_timer_button_clicked();
    void on_exit_button_clicked();
    void on_start_button_clicked();
    void updateCounter();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
