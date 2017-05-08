#include "analisadorlexico.h"

//--------------------------------------------------------------------------
AnalisadorLexico::AnalisadorLexico(){}

void AnalisadorLexico::calcularPadrao(string padraoNovo, string tokenNovo)
{
    ExpreRegular *padraoAux = new ExpreRegular(padraoNovo);
    int erro = padraoAux->infParaPos();
    std::string mensagem = "";

    if(erro != 2)
    {
        if(erro == -1)
            mensagem = "ERRO: Fechamento de parênteses sem abertura!";
        else if(erro == 0)
            mensagem = "ERRO: Abertura de parênteses sem fechamento!";
        else if(erro == 1)
            mensagem = "ERRO: Operador sem operando!";
    }
    else
    {
        if(!padraoAux->verificarExpressaoPosfixa())
            mensagem = "Expressão Inválida";
    }

    if(mensagem != "")
    {
        QMessageBox msgBox;
        msgBox.setInformativeText(QString::fromStdString(mensagem));
        msgBox.exec();
    }
    else
    {

        NFA NFAaux = NFA(padraoAux->posFix);

        NFAaux.criarNFA();

        DFA *DFAaux = new DFA(NFAaux.nfa, NFAaux.Alfabeto, tokenNovo, padraoNovo);

        DFAaux->criarDFA();
        this->listaDeTokens.push_back(DFAaux);
    }
}

//--------------------------------------------------------------------------

std::string AnalisadorLexico::analise(std::string codigo, int linha)
{
    string codigoTokenizado = "";
    string codigoAux = codigo;
    string tokenAtual = "";
    string trechoAtual;
    int indiceAtual = 0;
    int indiceAux;

    while(!codigoAux.empty())
    {
        std::istringstream iss(codigoAux);
        iss >> trechoAtual;//Leitura de um trecho de texto até o espaço

        for(auto it = this->listaDeTokens.begin(); it != this->listaDeTokens.end(); ++it)
        {

            indiceAux = (*it)->funcaoDeTransicao(trechoAtual, 0, (*(*it)->dfa.begin()));

            if(indiceAux > indiceAtual)
            {
                tokenAtual = (*it)->token;
                indiceAtual = indiceAux;
            }
        }

        //O trecho de código não pertence a linguagem
        if(tokenAtual.empty())
        {
            codigoTokenizado += "<ERRO>";
            int coluna = codigo.size() - codigoAux.size() + indiceAtual;
            this->possicaoDosErros.push_back(std::make_pair(linha, coluna));
        }
        else
        {
            codigoTokenizado += tokenAtual;
        }

        codigoAux.erase(codigoAux.begin(), codigoAux.begin()+indiceAtual+1);

        while(codigoAux[0] == ' ')
            codigoAux.erase(codigoAux.begin());

    }

    return codigoTokenizado;
}

//--------------------------------------------------------------------------
