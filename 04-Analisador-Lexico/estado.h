#ifndef ESTADO_H
#define ESTADO_H

//-----------------------------------------------------------------
class estado
{
    public:

        // CONSTRUTOR -----------------------------------------------
        estado (int id=-1, bool estadoFinal =false, bool estadoErro = false, bool fecho=false):
            id(id), estadoFinal(estadoFinal), estadoErro(estadoErro),fecho(fecho){}
        //----------------------------------------------------------

        int id;
        bool estadoFinal;
        bool estadoErro;
        bool fecho;
};
//-------------------------------------------------------------------
#endif // ESTADO_H
