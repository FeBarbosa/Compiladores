#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
#include <iostream>

#include "estado.h"

#define EPSILON '&'

using uchar = unsigned char; // define um apelido

class NFAEstado;

//------------------------------------------------------------------------------------------
class NFAEstado: public estado
{
    public:
        using estado::estado; // Permite o uso de apenas "estado" como construtor dentro deste escopo

        std::unordered_multimap<uchar, NFAEstado*> transicoes; //Tabela de Transicoes
};

//------------------------------------------------------------------------------------------

using NFATable = std::deque<NFAEstado*>; //Funciona como um #DEFINE

//------------------------------------------------------------------------------------------
class NFA
{
public:

    ///CONSTRUTOR ------------------------------------------
    NFA(const std::string&);


    ///MÉTODOS ---------------------------------------------
    void criarNFA();                            /** Converte Expressão regular para NFA*/

    NFATable base(uchar);                        /** Cria a base do Autômato */
    void kleene(NFATable&);
    void uniao(NFATable&, NFATable&);
    void conca(NFATable&, NFATable&);
    bool operador(char);
    void show();

    ///ATRIBUTOS -------------------------------------------

    std::string strNFA;
    int idAtual;
    std::unordered_set<uchar> Alfabeto;        /** Alfabeto */
    NFATable nfa;                              /** O Autômato */
};

#endif // NFA_H
