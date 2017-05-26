#include "analisadorSintatico.h"

namespace ll
{

    std::deque<simbolo> simbolosVisitados;

    simbolo palavraVazia = simbolo(true, "&");

    simbolo cifrao = simbolo(true, "$");

    // CONSTRUTOR -----------------------------------------------------------------------
    analisadorSintatico::analisadorSintatico(){}

    analisadorSintatico::analisadorSintatico(const std::vector<std::string> &variaveis,
                               const std::vector<std::string> &terminais ,
                               const std::vector<std::string> &producoes,
                               const std::string &inicial)
    {

        for(int i = 0; i < (int)variaveis.size(); i++)
        {
            simbolo aux(false, variaveis[i]);
           this->conjuntoDeSimbolos.insert(aux);
        }

        for(int i = 0; i < (int)terminais.size(); i++)
        {
            simbolo aux(true, terminais[i]);
            this->conjuntoDeSimbolos.insert(aux);
        }

        this->simboloInicial = simbolo(true, inicial);

        criarProducoes(producoes);

//        for(auto it = this->conjuntoDeProducoes.begin(); it != this->conjuntoDeProducoes.end(); ++it)
//        {
//            std::cout << it->first << ": ";

//            for(int i = 0; i < it->second.size(); i++)
//                std::cout << it->second[i];

//            std::cout << std::endl;
//        }

        this->calcularFirst();
        this->calcularFollow();
        this->calcularTabelaSintatica();
    }

    // ----------------------------------------------------------------------------------
    void analisadorSintatico::criarProducoes(const std::vector<std::string> &producoesStr)
    {
        std::string aux;

        //Percorre a lista de produções ainda na forma de string
        for(int i = producoesStr.size() -1 ; i >= 0 ; i--)
        {
            // trecho para separar os símbolos em tokens --------------------------------
            char *auxstr = strdup(producoesStr[i].c_str());
            char *pch;

            std::vector<std::string> strTokenizada;

            pch = strtok(auxstr, "-> ");

            while(pch != NULL)
            {
                strTokenizada.push_back(pch);
                pch = strtok(NULL, "-> ");
            }
            //---------------------------------------------------------------------------

            // Guarda chave do mapeamento de produções
            aux = strTokenizada.front();
            strTokenizada.erase(strTokenizada.begin());

            simbolo simboloAux(true, aux);

            std::vector<simbolo> producoesAux;

            for(int k = 0; k < (int)strTokenizada.size(); k++)
            {
                if(!strTokenizada[k].compare("|"))
                {
                    this->conjuntoDeProducoes.emplace(simboloAux, producoesAux);
                    producoesAux.clear();
                }
                else
                {
                    simbolo simboloAux(strTokenizada[k]);
                    auto itfind = this->conjuntoDeSimbolos.find(simboloAux);
                    if(itfind->terminal == true)
                        producoesAux.push_back(simbolo(true, strTokenizada[k]));
                    else
                        producoesAux.push_back(simbolo(false, strTokenizada[k]));
                }
            }

            this->conjuntoDeProducoes.emplace(simboloAux, producoesAux);
        }
    }

    // ----------------------------------------------------------------------------------
    void analisadorSintatico::calcularFirst()
    {
        for(auto it = this->conjuntoDeSimbolos.begin(); it != this->conjuntoDeSimbolos.end(); ++it)
            if(!it->terminal)
             {
                std::set<simbolo> aux = calcularFirst(*it);
                this->conjuntoFirst.emplace(*it, aux);
             }

//        for(auto it = this->conjuntoFirst.begin(); it != this->conjuntoFirst.end(); ++it)
//        {
//            std::cout << it->first << ": ";

//            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
//                std::cout << *it2 << " ";

//            std::cout << std::endl << std::endl;

//        }

//        std::cout << std::endl;
    }

    //-----------------------------------------------------------------------------------
    std::set<simbolo> analisadorSintatico::calcularFirst(const simbolo &variavel)
    {
        std::set<simbolo> conjuntoDeSimbolosAux;

        //Chama o conjunto
        auto range = this->conjuntoDeProducoes.equal_range(variavel);

        bool continuar = true;

        // Chamada o conjunto first verificando o primeiro símbolo de cada elemento da união
        for_each(
            range.first,
            range.second,
            [&](producoes::value_type& x){
                for(unsigned int i = 0; i < x.second.size(); i++)
                {
                    if(x.second[i].terminal)// O símbolo é terminal
                    {
                        conjuntoDeSimbolosAux.insert(x.second[i]);
                        break;
                    }
                    else// O símbolo não é terminal
                    {
                        continuar = false;

                        std::set<simbolo> aux2 = calcularFirst(x.second[i]); //Chama recursivamente o first do símbolo
                        for(auto it = aux2.begin(); it != aux2.end(); ++it)
                        {
                            if(((it)->compare(palavraVazia) != 0 || (i == x.second.size() - 1)))
                            {
                                conjuntoDeSimbolosAux.insert(*it);
                            }
                            else
                            {
                                continuar = true;
                            }
                        }

                        if(!continuar)
                            break;
                    }
                }
        }
        );

        return conjuntoDeSimbolosAux;
    }
    // ----------------------------------------------------------------------------------
    void analisadorSintatico::calcularFollow()
    {
        for(auto it = this->conjuntoDeSimbolos.begin(); it != this->conjuntoDeSimbolos.end(); ++it)
            if(!it->terminal)
             {
                std::set<simbolo> aux = calcularFollow(*it);
                this->conjuntoFollow.emplace(*it, aux);
             }

//        for(auto it = this->conjuntoFollow.begin(); it != this->conjuntoFollow.end(); ++it)
//        {
//            std::cout << it->first << ": ";

//            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
//                std::cout << *it2 << " ";

//            std::cout << std::endl << std::endl;

//        }

//        std::cout << std::endl;
    }

    //----------------------------------------------------------------------------------------
    std::set<simbolo> analisadorSintatico::calcularFollow(const simbolo &variavel)
    {
        std::set<simbolo> followAux;

        //O símbolo a se calcular o follow já foi visitado na recursão
        for(unsigned int i = 0; i < simbolosVisitados.size(); i++)
        {
            if(!variavel.compare(simbolosVisitados[i]))
                return followAux;
        }

        //Marco o símbolo como visitado
        simbolosVisitados.push_back(variavel);

        int indice;
        bool continuar;

        //Se for a variável inicial, insere $ no conjunto follow
        if(!variavel.compare(this->simboloInicial))
            followAux.insert(simbolo(true, "$"));


        //Procura a ocorrência da variável no conjunto de produções
        for(auto it = this->conjuntoDeProducoes.begin(); it != this->conjuntoDeProducoes.end(); ++it)
        {
            indice = -1;

            //Procura a variável na produção atual
            for(unsigned int i = 0; i < it->second.size(); i++)
            {
                //se a variável ocorre, guarda a posição em indice
                if(it->second[i] == variavel)
                {
                    indice = i;
                    break;
                }
            }

            //O elemento ocorre na última posição da produção, assim deve-se calcular o follow
            //da variável que gera a produção
            if(indice == (int)(it->second.size() -1))
            {
                std::set<simbolo> followAux2 = calcularFollow(it->first);
                followAux.insert(followAux2.begin(), followAux2.end());
            }
            else if(indice != -1)//o elemento foi encontrado e não é o último
            {
                //percorre os símbolos seguintes
                for(unsigned int i = indice+1; i < it->second.size(); i++)
                {
                    continuar = false;

                    //se o símbolo for terminal, insere o mesmo no conjunto follow e finaliza
                    if(it->second[i].terminal)
                    {
                        followAux.insert(it->second[i]);
                        break;
                    }
                    else//o símbolo é variável
                    {
                        //pega o first da variável
                        auto itfind = this->conjuntoFirst.find(it->second[i]);

                        //percorre o first da variável e insere os elementos no follow (se diferente de vazio)
                        for(auto it2 = itfind->second.begin(); it2 != itfind->second.end(); ++it2)
                        {
                            if(it2->compare(palavraVazia) == 0)// se igual a palavra vazia, calcular o first da próxima variável
                                continuar = true;
                            else
                                followAux.insert(*it2);
                        }

                        if(!continuar)
                            break;

                        //Se deve continuar e o elemento atual é o fim da produção
                        //calcular o follow da variável que gera a produção atual
                        if(i == it->second.size()-1 && continuar)
                        {
                            std::set<simbolo> followAux2 = calcularFollow(it->first);
                            followAux.insert(followAux2.begin(), followAux2.end());
                        }
                    }
                }
            }
        }

        simbolosVisitados.pop_front();

        return followAux;
    }

    //--------------------------------------------------------------------------------------------
    void analisadorSintatico::calcularTabelaSintatica()
    {
        //Percorrer o conjunto de produções para gerar as linhas da tabela
        for(auto it = this->conjuntoDeProducoes.begin(); it != this->conjuntoDeProducoes.end(); ++it)
        {
            //O primeiro símbolo da produção atual é terminal e não é palavra vazia
            if((it->second[0].terminal == true) && (it->second[0].compare(palavraVazia) != 0))
            {
                this->tabelaSintatica[it->first][it->second[0]] = it->second;
            }
            else//O primeiro símbolo não é terminal ou é a palavra vazia
            {
                auto FirstA = this->conjuntoFirst[it->first];

                if(FirstA.find(palavraVazia) == FirstA.end())//firstA não possui vazio
                {

                    //Percorre o conjunto first(A) e insere a produção A em M[A, simbolo]
                    //onde simbolo pertence a first(A)
                    for(auto it2 = FirstA.begin(); it2 != FirstA.end(); ++it2)
                        this->tabelaSintatica[it->first][*it2] = it->second;
                }
                else //firstA possui vazio
                {

                    //o elemento não é vazio
                    if(it->second[0].compare(palavraVazia) != 0)
                    {
                        auto FirstB = this->conjuntoFirst[it->second[0]];

                        //Percorre o conjunto first(B) e insere a produção A em M[A, simbolo]
                        //onde simbolo pertence a first(B)
                        for(auto it2 = FirstB.begin(); it2 != FirstB.end(); ++it2)
                            if((it2)->compare(palavraVazia) != 0)//Exclui a palavra vazia se existir
                                this->tabelaSintatica[it->first][*it2] = it->second;


                        //first(B) possui vazio
                        if(FirstB.find(palavraVazia) != FirstB.end())
                        {
                            //calcula o follow(A)
                            auto FollowA = this->conjuntoFollow[it->first];

                            //Percorre o follow(A) e insere a produção A em M[A, simbolo]
                            //onde simbolo pertence a follow(A)
                            for(auto it2 = FollowA.begin(); it2 != FollowA.end(); ++it2)
                                this->tabelaSintatica[it->first][*it2] = it->second;
                        }
                   }
                   else //o elemento é vazio
                   {
                          auto FollowA = this->conjuntoFollow[it->first];

                          //Percorre o follow(A) e insere a produção A em M[A, simbolo]
                          //onde simbolo pertence a follow(A)
                          for(auto it2 = FollowA.begin(); it2 != FollowA.end(); ++it2)
                              this->tabelaSintatica[it->first][*it2] = it->second;

                   }
                }
            }
        }
    }

    //----------------------------------------------------------------------------------------
    bool analisadorSintatico::analisarCodigo(std::list<std::string> codigo)
    {
        if(codigo.empty())
            return true;

        std::stack<simbolo> pilhaDeSimbolos;

        pilhaDeSimbolos.push(cifrao);
        pilhaDeSimbolos.push(this->simboloInicial);

        codigo.push_back(cifrao);

        while(!pilhaDeSimbolos.empty())
        {

            if((pilhaDeSimbolos.top().compare(cifrao) == 0) && (codigo.front().compare(cifrao) == 0))
            {
                return true;
            }

            if(pilhaDeSimbolos.top().compare(codigo.front()) == 0)
            {
                pilhaDeSimbolos.pop();
                codigo.pop_front();
            }

            std::vector<simbolo> producaoAtual;

            for(auto it = this->tabelaSintatica.begin(); it != this->tabelaSintatica.end(); ++it)
            {
                if(it->first.compare(pilhaDeSimbolos.top()) == 0)
                    for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                    {
                        if(it2->first.compare(codigo.front()) == 0)
                        {
                            producaoAtual.insert(producaoAtual.begin(), it2->second.begin(), it2->second.end());
                        }
                    }
            }

            if(producaoAtual.empty())
            {
                return false;
            }

            pilhaDeSimbolos.pop();

            if(producaoAtual[0].compare(palavraVazia) != 0)
                for(int i = producaoAtual.size(); i > 0 ; i--)
                    pilhaDeSimbolos.push(producaoAtual[i-1]);

        }
    }

}
