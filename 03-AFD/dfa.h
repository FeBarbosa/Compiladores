#ifndef DFA_H
#define DFA_H

#include "estado.h"
#include "expreregular.h"
#include "nfa.h"
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>

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
    NFAEstado* moveFecho(NFAEstado* estadoAtual, uchar simbolo);
    std::unordered_set<NFAEstado*> calculaFecho(NFAEstado*);
    void CriaEstadoDeErro();

    void criarDFA();
    void show();

    //ATRIBUTOS ---------------------------------------------
    NFATable nfa;
    DFATable dfa;
    DFAEstado *estadoErro;
    std::map<NFAEstado*, std::unordered_set<NFAEstado*>, comp> fechos;
    std::vector<uchar> Alfabeto;        /** Alfabeto */
    int idAtual;
    bool estadoErroUsado;
};

#endif // DFA_H
