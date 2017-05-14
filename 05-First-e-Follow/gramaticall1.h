#ifndef GRAMATICALL1_H
#define GRAMATICALL1_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

#include "simbolo.h"

namespace ll
{

    using producoes = std::unordered_multimap<simbolo, std::vector<simbolo>>;

    class gramaticaLL1
    {
    public:

        // CONSTRUTORES -------------------------------------------------------
        gramaticaLL1(const std::vector<std::string>&, const std::vector<std::string>&,
                     const std::vector<std::string>&, const std::string&);

        // MÉTODOS ------------------------------------------------------------


        // ATRIBUTOS ----------------------------------------------------------
        simbolo simboloInicial;
        producoes conjuntoDeProducoes;
        std::unordered_set<simbolo> conjuntoDeSimbolos;

        std::unordered_map<simbolo, std::unordered_set<simbolo>> conjuntoFirst;
        std::unordered_map<simbolo, std::unordered_set<simbolo>> conjuntoFollow;
    };

}


#endif // GRAMATICALL1_H
