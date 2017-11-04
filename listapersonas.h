#ifndef LISTAPERSONAS_H
#define LISTAPERSONAS_H
#include <iostream>
#include "persona.h"

//Estructura de los nodos de la lista de personas
struct NodoListaPersona
{
    Persona*dato;
    NodoListaPersona*siguiente=NULL;
    NodoListaPersona*anterior=NULL;

    NodoListaPersona(Persona *persona) {
        this->dato=persona;
    }


    //Para poder comparar 2 PersonaLista por el id de la persona contenida en dato
    bool operator < (const NodoListaPersona& str) const
    {
        return (dato->id < str.dato->id);
    }
    bool operator <= (const NodoListaPersona& str) const
    {
        return (dato->id <= str.dato->id);
    }
    bool operator == (const NodoListaPersona& str) const
    {
        return (dato->id == str.dato->id);
    }
    bool operator > (const NodoListaPersona& str) const
    {
        return (dato->id > str.dato->id);
    }
    bool operator >= (const NodoListaPersona& str) const
    {
        return (dato->id >= str.dato->id);
    }
    int compare (const NodoListaPersona * a, const NodoListaPersona* b)
    {
      if ( *(NodoListaPersona*)a <  *(NodoListaPersona*)b ) return -1;
      if ( *(NodoListaPersona*)a == *(NodoListaPersona*)b ) return 0;
      if ( *(NodoListaPersona*)a >  *(NodoListaPersona*)b ) return 1;
    }
};

struct ListaPersonas
{
    NodoListaPersona * primeraPersona=NULL;
    NodoListaPersona * ultimaPersona=NULL;

    ListaPersonas()
    {
        //primeraPersona = ultimaPersona = NULL;
    }

    //USAR insertarPersona
    void insertarAlInicio(Persona * nuevaPersona)
    {
        NodoListaPersona * nueva = new NodoListaPersona(nuevaPersona);

        if (primeraPersona == NULL)
        {
            primeraPersona = ultimaPersona = nueva;
        }

        else
        {
            primeraPersona->anterior = nueva;
            primeraPersona->anterior->siguiente = primeraPersona;
            primeraPersona = primeraPersona->anterior;
        }
    }

    //USAR insertarPersona
    void insertarAlFinal(Persona * nuevaPersona)
    {
        NodoListaPersona * nueva = new NodoListaPersona(nuevaPersona);

        if (primeraPersona == NULL)
        {
            primeraPersona = ultimaPersona = nueva;
        }

        else
        {
            ultimaPersona->siguiente = nueva;
            ultimaPersona->siguiente->anterior = ultimaPersona;
            ultimaPersona = ultimaPersona->siguiente;
        }
    }

    //D: Función que inserta a una persona de forma ordenada.
    void insertarPersona(Persona * nuevaPersona)
    {
        NodoListaPersona * nueva = new NodoListaPersona(nuevaPersona);

        if (primeraPersona == NULL||primeraPersona->dato->id > nueva->dato->id) //Persona con el ID más pequeño
        {
            insertarAlInicio(nuevaPersona);
        }

        else if (ultimaPersona->dato->id < nueva->dato->id) //Persona con el ID más grande
        {
            insertarAlFinal(nuevaPersona);
        }

        else
        {
            NodoListaPersona * temporal = primeraPersona;
            while (temporal->dato->id < nueva->dato->id)
            {
                temporal = temporal->siguiente;
            }
            temporal->anterior->siguiente = nueva;
            nueva->siguiente = temporal;
            nueva->anterior = temporal->anterior;
            temporal->anterior = nueva;
        }
    }

    void imprimirPersonas()
    {
        NodoListaPersona * temporal = primeraPersona;
        while (temporal != NULL)
        {

            std::cout << "ID: " << temporal->dato->id << " " << "Nombre: " << temporal->dato->nombre.toStdString() << " " << temporal->dato->apellido.toStdString() << std::endl;
            temporal = temporal->siguiente;
        }
    }

    int cantPersonas()
    {
        NodoListaPersona * temporal = primeraPersona;
        int contador = 0;
        while (temporal != NULL)
        {
            contador++;
            temporal = temporal->siguiente;
        }
        return contador;
    }

    /*
     * Esto no se deberia de usar, porque se deberia de usar la busqueda en el mundo.
     */
    NodoListaPersona * buscarPersona(int id)
    {
        if (primeraPersona != NULL)
        {
            NodoListaPersona * temporal = primeraPersona;

            while (temporal != NULL)
            {
                if (temporal->dato->id == id)
                    return temporal;

                temporal = temporal->siguiente;
            }
            return NULL;
        }

        else
            return NULL;
    }

};


#endif // LISTAPERSONAS_H
