#ifndef SIMBOLO_H
#define SIMBOLO_H

#include <type_traits>
#include <string>
#include <unordered_map>

namespace ll
{

    struct simbolo: public std::string
    {
        // CONSTRUTORES -----------------------------------------------------------------
        simbolo() {}
        simbolo(const simbolo& s): std::string(s), terminal(s.terminal){}
        simbolo(const std::string& s): std::string(s){}
        simbolo(bool terminal, const std::string& s): std::string(s), terminal(terminal){}

        // VARIÁVEIS --------------------------------------------------------------------
        bool terminal;
    };

}


namespace std
{
    template <>
    struct hash<ll::simbolo> : hash<string> {};
}

#endif // SIMBOLO_H
