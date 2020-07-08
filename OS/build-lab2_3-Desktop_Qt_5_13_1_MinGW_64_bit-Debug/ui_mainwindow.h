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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *NT_tab;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *proc_NT_tab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *pr_table_NT;
    QWidget *dr_NT_tab;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *drivers_table_NT;
    QWidget *tab_9x;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *proc_table;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        NT_tab = new QWidget();
        NT_tab->setObjectName(QString::fromUtf8("NT_tab"));
        verticalLayout_2 = new QVBoxLayout(NT_tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget_2 = new QTabWidget(NT_tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        proc_NT_tab = new QWidget();
        proc_NT_tab->setObjectName(QString::fromUtf8("proc_NT_tab"));
        verticalLayout_4 = new QVBoxLayout(proc_NT_tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pr_table_NT = new QTableWidget(proc_NT_tab);
        if (pr_table_NT->columnCount() < 2)
            pr_table_NT->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        pr_table_NT->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        pr_table_NT->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        pr_table_NT->setObjectName(QString::fromUtf8("pr_table_NT"));

        verticalLayout_4->addWidget(pr_table_NT);

        tabWidget_2->addTab(proc_NT_tab, QString());
        dr_NT_tab = new QWidget();
        dr_NT_tab->setObjectName(QString::fromUtf8("dr_NT_tab"));
        verticalLayout_5 = new QVBoxLayout(dr_NT_tab);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        drivers_table_NT = new QTableWidget(dr_NT_tab);
        if (drivers_table_NT->columnCount() < 2)
            drivers_table_NT->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        drivers_table_NT->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        drivers_table_NT->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        drivers_table_NT->setObjectName(QString::fromUtf8("drivers_table_NT"));

        verticalLayout_5->addWidget(drivers_table_NT);

        tabWidget_2->addTab(dr_NT_tab, QString());

        verticalLayout_2->addWidget(tabWidget_2);

        tabWidget->addTab(NT_tab, QString());
        tab_9x = new QWidget();
        tab_9x->setObjectName(QString::fromUtf8("tab_9x"));
        verticalLayout_3 = new QVBoxLayout(tab_9x);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        proc_table = new QTableWidget(tab_9x);
        if (proc_table->columnCount() < 5)
            proc_table->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        proc_table->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        proc_table->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        proc_table->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        proc_table->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        proc_table->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        proc_table->setObjectName(QString::fromUtf8("proc_table"));

        verticalLayout_3->addWidget(proc_table);

        tabWidget->addTab(tab_9x, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = pr_table_NT->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = pr_table_NT->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(proc_NT_tab), QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201\321\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = drivers_table_NT->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\267\320\276\320\262\321\213\320\271 \320\260\320\264\321\200\320\265\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = drivers_table_NT->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(dr_NT_tab), QCoreApplication::translate("MainWindow", "\320\224\321\200\320\260\320\271\320\262\320\265\321\200\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(NT_tab), QCoreApplication::translate("MainWindow", "Windows NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = proc_table->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "ID \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = proc_table->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = proc_table->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\321\202\320\276\320\272\320\276\320\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = proc_table->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "ID \321\200\320\276\320\264\320\270\321\202\320\265\320\273\321\214\321\201\320\272\320\276\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = proc_table->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\276\321\200\320\270\321\202\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9x), QCoreApplication::translate("MainWindow", "Windows 9x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
