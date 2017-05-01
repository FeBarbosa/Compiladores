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
#include <memory>
#include <map>
#include "estado.h"
#include "expreregular.h"

#define EPSILON '&'

using uchar = unsigned char; //define um apelido

class NFAEstado;

//----------------------------------------------------------
class NFAEstado: public estado
{
    public:
    using estado::estado; // Permite o uso de apenas "estado" como construtor dentro deste escopo
    std::multimap<uchar, NFAEstado*> transicoes; //Tabela de Transicoes
};

//---------------------------------------------------------------
using NFATable = std::deque<NFAEstado*>; //Funciona com um #DEFINE

typedef std::multimap<uchar, NFAEstado*> trans;

//---------------------------------------------------------------
class NFA
{
public:
    ///CONSTRUTOR------------------------------------------------
    NFA(const std::string&);

    ///METODOS -------------------------------------------------
    void criarNFA();     /* Converte Expressão regular para NFA*/

    NFATable base(uchar);  /* Cria a base do Autômato */
    void kleene(NFATable&);
    void uniao(NFATable&, NFATable&);
    void conca(NFATable&, NFATable&);
    void show();
    void renomeiaEstados(NFATable&, int);

    ///ATRIBUTOS --------------------------------------------------
    std::string strNFA;
    int idAtual;
    std::vector<uchar> Alfabeto;   /* Alfabeto */
    NFATable nfa;                         /* O Autômato */
};

#endif // NFA_H
