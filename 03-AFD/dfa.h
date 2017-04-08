#ifndef DFA_H
#define DFA_H

#include "estado.h"
#include "expreregular.h"
#include "nfa.h"
#include <sstream>
#include <iostream>

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
    DFA(const NFATable&, const std::vector<uchar>&);

    //MÉTODOS ----------------------------------------------------
    //std::unordered_set<NFAEstado*> epsilonFecho(std::unordered_set<NFAEstado*>);
    std::unordered_set<NFAEstado*> moveFecho(const std::unordered_set<NFAEstado*>&, uchar);
    std::vector<NFAEstado*> calculaFecho(NFAEstado*);

    void criarDFA();
    void show();

    //ATRIBUTOS ---------------------------------------------
    NFATable nfa;
    DFATable dfa;
    std::unordered_map<NFAEstado*, std::vector<NFAEstado*>> fechos;
    std::vector<uchar> Alfabeto;        /** Alfabeto */
    int idAtual;
};

#endif // DFA_H
