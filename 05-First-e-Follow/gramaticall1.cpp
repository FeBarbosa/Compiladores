#include "gramaticall1.h"

namespace ll
{
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
            simbolo aux(true ,terminais[i]);

            std::cout << aux << aux.terminal << std::endl;
        }

    }

}
