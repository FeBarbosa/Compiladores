#ifndef GRAMATICALL1_H
#define GRAMATICALL1_H

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "simbolo.h"

namespace ll
{

    using producoes = std::unordered_multimap<simbolo, std::vector<simbolo>>;

    class gramaticaLL1
    {
    public:

        // CONSTRUTORES -----------------------------------------------------------------
        gramaticaLL1(const std::vector<std::string>&, const std::vector<std::string>&,
                     const std::vector<std::string>&, const std::string&);

        // MÉTODOS ----------------------------------------------------------------------
        void criarProducoes(const std::vector<std::string>&);
        void calcularFirst();
        std::set<simbolo> calcularFirst(const simbolo&);
        void calcularFollow();

        // ATRIBUTOS --------------------------------------------------------------------
        simbolo simboloInicial;
        producoes conjuntoDeProducoes;
        std::unordered_set<simbolo> conjuntoDeSimbolos;
        std::map<simbolo, std::set<simbolo>> conjuntoFirst;
        std::map<simbolo, std::set<simbolo>> conjuntoFollow;

    };

}


#endif // GRAMATICALL1_H
