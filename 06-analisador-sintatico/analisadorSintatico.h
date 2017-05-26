#ifndef analisadorSintatico_H
#define analisadorSintatico_H

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <stack>
#include <list>

#include "simbolo.h"

namespace ll
{

    using producoes = std::unordered_multimap<simbolo, std::vector<simbolo>>;
    using tabelaLL1 = std::unordered_map<simbolo, std::unordered_map<simbolo, std::vector<simbolo>>>;

    class analisadorSintatico
    {
    public:

        // CONSTRUTORES -----------------------------------------------------------------
        analisadorSintatico();

        analisadorSintatico(const std::vector<std::string>&, const std::vector<std::string>&,
                     const std::vector<std::string>&, const std::string&);

        // MÉTODOS ----------------------------------------------------------------------
        void criarProducoes(const std::vector<std::string>&);
        void calcularFirst();
        std::set<simbolo> calcularFirst(const simbolo&);
        void calcularFollow();
        std::set<simbolo> calcularFollow(const simbolo&);
        void calcularTabelaSintatica();
        bool analisarCodigo(std::list<std::string>);

        // ATRIBUTOS --------------------------------------------------------------------
        simbolo simboloInicial;
        producoes conjuntoDeProducoes;
        std::unordered_set<simbolo> conjuntoDeSimbolos;
        std::map<simbolo, std::set<simbolo>> conjuntoFirst;
        std::map<simbolo, std::set<simbolo>> conjuntoFollow;
        tabelaLL1 tabelaSintatica;

    };

}


#endif // analisadorSintatico_H
