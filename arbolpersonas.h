#ifndef ARBOLPERSONAS_H
#define ARBOLPERSONAS_H
#include <algorithm>
#include <QList>

struct NodoArbolPersona
{
    NodoListaPersona*dato=NULL;
    NodoArbolPersona*izquierdo=NULL;
    NodoArbolPersona*derecho=NULL;
    NodoArbolPersona(NodoListaPersona *personaLista) {
        this->dato=personaLista;
    }
};

struct ArbolPersonas
{
    NodoArbolPersona*raiz=NULL;
    QList<NodoListaPersona*> listaDelArbol;

    bool generarArbol(){
        this->raiz=NULL;
        if(listaDelArbol.size()!=0){
            double logaritmo= log(listaDelArbol.size()+1)/log(2);//Logaritmo en base 2 de x+1
            double intpart;
            if( modf( logaritmo, &intpart) == 0){//Si el logaritmo dio un numero entero
                std::sort(listaDelArbol.begin(),listaDelArbol.end(), [](NodoListaPersona * a, NodoListaPersona * b){
                    return *a < *b;
                });
                //qSort(listaDelArbol);
                int medio = (listaDelArbol.size()-1)/2;
                raiz=new NodoArbolPersona(listaDelArbol[medio]);
                agregarAlArbol(raiz,(listaDelArbol.size()+1)/2, medio);
                return true;
            }
        }
        return false;
    }
    void agregarAlArbol(NodoArbolPersona*arbol, int dif, int pos){
        dif=dif/2;
        if(dif==0)
            return;
        arbol->izquierdo=new NodoArbolPersona(listaDelArbol[pos-dif]);
        arbol->derecho=new NodoArbolPersona(listaDelArbol[pos+dif]);
        agregarAlArbol(arbol->izquierdo,dif,pos-dif);
        agregarAlArbol(arbol->derecho,dif,pos+dif);

    }
    void eliminarPersona(NodoListaPersona * persona)
    {
        listaDelArbol.removeAll(persona);
        generarArbol();
    }

    ArbolPersonas() {}
};


#endif // ARBOLPERSONAS_H
