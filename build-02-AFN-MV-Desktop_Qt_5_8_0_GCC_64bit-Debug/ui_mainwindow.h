/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
    QPushButton *gerarPosFixa;
    QPushButton *gerarAFN;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(900, 650);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        entrada = new QLineEdit(centralWidget);
        entrada->setObjectName(QStringLiteral("entrada"));
        entrada->setGeometry(QRect(20, 20, 750, 41));
        saida = new QLineEdit(centralWidget);
        saida->setObjectName(QStringLiteral("saida"));
        saida->setGeometry(QRect(20, 70, 750, 41));
        mensagem = new QLabel(centralWidget);
        mensagem->setObjectName(QStringLiteral("mensagem"));
        mensagem->setGeometry(QRect(90, 130, 681, 31));
        mensagem->setFrameShape(QFrame::Box);
        mensagem->setAlignment(Qt::AlignCenter);
        gerarPosFixa = new QPushButton(centralWidget);
        gerarPosFixa->setObjectName(QStringLiteral("gerarPosFixa"));
        gerarPosFixa->setGeometry(QRect(780, 20, 111, 41));
        gerarAFN = new QPushButton(centralWidget);
        gerarAFN->setObjectName(QStringLiteral("gerarAFN"));
        gerarAFN->setGeometry(QRect(780, 70, 111, 41));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 190, 861, 411));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        mensagem->setText(QString());
        gerarPosFixa->setText(QApplication::translate("MainWindow", "Gerar P\303\263s-Fixa", Q_NULLPTR));
        gerarAFN->setText(QApplication::translate("MainWindow", "Gerar AFN-MV", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
