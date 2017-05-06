#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H
#include <QMessageBox>
#include "estado.h"
#include "expreregular.h"
#include "nfa.h"
#include "dfa.h"

class AnalisadorLexico
{
public:

    // CONSTRUTOR ----------------------------------------------
    AnalisadorLexico();

    // METODOS -------------------------------------------------
    void calcularPadrao(std::string, std::string);

    // ATRIBUTOS -----------------------------------------------
    std::vector<DFA*> listaDeTokens;
};

#endif // ANALISADORLEXICO_H
