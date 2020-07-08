#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <viewwidget.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openFile();
    void light1();
    void light2();
    void light3();
private:
    Ui::MainWindow *ui;
    QAction * openFileAction, * setupLight1Action, * setupLight2Action, * setupLight3Action;
    QString filename;
    bool l1Enabled, l2Enabled, l3Enabled;
};
#endif // MAINWINDOW_H
