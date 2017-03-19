#include "nfa.h"

NFA::NFA(const std::string& strNFA):strNFA(strNFA), idAtual(0){}

// Cria a base do autômato ----------------------------------------------
NFATable NFA::base(uchar c)
{
    NFAEstado* estadoInicial = new NFAEstado(idAtual++);
    NFAEstado* estadoFinal   = new NFAEstado(idAtual++);

    estadoInicial->transicoes.emplace(c, estadoFinal);

    return NFATable{estadoInicial, estadoFinal};
}

//------------------------------------------------------------------------
void NFA::kleene(NFATable &t)
{
    NFAEstado* estadoInicial = new NFAEstado(idAtual++);
    NFAEstado* estadoFinal   = new NFAEstado(idAtual++);

    estadoInicial->transicoes.emplace(EPSILON, t.front());
    estadoInicial->transicoes.emplace(EPSILON, estadoFinal);

    t.back()->transicoes.emplace(EPSILON, t.front());       // FINAL transição INICIAL &
    t.back()->transicoes.emplace(EPSILON, estadoFinal);

    t.push_front(estadoInicial);
    t.push_back(estadoFinal);
}

//-------------------------------------------------------------------
void NFA::conca(NFATable& t1, NFATable& t2)
{
    t1.back()->transicoes.emplace(EPSILON, t2.front());
    t1.insert(t1.end(), t2.begin(), t2.end());
}

//----------------------------------------------------------------------
void NFA::uniao(NFATable& t1, NFATable& t2)
{
    NFAEstado* estadoInicial = new NFAEstado(idAtual++);
    NFAEstado* estadoFinal   = new NFAEstado(idAtual++);

    estadoInicial->transicoes.emplace(EPSILON, t1.front());
    estadoInicial->transicoes.emplace(EPSILON, t2.front());

    t1.back()->transicoes.emplace(EPSILON, estadoFinal);
    t2.back()->transicoes.emplace(EPSILON, estadoFinal);

    t1.push_front(estadoInicial);
    t2.push_back(estadoFinal);

    t1.insert(t1.end(), t2.begin(), t2.end());
}

//-------Verifica se um caracter é um símbolo------------------------------------
bool NFA::operador(char c)
{
    if(c == '*' || c =='+' || c =='.')
        return true;

    return false;
}

// Cria o NFA--------------------------------------------------------------------
void NFA::criarNFA()
{
    std::vector<NFATable> NFAPilha;
    uchar c;

    for(int i = 0; i < (int)strNFA.length(); i++)
    {
        c = strNFA[i];
        if(!operador(c))
        {
            NFAPilha.push_back(base(c));  //Cria e empilha um autômato com a base do símbolo c
            Alfabeto.insert(c);
        }
        else
        {
            switch (c)
            {
                case '*':
                    kleene(NFAPilha.back());
                    break;
                case '.':
                    conca(*(NFAPilha.rbegin()+1), NFAPilha.back());
                    NFAPilha.pop_back();
                    break;
                case '+':
                    uniao(*(NFAPilha.rbegin() + 1), NFAPilha.back());
                    NFAPilha.pop_back();
                    break;
            }
        }
    }

    nfa = std::move(NFAPilha.front());
    nfa.back()->estadoFinal = true;
}
using namespace std;

void NFA::show()
{
    for(auto it = nfa.begin(); it != nfa.end(); ++it)  ///percorre o deque
    {
        cout << "q" << (*it)->id << " : ";

        if((*it)->estadoFinal)
            cout << "Final";

        cout << endl;

        for(auto it2 = (*it)->transicoes.begin(); it2 != (*it)->transicoes.end(); ++it2) ///percorre o unordered_multimap
            cout << (*it2).first << " : q" << (*it2).second->id << endl;

        cout << endl << endl;
    }
}
