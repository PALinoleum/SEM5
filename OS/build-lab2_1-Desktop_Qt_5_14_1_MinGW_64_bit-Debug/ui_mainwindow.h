/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *module_button;
    QLabel *label_3;
    QPushButton *descriptor_button;
    QLineEdit *full_module_line;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *module_line;
    QPushButton *full_module_button;
    QLineEdit *descriptor_line;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(533, 156);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        module_button = new QPushButton(centralwidget);
        module_button->setObjectName(QString::fromUtf8("module_button"));

        gridLayout->addWidget(module_button, 3, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        descriptor_button = new QPushButton(centralwidget);
        descriptor_button->setObjectName(QString::fromUtf8("descriptor_button"));

        gridLayout->addWidget(descriptor_button, 1, 1, 1, 1);

        full_module_line = new QLineEdit(centralwidget);
        full_module_line->setObjectName(QString::fromUtf8("full_module_line"));

        gridLayout->addWidget(full_module_line, 5, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        module_line = new QLineEdit(centralwidget);
        module_line->setObjectName(QString::fromUtf8("module_line"));

        gridLayout->addWidget(module_line, 3, 0, 1, 1);

        full_module_button = new QPushButton(centralwidget);
        full_module_button->setObjectName(QString::fromUtf8("full_module_button"));

        gridLayout->addWidget(full_module_button, 5, 1, 1, 1);

        descriptor_line = new QLineEdit(centralwidget);
        descriptor_line->setObjectName(QString::fromUtf8("descriptor_line"));

        gridLayout->addWidget(descriptor_line, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        module_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\276\320\265 \320\270\320\274\321\217 \320\274\320\276\320\264\321\203\320\273\321\217:", nullptr));
        descriptor_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\274\320\276\320\264\321\203\320\273\321\217:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200:", nullptr));
        full_module_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
