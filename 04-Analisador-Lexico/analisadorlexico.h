#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H
#include <QMessageBox>
#include "estado.h"
#include "expreregular.h"
#include "nfa.h"
#include "dfa.h"
#include <string>
#include <iostream>

class AnalisadorLexico
{
public:

    // CONSTRUTOR ----------------------------------------------
    AnalisadorLexico();

    // METODOS -------------------------------------------------
    void calcularPadrao(std::string, std::string);
    std::string analise(std::string, int);

    // ATRIBUTOS -----------------------------------------------
    std::vector<DFA*> listaDeTokens;
    std::vector<std::pair<int, int>> possicaoDosErros;
};

#endif // ANALISADORLEXICO_H
