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
//std::unordered_set<NFAEstado*> DFA::moveFecho(const std::unordered_set<NFAEstado*>& setNFA, uchar c)
//{
//    std::unordered_set<NFAEstado*> result;

//    for(auto estado : setNFA)
//    {
//        auto range = estado->transicoes.equal_range(c);
//        std::for_each(range.first, range.second, [&](const auto& p) {result.insert(p.second);});
//    }
//    return result;
//}

NFAEstado* DFA::moveFecho(NFAEstado* estadoAtual, uchar simbolo)
{
    auto itFind = this->fechos.find(estadoAtual);
    NFAEstado* novoEstado;
    for(auto it = itFind->second.begin(); it != itFind->second.end(); ++it)
    {
        auto itFind2 = (*it)->transicoes.equal_range(simbolo);

        // VERIFICAR QUANDO NÃO TIVER TRANSIÇÃO PARA O SIMBOLO

        for_each(
            itFind2.first,
            itFind2.second,
            [&novoEstado](trans::value_type& x){
                novoEstado = x.second;
        }
        );
    }

    return novoEstado;
}


//---------------------------------------------------------------------------------

void DFA::criarDFA()
{

    bool estadoExiste;

    this->Alfabeto.pop_back();//Remove o EPSILON do alfabeto

    //Inserir estados na lista de &-fechos
    for(auto it = this->nfa.begin(); it != this->nfa.end(); ++it)
    {
        this->fechos.insert(std::make_pair(*it, std::unordered_set<NFAEstado*>({})));
    }

    //Cria a lista de fechos
    for(auto it = this->nfa.begin(); it != this->nfa.end(); ++it)
    {
        calculaFecho(*(it));

        //torna os estados não visitados para calcular o próximo fecho
        for(auto it2 = this->nfa.begin(); it2 != this->nfa.end(); ++it2)
        {
            (*it2)->fecho = false;
        }
    }



    // inicia a pilha com estado inicial
    auto it = fechos.begin();
    std::stack<NFAEstado*> pilhaDeEstados;
    pilhaDeEstados.push(it->first);

    // Cria e insere o estado inicial (sem as transições)
    DFAEstado* estadoInicial = new DFAEstado(it->first->id);
    this->dfa.push_back(estadoInicial);


    //Parte que cria o DFA
    while(!pilhaDeEstados.empty())
    {
        DFAEstado* atual;

        //busca o elemento atual para inserir transições
        for(auto it = this->dfa.begin(); it != dfa.end(); ++it)
            if((*it)->id == pilhaDeEstados.top()->id)
                atual = *it;

        for(int i = 0; i < (int)this->Alfabeto.size(); i++)
        {
            estadoExiste = false;

            NFAEstado* novoEstado = moveFecho(pilhaDeEstados.top(), this->Alfabeto[i]);


            for(auto it = this->dfa.begin(); it != dfa.end(); ++it)
            {
                if((*it)->id == novoEstado->id)
                {
                    estadoExiste = true;
                }

            }

            if(!estadoExiste)
            {
                DFAEstado* novo = new DFAEstado(novoEstado->id);
                this->dfa.push_back(novo); //Insere um novo estado


                //Insere a transição no estado atual
                atual->transicoes.emplace(this->Alfabeto[i], novo);

                pilhaDeEstados.push(novoEstado);

            }
            else
            {
                for(auto it = dfa.begin(); it != dfa.end(); ++it)
                    if((*it)->id == novoEstado->id)
                         atual->transicoes.emplace(this->Alfabeto[i], *it);
            }

        }

        pilhaDeEstados.pop();
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
