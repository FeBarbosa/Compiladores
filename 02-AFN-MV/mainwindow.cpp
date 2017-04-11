#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expreregular.h"
#include <iostream>
#include <nfa.h>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), tableWidget(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Gerar a pós-fixa e mostrar na tela -------------------------------------------------------------
void MainWindow::on_gerarPosFixa_clicked()
{
    ui->saida->setText(QString::fromStdString(""));

    ExpreRegular nt = ExpreRegular(ui->entrada->text().toStdString());

    int erro = nt.infParaPos();

    if(erro == -1)
        ui->mensagem->setText(QString::fromStdString("ERRO: Fechamento de parênteses sem abertura!"));
    else if(erro == 0)
        ui->mensagem->setText(QString::fromStdString("ERRO: Abertura de parênteses sem fechamento!"));
    else if(erro == 1)
        ui->mensagem->setText(QString::fromStdString("ERRO: Operador sem operando!"));
    else
    {
        std::cout << nt.posFix << endl;
        if(!nt.verificarExpressaoPosfixa())
            ui->mensagem->setText(QString::fromStdString("Expressão Inválida"));
        else
        {
            ui->saida->setText(QString::fromStdString(nt.posFix));
            ui->mensagem->setText(QString::fromStdString("Expressão Válida!!!"));
        }
    }
}



typedef std::unordered_multimap<uchar, NFAEstado*> trans;

// Gera o AFN-& a partir da expressão pós-fixa-----------------------------------------------------
void MainWindow::on_gerarAFN_clicked()
{
    NFA automato = NFA(ui->saida->text().toStdString());
    automato.criarNFA();

    //inicializando a tabela
     int i =1, j=1;
    tableWidget = new QTableWidget(this);
    int colCount = automato.Alfabeto.size()+1;
    int rCount = automato.nfa.size()+1;
    ui->tableWidget->setColumnCount(colCount);
    ui->tableWidget->setRowCount(rCount);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    // Preenchendo a primeira linha
    QStringList l;

    l <<" ";
    while(colCount>0){
        if(colCount==2){
             l= l <<"&";
             colCount=0;
        }
        else {
            l = l << "Simbolo";
            colCount=colCount-1;
        }
    }
    //ui->tableWidget->setHorizontalHeaderLabels(l);

   string str;
   //stringstream auxParaConverter;

   //Cabeçalho da tabela
   for(auto it2 = automato.Alfabeto.begin(); it2 != automato.Alfabeto.end(); it2++)
   {
       str = "";
       str.push_back((*it2));
       std::cout << (*it2) << std::endl;
       ui->tableWidget->setItem(0,j, new QTableWidgetItem(QString::fromStdString(str)));
       j++;
   }

   i = 1;

    //Preenchimento da tabela
    for(auto it = automato.nfa.begin(); it !=automato.nfa.end(); it++) // Percorre estados
        {
            if(it == automato.nfa.begin())
                str = "->q";
            else
                str = "q";

            str += to_string((*it)->id);

            if((*it)->estadoFinal)
                str += "*";

            ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(str)));

            j = 1;


            //Preenchimento das células
            for(auto it2 = automato.Alfabeto.begin(); it2 != automato.Alfabeto.end(); it2++) // Percorre alfabeto para cada estado
            {
                str = "{";

                auto range = (*it)->transicoes.equal_range((*it2));
                for_each(
                    range.first,
                    range.second,
                    [&str](trans::value_type& x){str += "q" + to_string(x.second->id) + " ";}
                );

                str += "}";

                ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::fromStdString(str)));

                j++;
            }

            i++;
   }

}
