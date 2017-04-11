#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expreregular.h"
#include <iostream>
#include <nfa.h>
#include <dfa.h>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), tableWidget(NULL), tableWidget_2(NULL),
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
        if(!nt.verificarExpressaoPosfixa())
            ui->mensagem->setText(QString::fromStdString("Expressão Inválida"));
        else
        {
            ui->saida->setText(QString::fromStdString(nt.posFix));
            ui->mensagem->setText(QString::fromStdString("Expressão Válida!!!"));
        }
    }
}



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
       //std::cout << (*it2) << std::endl;
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
                str = "";

                auto range = (*it)->transicoes.equal_range((*it2));
                for_each(
                    range.first,
                    range.second,
                    [&str](trans::value_type& x){str += "q" + to_string(x.second->id) + " ";}
                );

                if(!str.empty())
                {
                    str = "{" + str;
                    str += "}";
                }

                ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::fromStdString(str)));

                j++;
            }

            i++;
   }

}

void MainWindow::on_gerarAFD_clicked()
{
    NFA automato = NFA(ui->saida->text().toStdString());
    automato.criarNFA();

    DFA automato2 = DFA(automato.nfa, automato.Alfabeto);

    automato2.criarDFA();

    //inicializando a tabela
     int i =0;
    tableWidget_3 = new QTableWidget(this);
    int colCount = 2;
    int rCount = automato2.fechos.size();
    ui->tableWidget_3->setColumnCount(colCount);
    ui->tableWidget_3->setRowCount(rCount);
    ui->tableWidget_3->horizontalHeader()->setResizeContentsPrecision(QHeaderView::ResizeToContents);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);
    string str;
    //stringstream auxParaConverter;
    //Preenchimento da tabela
//    for(auto it = automato.nfa.begin(); it !=automato.nfa.end(); it++) // Percorre estados
//        {
//            if(it == automato.nfa.begin())
//                str = "Fecho-& ->q";
//            else
//                str = "Fecho-& q";

//            str += to_string((*it)->id);

//            if((*it)->estadoFinal)
//                str += "*";

//            ui->tableWidget_3->setItem(i,0, new QTableWidgetItem(QString::fromStdString(str)));

//            //Preenchimento das células - usar função epsilonFecho de DFA
//            for(auto it2 = ; it2 !=automato.nfa.end(); it2++) // Percorre alfabeto para cada estado
//            {
//                str = "{";

//                auto range = (*it)->transicoes.equal_range((EPSILON));
//                for_each(
//                    range.first,
//                    range.second,
//                    [&str](trans::value_type& x){str += "q" + to_string(x.second->id) + " ";}
//                );
//               str += to_string(DFA.calculaFecho((*it2)->id));

//                str += "}";


//                ui->tableWidget_3->setItem(i,1, new QTableWidgetItem(QString::fromStdString(str)));

//            }

//            i++;
//   }


    for(auto it = automato2.fechos.begin(); it != automato2.fechos.end(); ++it)
    {

//        if(it == automato2.nfa.begin()+1)
//            str = "Fecho-& ->q";
//        else
            str = "Fecho-& q";

        str += to_string((*((*it).first)).id);

//        if((*it)->estadoFinal)
//            str += "*";

        ui->tableWidget_3->setItem(i,0, new QTableWidgetItem(QString::fromStdString(str)));

        str = "";

        for(auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
        {
            str += "q" + to_string((*it2)->id) + " ";
        }

//        auto range = (*it2)
//        for_each(
//            range.first,
//            range.second,
//            [&str](trans::value_type& x){str += "q" + to_string(x.second->id) + " ";}
//        );


        if(!str.empty())
        {
            str = "{" + str;
            str += "}";
        }

        cout << str << endl;

        ui->tableWidget_3->setItem(i,1, new QTableWidgetItem(QString::fromStdString(str)));

        i++;
    }

}
