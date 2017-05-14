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

//---------------------------------------------------------------------------------------
std::vector<std::string> MainWindow::tokenizar(std::string str, char *delim)
{
    char *aux = strdup(str.c_str());
    char *pch;
    std::vector<std::string> strTokenizada;

    pch = strtok(aux, delim);

    while(pch != NULL)
    {
        strTokenizada.push_back(pch);
        pch = strtok(NULL, delim);
    }

    return strTokenizada;
}
//---------------------------------------------------------------------------------------

void MainWindow::on_ok_clicked()
{
    std::string strV, strT, strP, strS;

    std::vector<std::string> Vaux; // Conjunto de variáveis
    std::vector<std::string> Taux; // Conjunto de terminais
    std::vector<std::string> Paux; // Conjunto de produções

    std::string aux; // Auxilia na leitura das produções

    strV = ui->entradaV->text().toStdString();
    strT = ui->entradaT->text().toStdString();
    strS = ui->entradaS->text().toStdString();
    strP = ui->entradaP->toPlainText().toStdString();

    Vaux = tokenizar(strV, " ,");
    Taux = tokenizar(strV, " ,");

    std::stringstream ss(strP);

    while(std::getline(ss, aux))
    {
        if(aux[aux.size()-1] == ',')
            aux.pop_back();

        Paux.push_back(aux);
    }

    ll::gramaticaLL1 a(Vaux, Taux, Paux, strS);


}
