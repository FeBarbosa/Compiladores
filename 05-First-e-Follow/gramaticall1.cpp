#include "gramaticall1.h"

namespace ll
{

    std::deque<simbolo> simbolosVisitados;

    // CONSTRUTOR -----------------------------------------------------------------------
    gramaticaLL1::gramaticaLL1(const std::vector<std::string> &variaveis,
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
    }

    // ----------------------------------------------------------------------------------
    void gramaticaLL1::criarProducoes(const std::vector<std::string> &producoesStr)
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
    void gramaticaLL1::calcularFirst()
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
    }

    //-----------------------------------------------------------------------------------
    std::set<simbolo> gramaticaLL1::calcularFirst(const simbolo &variavel)
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
                for(int i = 0; i < x.second.size(); i++)
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
                            if((*it != "&") || (i == x.second.size() - 1))
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
    void gramaticaLL1::calcularFollow()
    {
        for(auto it = this->conjuntoDeSimbolos.begin(); it != this->conjuntoDeSimbolos.end(); ++it)
            if(!it->terminal)
             {
                std::set<simbolo> aux = calcularFollow(*it);
                this->conjuntoFollow.emplace(*it, aux);
             }

        for(auto it = this->conjuntoFollow.begin(); it != this->conjuntoFollow.end(); ++it)
        {
            std::cout << it->first << ": ";

            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                std::cout << *it2 << " ";

            std::cout << std::endl << std::endl;

        }
    }
    //-----------------------------------------------------------------------------------
    std::set<simbolo> gramaticaLL1::calcularFollow(const simbolo &variavel)
    {
        std::set<simbolo> followAux;

        for(int i = 0; i < simbolosVisitados.size(); i++)
        {
            if(!variavel.compare(simbolosVisitados[i]))
                return followAux;
        }

        simbolosVisitados.push_back(variavel);

        int indice;
        bool continuar;

        if(!variavel.compare(this->simboloInicial))
            followAux.insert(simbolo(true, "$"));


        for(auto it = this->conjuntoDeProducoes.begin(); it != this->conjuntoDeProducoes.end(); ++it)
        {
            indice = -1;

            for(int i = 0; i < it->second.size(); i++)
            {
                if(it->second[i] == variavel)
                {
                    indice = i;
                    break;
                }
            }

            if(indice == it->second.size() -1)
            {
                std::set<simbolo> followAux2 = calcularFollow(it->first);
                followAux.insert(followAux2.begin(), followAux2.end());
            }
            else if(indice != -1)
            {
                for(int i = indice+1; i < it->second.size(); i++)
                {
                    std::cout << "AAA" << std::endl;

                    continuar = false;

                    if(it->second[i].terminal)
                    {
                        followAux.insert(it->second[i]);
                        break;
                    }
                    else
                    {

                        auto itfind = this->conjuntoFirst.find(it->second[i]);

                        for(auto it2 = itfind->second.begin(); it2 != itfind->second.end(); ++it2)
                        {
                            if(*it2 == "&")
                                continuar = true;
                            else
                                followAux.insert(*it2);
                        }

                        if(!continuar)
                            break;

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

}
