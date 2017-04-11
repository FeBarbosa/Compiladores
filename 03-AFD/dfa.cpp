#include "dfa.h"

//--------------------------------------------------------------------------

DFA::DFA(const NFATable& nfa, const std::vector<uchar>& Alfabeto): nfa(nfa), Alfabeto(Alfabeto), idAtual(0){}

//--------------------------------------------------------------------------

std::unordered_set<NFAEstado*> DFA::calculaFecho(NFAEstado* estadoAtual)
{
    if(estadoAtual->fecho)
    {
        auto itFind = this->fechos.find(estadoAtual);
        return itFind->second;
    }

    estadoAtual->fecho = true;

    //insere em fechos {fecho(qi) = {qi}}
    std::unordered_set<NFAEstado*> listaEstados;
    listaEstados.insert(estadoAtual);

    auto it = estadoAtual->transicoes.equal_range(EPSILON);

    for_each(
        it.first,
        it.second,
        [&](trans::value_type& x){
           //itFind->second.insert(x.second);
           auto aux = calculaFecho(x.second);
           listaEstados.insert(aux.begin(), aux.end());
        }
        );

      auto itFind = this->fechos.find(estadoAtual);
      itFind->second.insert(listaEstados.begin(), listaEstados.end());
      return listaEstados;
}

//------------------------------------------------------------------------------
std::unordered_set<NFAEstado*> DFA::moveFecho(const std::unordered_set<NFAEstado*>& setNFA, uchar c)
{
    std::unordered_set<NFAEstado*> result;

    for(auto estado : setNFA)
    {
        auto range = estado->transicoes.equal_range(c);
        std::for_each(range.first, range.second, [&](const auto& p) {result.insert(p.second);});
    }
    return result;
}


//---------------------------------------------------------------------------------

void DFA::criarDFA()
{

    //Inserir estados na lista de &-fechos
    for(auto it = this->nfa.begin(); it != this->nfa.end(); ++it)
    {
        this->fechos.insert(std::make_pair(*it, std::unordered_set<NFAEstado*>({})));
    }

    for(auto it = this->nfa.begin(); it != this->nfa.end(); ++it)
    {
        calculaFecho(*(it));

        for(auto it2 = this->nfa.begin(); it2 != this->nfa.end(); ++it2)
        {
            (*it2)->fecho = false;
        }
    }
}

using namespace std;

//-----------------------------------------------------------------------------------------------

void DFA::show()
{
    for(auto it = Alfabeto.begin(); it !=Alfabeto.end(); ++it)
        cout<< " "<< *it;
    cout << endl;

    cout << nfa.size() << endl;

    for(auto it = dfa.begin(); it != dfa.end(); ++it) //percorre o deque
    {
        cout << "q" << (*it)->id << " : ";

        if((*it)->estadoFinal)
            cout << "Final";

        cout << endl;

        for(auto it2 = (*it)->transicoes.begin(); it2 != (*it)->transicoes.end(); ++it2)  /// percorre o unordered_multimap
            cout << (*it2).first << " :q" << (*it2).second->id << endl;

        cout << endl << endl;
    }
}
