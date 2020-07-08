/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLineEdit *ID_line;
    QLabel *label_5;
    QLineEdit *p_handle_line;
    QLabel *label_6;
    QLineEdit *d_handle_line;
    QLabel *label_7;
    QLineEdit *op_handle_line;
    QLabel *label_8;
    QLineEdit *close_d_handle_line;
    QLabel *label_9;
    QLineEdit *close_op_handle_line;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(603, 288);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        ID_line = new QLineEdit(centralwidget);
        ID_line->setObjectName(QString::fromUtf8("ID_line"));
        ID_line->setReadOnly(true);

        verticalLayout->addWidget(ID_line);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        p_handle_line = new QLineEdit(centralwidget);
        p_handle_line->setObjectName(QString::fromUtf8("p_handle_line"));
        p_handle_line->setReadOnly(true);

        verticalLayout->addWidget(p_handle_line);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        d_handle_line = new QLineEdit(centralwidget);
        d_handle_line->setObjectName(QString::fromUtf8("d_handle_line"));
        d_handle_line->setReadOnly(true);

        verticalLayout->addWidget(d_handle_line);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        op_handle_line = new QLineEdit(centralwidget);
        op_handle_line->setObjectName(QString::fromUtf8("op_handle_line"));
        op_handle_line->setReadOnly(true);

        verticalLayout->addWidget(op_handle_line);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        close_d_handle_line = new QLineEdit(centralwidget);
        close_d_handle_line->setObjectName(QString::fromUtf8("close_d_handle_line"));
        close_d_handle_line->setReadOnly(true);

        verticalLayout->addWidget(close_d_handle_line);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        close_op_handle_line = new QLineEdit(centralwidget);
        close_op_handle_line->setObjectName(QString::fromUtf8("close_op_handle_line"));
        close_op_handle_line->setReadOnly(true);

        verticalLayout->addWidget(close_op_handle_line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\230\320\264\320\265\320\275\321\202\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200 \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\201\320\265\320\262\320\264\320\276\320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200 \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\204\321\203\320\275\320\272\321\206\320\270\320\265\320\271 DuplicateHandle", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\204\321\203\320\275\320\272\321\206\320\270\320\265\320\271 OpenProcess", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\320\262\320\260\320\265\320\274 \320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\204\321\203\320\275\320\272\321\206\320\270\320\265\320\271 DuplicateHandle", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\320\262\320\260\320\265\320\274 \320\264\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200, \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\271 \321\204\321\203\320\275\320\272\321\206\320\270\320\265\320\271 OpenProcess: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
