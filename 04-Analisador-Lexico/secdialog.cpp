#include "secdialog.h"
#include "ui_secdialog.h"
#include "analisadorlexico.h"

AnalisadorLexico *analisador = new AnalisadorLexico();

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),tableWidget(NULL),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
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
