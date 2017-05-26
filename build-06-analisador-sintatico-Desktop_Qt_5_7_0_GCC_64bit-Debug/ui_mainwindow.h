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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *variaveis;
    QLineEdit *terminais;
    QLineEdit *inicial;
    QPlainTextEdit *producoes;
    QPushButton *inserirGramatica;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPlainTextEdit *codigoTokenizado;
    QPushButton *analisar;
    QLineEdit *variavelEscolhida;
    QPushButton *first;
    QPushButton *follow;
    QPushButton *tabela;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(995, 504);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        variaveis = new QLineEdit(centralWidget);
        variaveis->setObjectName(QStringLiteral("variaveis"));
        variaveis->setGeometry(QRect(90, 40, 261, 41));
        terminais = new QLineEdit(centralWidget);
        terminais->setObjectName(QStringLiteral("terminais"));
        terminais->setGeometry(QRect(90, 90, 261, 41));
        inicial = new QLineEdit(centralWidget);
        inicial->setObjectName(QStringLiteral("inicial"));
        inicial->setGeometry(QRect(90, 310, 261, 41));
        producoes = new QPlainTextEdit(centralWidget);
        producoes->setObjectName(QStringLiteral("producoes"));
        producoes->setGeometry(QRect(90, 140, 261, 161));
        inserirGramatica = new QPushButton(centralWidget);
        inserirGramatica->setObjectName(QStringLiteral("inserirGramatica"));
        inserirGramatica->setGeometry(QRect(180, 380, 80, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(48, 50, 31, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(48, 110, 31, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(48, 150, 31, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 310, 21, 41));
        codigoTokenizado = new QPlainTextEdit(centralWidget);
        codigoTokenizado->setObjectName(QStringLiteral("codigoTokenizado"));
        codigoTokenizado->setGeometry(QRect(560, 40, 341, 301));
        analisar = new QPushButton(centralWidget);
        analisar->setObjectName(QStringLiteral("analisar"));
        analisar->setGeometry(QRect(690, 370, 121, 41));
        variavelEscolhida = new QLineEdit(centralWidget);
        variavelEscolhida->setObjectName(QStringLiteral("variavelEscolhida"));
        variavelEscolhida->setGeometry(QRect(410, 40, 101, 41));
        first = new QPushButton(centralWidget);
        first->setObjectName(QStringLiteral("first"));
        first->setGeometry(QRect(410, 100, 101, 41));
        follow = new QPushButton(centralWidget);
        follow->setObjectName(QStringLiteral("follow"));
        follow->setGeometry(QRect(410, 170, 101, 41));
        tabela = new QPushButton(centralWidget);
        tabela->setObjectName(QStringLiteral("tabela"));
        tabela->setGeometry(QRect(410, 230, 101, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 995, 19));
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
        inserirGramatica->setText(QApplication::translate("MainWindow", "OK", 0));
        label->setText(QApplication::translate("MainWindow", "V =", 0));
        label_2->setText(QApplication::translate("MainWindow", "T =", 0));
        label_3->setText(QApplication::translate("MainWindow", "P =", 0));
        label_4->setText(QApplication::translate("MainWindow", "S =", 0));
        analisar->setText(QApplication::translate("MainWindow", "ANALISAR", 0));
        first->setText(QApplication::translate("MainWindow", "First", 0));
        follow->setText(QApplication::translate("MainWindow", "Follow", 0));
        tabela->setText(QApplication::translate("MainWindow", "Tabela", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
