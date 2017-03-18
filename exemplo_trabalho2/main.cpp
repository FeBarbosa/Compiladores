#include <iostream>
#include "posFix.h"
#include "nfa.h"
#include "dfa.h"

using namespace std;

int main()
{
    NFA nautomato = NFA("01+*0+");

    nautomato.criarNFA();

    nautomato.show();

    DFA dautomato = DFA(nautomato.nfa, nautomato.Alfabeto);

    dautomato.show();

    return 0;
}
