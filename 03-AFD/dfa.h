#ifndef DFA_H
#define DFA_H

#include "estado.h"
#include "nfa.h"

class DFAEstado;

//----------------------------------------------------------
class DFAEstado : public estado
{
public:

    using estado::estado; // Permite o uso de apenas "estado" como construtor dentro deste escopo
    std::unordered_map<uchar, DFAEstado*> transicoes; //Tabela de Transicoes
};
//---------------------------------------------------------------

using DFATable = std::deque<DFAEstado*>;

//---------------------------------------------------------------
class DFA
{
public:
    DFA(const NFATable&, const std::unordered_set<uchar>&);

    //MÉTODOS ----------------------------------------------------
    std::unordered_set<NFAEstado*> epsilonFecho(std::unordered_set<NFAEstado*>);
    std::unordered_set<NFAEstado*> moveFecho(const std::unordered_set<NFAEstado*>&, uchar);
    void criarDFA();
    void show();

    //ATRIBUTOS ---------------------------------------------
    NFATable nfa;
    DFATable dfa;
    std::unordered_set<uchar> Alfabeto;        /** Alfabeto */
    int idAtual;
};

#endif // DFA_H
