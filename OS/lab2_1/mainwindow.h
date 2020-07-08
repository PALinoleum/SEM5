#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <windows.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showBase();
    bool showInfoByHandle(HMODULE handle_m);
    bool showInfoByName(QString name);

private slots:
    void on_descriptor_button_clicked();
    void on_module_button_clicked();
    void on_full_module_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
