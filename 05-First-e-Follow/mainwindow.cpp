#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_ok_clicked()
{
    std::string strV, strT, strP, strS;

    strV = ui->entradaV->text().toStdString();
    strT = ui->entradaT->text().toStdString();
    strS = ui->entradaS->text().toStdString();
    strP = ui->entradaP->toPlainText().toStdString();
    char auxiliar[] = strP.c_str();
}
