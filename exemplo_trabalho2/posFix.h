#ifndef POSFIX_H
#define POSFIX_H
#include <string>

using namespace std;

/**
    * Operadores:
        - fecho de Kleene: '*';
        - Concatenação:'.', ou dois operandos seguidos;
        - União: '+';
       (a precedência é dada de cima para baixo);
    * Palavra Vazia: &

    OBS: o operador de concatenação deve estar explícito na notação pós-fixa.

**/

class PosFix
{

public:
    //Atributos---------------------------
    string inFix;
    string posFix;
    //------------------------------------

    //Métodos-----------------------------
    PosFix(string);              /** Construtor **/
    bool preced(char, char);      /** Verifica a precedência entre dois operadores **/
    bool operador(char);          /** Verifica se um caracter é um operador **/
    int infPos();                 /** Converte uma expressão infixa para pós-fixa **/
    bool verExprePos();           /** Verifica se a expressão pós-fixa é válida**/
};

#endif // POSFIX_H
