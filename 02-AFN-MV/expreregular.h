#ifndef EXPREREGULAR_H
#define EXPREREGULAR_H

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

class ExpreRegular
{
public:

    //ATRIBUTOS------------------------------------------------------------------------------------
    string inFix;
    string posFix;

    //MÉTODOS--------------------------------------------------------------------------------------
    ExpreRegular(string);                     /** CONSTRUTOR */
    int infParaPos();                   /** Converte uma expressão na fora infixa para posfixa */
    bool verificarExpressaoPosfixa();   /** Verifica se uma expressão posfixa é válida */

private:
    bool precedencia(char, char);       /** Verifica a precedencia entre 2 operadores */
    bool operador(char);                /** Verifica se um caracter é um operador */

};

#endif // EXPREREGULAR_H
