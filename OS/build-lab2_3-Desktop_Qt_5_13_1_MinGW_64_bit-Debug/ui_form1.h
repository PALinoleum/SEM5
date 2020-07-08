/********************************************************************************
** Form generated from reading UI file 'form1.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM1_H
#define UI_FORM1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form1
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *th_table;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *mod_table;

    void setupUi(QDialog *Form1)
    {
        if (Form1->objectName().isEmpty())
            Form1->setObjectName(QString::fromUtf8("Form1"));
        Form1->resize(1136, 599);
        verticalLayout = new QVBoxLayout(Form1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(Form1);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        th_table = new QTableWidget(tab);
        if (th_table->columnCount() < 3)
            th_table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        th_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        th_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        th_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        th_table->setObjectName(QString::fromUtf8("th_table"));

        verticalLayout_2->addWidget(th_table);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        mod_table = new QTableWidget(tab_2);
        if (mod_table->columnCount() < 6)
            mod_table->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        mod_table->setHorizontalHeaderItem(5, __qtablewidgetitem8);
        mod_table->setObjectName(QString::fromUtf8("mod_table"));

        verticalLayout_3->addWidget(mod_table);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(Form1);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(QDialog *Form1)
    {
        Form1->setWindowTitle(QCoreApplication::translate("Form1", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = th_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Form1", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = th_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Form1", "ID \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = th_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Form1", "\320\237\321\200\320\270\320\276\321\200\320\270\321\202\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Form1", "\320\237\320\276\321\202\320\276\320\272\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = mod_table->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Form1", "ID \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = mod_table->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Form1", "\320\230\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = mod_table->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Form1", "\320\237\321\203\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = mod_table->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Form1", "\320\221\320\260\320\267\320\276\320\262\321\213\320\271 \320\260\320\264\321\200\320\265\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = mod_table->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Form1", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = mod_table->horizontalHeaderItem(5);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Form1", "\320\224\320\265\321\201\320\272\321\200\320\270\320\277\321\202\320\276\321\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Form1", "\320\234\320\276\320\264\321\203\320\273\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM1_H
