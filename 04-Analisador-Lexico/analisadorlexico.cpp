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

    NFA NFAaux = NFA(padraoAux->posFix);

    NFAaux.criarNFA();

    DFA *DFAaux = new DFA(NFAaux.nfa, NFAaux.Alfabeto, tokenNovo, padraoNovo);

    DFAaux->criarDFA();
    this->listaDeTokens.push_back(DFAaux);
}
//--------------------------------------------------------------------------
