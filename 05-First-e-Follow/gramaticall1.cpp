#include "gramaticall1.h"

namespace ll
{

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

        criarProducoes(producoes);
        this->simboloInicial = simbolo(true, inicial);

        this->calcularFirst();
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

        for(auto it = this->conjuntoFirst.begin(); it != this->conjuntoFirst.end(); ++it)
        {
            std::cout << it->first << ": ";

            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                std::cout << *it2 << " ";

            std::cout << std::endl << std::endl;

        }
    }

    //-----------------------------------------------------------------------------------
    std::set<simbolo> gramaticaLL1::calcularFirst(const simbolo &variavel)
    {
        std::set<simbolo> conjuntoDeSimbolosAux;

        //Chama o conjunto
        auto range = this->conjuntoDeProducoes.equal_range(variavel);

        // Chamada o conjunto first verificando o primeiro símbolo de cada elemento da união
        for_each(
            range.first,
            range.second,
            [&](producoes::value_type& x){
                if(x.second[0].terminal)// O símbolo é terminal
                    conjuntoDeSimbolosAux.insert(x.second[0]);
                else// O símbolo não é terminal
                {
                    std::set<simbolo> aux2 = calcularFirst(x.second[0]); //Chama recursivamente o first do símbolo
                    conjuntoDeSimbolosAux.insert(aux2.begin(), aux2.end());
                }
        }
        );

        return conjuntoDeSimbolosAux;
    }
    // ----------------------------------------------------------------------------------

}
