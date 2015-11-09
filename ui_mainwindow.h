/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *BtnStartListen;
    QTableWidget *TabelFileList;
    QPushButton *BtnAddFile;
    QLineEdit *LineClientIP;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(352, 427);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BtnStartListen = new QPushButton(centralWidget);
        BtnStartListen->setObjectName(QStringLiteral("BtnStartListen"));
        BtnStartListen->setGeometry(QRect(10, 10, 75, 23));
        TabelFileList = new QTableWidget(centralWidget);
        if (TabelFileList->columnCount() < 3)
            TabelFileList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TabelFileList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        TabelFileList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TabelFileList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        TabelFileList->setObjectName(QStringLiteral("TabelFileList"));
        TabelFileList->setGeometry(QRect(0, 70, 311, 181));
        BtnAddFile = new QPushButton(centralWidget);
        BtnAddFile->setObjectName(QStringLiteral("BtnAddFile"));
        BtnAddFile->setGeometry(QRect(0, 260, 75, 23));
        LineClientIP = new QLineEdit(centralWidget);
        LineClientIP->setObjectName(QStringLiteral("LineClientIP"));
        LineClientIP->setEnabled(false);
        LineClientIP->setGeometry(QRect(100, 10, 191, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 352, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        BtnStartListen->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\233\221\345\220\254", 0));
        QTableWidgetItem *___qtablewidgetitem = TabelFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = TabelFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\234\260\345\235\200", 0));
        BtnAddFile->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
