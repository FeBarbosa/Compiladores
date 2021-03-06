#include "mainwindow.h"
#include "ui_mainwindow.h"

ll::analisadorSintatico *a = new ll::analisadorSintatico;

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

//--------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------
void MainWindow::on_inserirGramatica_clicked()
{
    std::string strV, strT, strP, strS;

    std::vector<std::string> Vaux; // Conjunto de variáveis
    std::vector<std::string> Taux; // Conjunto de terminais
    std::vector<std::string> Paux; // Conjunto de produções

    std::string aux; // Auxilia na leitura das produções

    strV = ui->variaveis->text().toStdString();
    strT = ui->terminais->text().toStdString();
    strS = ui->inicial->text().toStdString();
    strP = ui->producoes->toPlainText().toStdString();

    Vaux = tokenizar(strV, " ,");
    Taux = tokenizar(strT, " ,");

    std::stringstream ss(strP);

    while(std::getline(ss, aux))
    {
        if(aux[aux.size()-1] == ',')
            aux.pop_back();

        Paux.push_back(aux);
    }

    a = new ll::analisadorSintatico(Vaux, Taux, Paux, strS);

//    for(auto it = a->tabelaSintatica.begin(); it != a->tabelaSintatica.end(); ++it)
//    {
//              for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
//              {
//                  std::cout << it->first << ": ";

//                  std::cout << it2->first << " ";
//                  for(unsigned int i = 0; i < it2->second.size(); i++)
//                    std::cout << it2->second[i] << " ";

//                    std::cout << std::endl << std::endl;
//              }
//    }


}

//--------------------------------------------------------------------------------------------
void MainWindow::on_analisar_clicked()
{
    std::string strCodigo;

    QString plaintextedit = ui->codigoTokenizado->toPlainText();

    QStringList lines = plaintextedit.split("\n");

    bool aceita;

    for(int i = 0; i < lines.size(); i++)
    {
        strCodigo = lines.at(i).toStdString();

        //strCodigo = atual.toStdString();

        std::vector<std::string> codigo;

        codigo = tokenizar(strCodigo, " ");

        std::list<std::string> aux;

        aux.insert(aux.begin(), codigo.begin(), codigo.end());

        aceita = a->analisarCodigo(aux);

        if(aceita)
            std::cout << "Aceito" << std::endl;
        else
            std::cout << "Não Aceita na linha " << i << std::endl;
    }
}
