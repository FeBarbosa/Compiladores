#ifndef DFA_H
#define DFA_H

#include "estado.h"
#include "expreregular.h"
#include "nfa.h"
#include <sstream>
#include <iostream>
#include <map>
#include <set>

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


struct comp
{
    bool operator () (NFAEstado* a, NFAEstado* b)const
    {
        return a->id < b->id;
    }
};

//---------------------------------------------------------------
class DFA
{
public:
    DFA(const NFATable&, const std::vector<uchar>&);

    //MÉTODOS ----------------------------------------------------
    std::unordered_set<NFAEstado*> moveFecho(const std::unordered_set<NFAEstado*>&, uchar);
    std::unordered_set<NFAEstado*> calculaFecho(NFAEstado*);

    void criarDFA();
    void show();

    //ATRIBUTOS ---------------------------------------------
    NFATable nfa;
    DFATable dfa;
    std::map<NFAEstado*, std::unordered_set<NFAEstado*>, comp> fechos;
    std::vector<uchar> Alfabeto;        /** Alfabeto */
    int idAtual;
};

#endif // DFA_H
