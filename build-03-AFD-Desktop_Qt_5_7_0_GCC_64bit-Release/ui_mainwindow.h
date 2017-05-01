/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *entrada;
    QLineEdit *saida;
    QLabel *mensagem;
    QTableWidget *tableWidget;
    QPushButton *gerarPosFixa;
    QPushButton *gerarAFN;
    QPushButton *gerarAFD;
    QTableWidget *tableWidget_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *tableWidget_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1322, 707);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        entrada = new QLineEdit(centralWidget);
        entrada->setObjectName(QStringLiteral("entrada"));
        entrada->setGeometry(QRect(20, 10, 750, 41));
        saida = new QLineEdit(centralWidget);
        saida->setObjectName(QStringLiteral("saida"));
        saida->setGeometry(QRect(20, 60, 750, 41));
        mensagem = new QLabel(centralWidget);
        mensagem->setObjectName(QStringLiteral("mensagem"));
        mensagem->setGeometry(QRect(50, 120, 681, 31));
        mensagem->setFrameShape(QFrame::Box);
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(50, 210, 541, 231));
        gerarPosFixa = new QPushButton(centralWidget);
        gerarPosFixa->setObjectName(QStringLiteral("gerarPosFixa"));
        gerarPosFixa->setGeometry(QRect(780, 10, 111, 41));
        gerarAFN = new QPushButton(centralWidget);
        gerarAFN->setObjectName(QStringLiteral("gerarAFN"));
        gerarAFN->setGeometry(QRect(780, 60, 111, 41));
        gerarAFD = new QPushButton(centralWidget);
        gerarAFD->setObjectName(QStringLiteral("gerarAFD"));
        gerarAFD->setGeometry(QRect(780, 120, 111, 41));
        tableWidget_2 = new QTableWidget(centralWidget);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(50, 480, 611, 191));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(60, 170, 311, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 450, 291, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(660, 170, 67, 17));
        tableWidget_3 = new QTableWidget(centralWidget);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(630, 210, 591, 231));
        tableWidget_3->setLineWidth(1);
        tableWidget_3->setColumnCount(0);
        tableWidget_3->horizontalHeader()->setDefaultSectionSize(200);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1322, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        mensagem->setText(QString());
        gerarPosFixa->setText(QApplication::translate("MainWindow", "Gerar P\303\263s-Fixa", 0));
        gerarAFN->setText(QApplication::translate("MainWindow", "Gerar AFN-MV", 0));
        gerarAFD->setText(QApplication::translate("MainWindow", "Gerar AFD", 0));
        label->setText(QApplication::translate("MainWindow", "Aut\303\264mato finito com movimento vazio:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Aut\303\264mato finito determin\303\255stico (AFD):", 0));
        label_3->setText(QApplication::translate("MainWindow", "Fecho-\316\265:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
