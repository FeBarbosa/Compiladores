#include "dfa.h"

//--------------------------------------------------------------------------

DFA::DFA(const NFATable& nfa, const std::vector<uchar>& Alfabeto): nfa(nfa), Alfabeto(Alfabeto), idAtual(0){}

//--------------------------------------------------------------------------

//std::unordered_set<NFAEstado*> DFA::epsilonFecho(std::unordered_set<NFAEstado*> setNFA)
//{
//    std::unordered_set<NFAEstado*> result(setNFA);

//    std::stack<NFAEstado*> pilhaEstados;

//    for(auto estado : setNFA)
//        pilhaEstados.push(estado);

//    while (pilhaEstados.size())
//    {
//        NFAEstado* estado = pilhaEstados.top();
//        pilhaEstados.pop();

//        auto range = estado->transicoes.equal_range(EPSILON);

//        std::for_each(range.first, range.second, [&](const auto& p)
//        {
//            if(result.find(p.second) == result.end())
//             {
//                result.insert(p.second);
//                pilhaEstados.push(p.second);
//            }
//        });
//    }

//    return result;
//}

std::vector<NFAEstado*> DFA::calculaFecho(NFAEstado* estadoAtual)
{
    if(estadoAtual->fecho)
    {
        std::unordered_map<NFAEstado*, std::vector<NFAEstado*>>::const_iterator itFind = this->fechos.find(estadoAtual);
        return itFind->second;
    }

    estadoAtual->fecho = true;

//    std::vector<NFAEstado*> listaEstados = {estadoAtual};
     std::vector<NFAEstado*> listaEstados;
     listaEstados.push_back(estadoAtual);

     //std::cout << listaEstados[0]->id << endl;

    auto it = estadoAtual->transicoes.equal_range(EPSILON);

    //std::cout << "BBB" << endl;

    for_each(
        it.first,
        it.second,
        [&](trans::value_type& x){
           auto aux = calculaFecho(x.second);
           listaEstados.insert(listaEstados.end(), aux.begin(), aux.end());
        }
        );

      fechos.insert(std::make_pair(estadoAtual, listaEstados));

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

//void DFA::criarDFA()
//{
//    static auto estadoFinal = [](const std::unordered_set<NFAEstado*>& estados){ return std::any_of(estados.begin(), estados.end(),
//                                                         [](NFAEstado* s){return s->estadoFinal; }); };

//    std::unordered_map<DFAEstado*, std::unordered_set<NFAEstado*>> mapEstados;

//    std::unordered_set<NFAEstado*> setInicial = epsilonFecho(std::unordered_set<NFAEstado*>{nfa.front()});

//    dfa.push_back(new DFAEstado(idAtual++, estadoFinal(setInicial)));

//    mapEstados.emplace(dfa.back(), setInicial);


//        std::stack<DFAEstado*> proxEstado;
//        proxEstado.push(dfa.back());

//        // REMOVER & DO ALFABETO

//        while(proxEstado.size())
//        {
//            DFAEstado* estado = proxEstado.top();
//            proxEstado.pop();

//            for(uchar c: Alfabeto)
//            {
//                std::unordered_set<NFAEstado*> setRes = epsilonFecho(moveFecho(mapEstados[estado], c));

//                auto it = std::find_if(dfa.begin(), dfa.end(),
//                                       [&](const auto& s){return setRes == mapEstados[s]; });

//                if(it == dfa.end())
//                {
//                    dfa.push_back(new DFAEstado(idAtual++, estadoFinal(setRes), setRes.empty()));

//                    mapEstados.emplace(dfa.back(), setRes);

//                    estado->transicoes.emplace(c, dfa.back());

//                    proxEstado.push(dfa.back());
//                }

//                else
//                    estado->transicoes.emplace(c, *it);
//            }
//        }
//}

using namespace std;

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
