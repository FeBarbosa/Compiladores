#include "posFix.h"


// CONSTRUTOR -------------------------------------------------------------------
PosFix::PosFix(string s):inFix(s), posFix(""){}

// Verifica se um caracter é um operador ----------------------------------------
bool PosFix::operador(char c)
{
    if(c == '*' || c == '+' || c == '.')
        return true;

    return false;
}

// Verifica a precedência entre dois operadores ---------------------------------
bool PosFix::preced(char op1, char op2)
{
    if(op1 == op2)      //Mesma precedência
        return true;

    if(op1 != '+' && op2 != '+')
    {
        if(op1 == '*') //op1 tem maior precedência
            return true;
        else           //op2 tem maior precedência
            return false;
    }

    if(op1 != '+')     //op1 tem maior precedência
        return true;

    return false;      //op2 tem maior precedência
}

// Converte uma expressão inFixa para posFixa ----------------------------------
/**
    Retornos:
        * -1: fechamento de parênteses sem abertura
        *  0: abertura de parênteses sem fechamento
        *  1: operador sem operando
        *  2: expressão válida
**/
int PosFix::infPos()
{
    int aux = 0;    // Controle para concatenação implícita
    string pilha = ""; // inicializa a pilha com string vazia
    char op; // auxiliar para
    //int parent = 0; // auxiliar para o controle de parentes

    for(int i = 0; i < (int)this->inFix.length(); i++)
    {

        if(operador(this->inFix[i]) || (aux && !operador(this->inFix[i]) && this->inFix[i] != ')')) // OPERADOR ----------------------------------------------
        {
            if(aux && !operador(this->inFix[i])) // concatenação implícita
            {
                op = '.';
                i--;
                aux = 0;
            }
            else
                op = this->inFix[i];

            while(!pilha.empty() && pilha.back() != '(' && preced(pilha.back(), op))
            {
                this->posFix.push_back(pilha.back());
                pilha.pop_back();
            }

            pilha.push_back(op); // empilha operador atual

            aux = (op == '*' ? 1 : 0); // possibilidade de concatenção implícita depois de fecho de kleene

        } //-----------------------------------------------------------------------------------
        else if(inFix[i] == '(') // ABERTURA DE PARÊNTESE
        {
                pilha.push_back(inFix[i]);
        }
        else if(inFix[i] == ')') //  FECHAMENTO DE PARÊNTESE
        {
            while(pilha.back() != '(' && !pilha.empty()) // Retira da pilha e coloca na posFix
            {
                this->posFix.push_back(pilha.back());
                pilha.pop_back();
            }
            if(pilha.empty())   //Fechamento de parênteses sem abertura
                return -1;

            pilha.pop_back();
            aux = 1;
        }
        else // OPERANDO ----------------------------------------------------------------------
        {
            this->posFix.push_back(inFix[i]); //insere o operadando atual
            aux = 1; // indica que o último elemento da posFix é um operando
        }
    }

    while(!pilha.empty())
    {
        if(pilha.back() == '(') // Abertura de parênteses sem fechamento
            return 0;

        this->posFix.push_back(pilha.back());
        pilha.pop_back();
    }

    return 2;
}

// Verifica se a expressão pós-fixa é válida -----------------------------------
bool PosFix::verExprePos()
{
    string pilha = ""; //pilha de operandos

    for(int i = 0; i < (int)this->posFix.length(); i++)
    {
        if(!operador(this->posFix[i])) // Se não for um operador empilha
            pilha.push_back(this->posFix[i]);
        else
        {                              // Trata-se de um operador
            if(!pilha.empty())              // Verifica se existe pelo menos um operando
            {
                if(this->posFix[i] == '*')  // Trata-se do operador unário fecho de kleene
                    continue;
                else                        // Trata-se de um operador binário
                {
                    pilha.pop_back();       // Desempilha o operando do topo
                    if(!pilha.empty())      // Verifica se existe o segundo operando necessário
                        continue;
                    else
                        return false;

                }
            }
            else
                return false;
        }
    }

    if(pilha.empty()) //Se a pilha estiver vazia, houve erro
       return false;

    pilha.pop_back();

    if(!pilha.empty()) //Se houver mais de um elemento na pilha, houve erro
        return false;

    return true;
}
