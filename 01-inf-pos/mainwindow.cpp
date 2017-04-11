#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expreregular.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_Converter_clicked()
{
    ui->saida->setText(QString::fromStdString(""));

        ExpreRegular nt = ExpreRegular(ui->entrada->text().toStdString());

        int erro = nt.infParaPos();

        if(erro == -1)
            ui->Mensagens->setText(QString::fromStdString("ERRO: Fechamento de parênteses sem abertura!"));
        else if(erro == 0)
            ui->Mensagens->setText(QString::fromStdString("ERRO: Abertura de parênteses sem fechamento!"));
        else if(erro == 1)
            ui->Mensagens->setText(QString::fromStdString("ERRO: Operador sem operando!"));
        else
        {
            std::cout << nt.posFix << endl;
            if(!nt.verificarExpressaoPosfixa())
                ui->Mensagens->setText(QString::fromStdString("Expressão Inválida"));
            else
            {
                ui->saida->setText(QString::fromStdString(nt.posFix));
                ui->Mensagens->setText(QString::fromStdString("Expressão Válida!!!"));
            }
        }
}
