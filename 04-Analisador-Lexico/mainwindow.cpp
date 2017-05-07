#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analisadorlexico.h"
#include <QMessageBox>
#include <iostream>
#include <sstream>

AnalisadorLexico *analisador = new AnalisadorLexico();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),tableWidget(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Token_clicked()
{
//    SecDialog secdialog;
//    secdialog.setModal(true);
//    secdialog.exec();
//    secdialog = new SecDialog(this);
//    secdialog->show();

}


void MainWindow::on_Analisar_clicked()
{
    string str;
    str = ui->plainTextEdit->toPlainText().toStdString();
    QString str2 = QString::fromStdString(str);
    ui->textEdit->setText(str2);
}

void MainWindow::on_inserirToken_clicked()
{
    analisador->calcularPadrao(ui->entradaExpressao->text().toStdString(), ui->entradaToken->text().toStdString());

    //inicializando a tabela
    tableWidget = new QTableWidget(this);
    int colCount = 2;
    int rCount = analisador->listaDeTokens.size();
    ui->tableWidget->setColumnCount(colCount);
    ui->tableWidget->setRowCount(rCount);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);


    string strPadrao;
    string strToken;
    int i = 0;
    //stringstream auxParaConverter;

    //Cabeçalho da tabela
    for(auto it = analisador->listaDeTokens.begin(); it != analisador->listaDeTokens.end(); it++)
    {
       strPadrao = (*it)->padrao;
       strToken = (*it)->token;
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(strPadrao)));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(strToken)));

        i++;
    }
}
