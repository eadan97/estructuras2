#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QDateTime>
#include<avl.h>
using namespace std;
struct Persona
{
    int id;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    QString correo;
    QDateTime nacimiento;
    int pecados[7];
    QVector <Persona*> hijos;
    int cantHijos;


    Persona(int id, QString nombre, QString apellido, QString pais, QString creencia, QString profesion, QString correo) {
        this->id=id;
        this->nombre=nombre;
        this->apellido=apellido;
        this->pais=pais;
        this->creencia=creencia;
        this->profesion=profesion;
        this->nacimiento=QDateTime::currentDateTime();
        this->correo=correo;
    }

    bool esDescendiente(Persona*aBuscar){
        if(esHijo(aBuscar)||esNieto(aBuscar))
            return true;
        return false;
    }

    bool esHijo(Persona*aBuscar){
        for (int i=0; i<hijos.size(); ++i ) {
            if(aBuscar==hijos[i])
                return true;
        }
        return false;
    }

    bool esNieto(Persona*aBuscar){
        for (int i=0; i<hijos.size(); ++i ) {
            if(hijos[i]->esHijo(aBuscar))
                return true;
        }
        return false;
    }

};

struct NodoPersona
{
    Persona*dato;
    NodoPersona*siguiente;
    NodoPersona*anterior;
    NodoPersona(Persona *persona) {
        this->dato=persona;
    }

    //Para poder comparar 2 PersonaLista por el id de la persona contenida en dato
    bool operator < (const NodoPersona& str) const
    {
        return (dato->id < str.dato->id);
    }
    bool operator <= (const NodoPersona& str) const
    {
        return (dato->id <= str.dato->id);
    }
    bool operator == (const NodoPersona& str) const
    {
        return (dato->id == str.dato->id);
    }
    bool operator > (const NodoPersona& str) const
    {
        return (dato->id > str.dato->id);
    }
    bool operator >= (const NodoPersona& str) const
    {
        return (dato->id >= str.dato->id);
    }
};

struct ListaPersonas
{
    NodoPersona * primeraPersona;
    NodoPersona * ultimaPersona;

    ListaPersonas()
    {
        primeraPersona = ultimaPersona = NULL;
    }

    void insertarAlInicio(Persona * nuevaPersona)
    {
        NodoPersona * nueva = new NodoPersona(nuevaPersona);

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

    void insertarAlFinal(Persona * nuevaPersona)
    {
        NodoPersona * nueva = new NodoPersona(nuevaPersona);

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
        NodoPersona * nueva = new NodoPersona(nuevaPersona);

        if (primeraPersona > nueva || primeraPersona == NULL) //Persona con el ID más pequeño
        {
            insertarAlInicio(nuevaPersona);
        }

        else if (ultimaPersona < nueva) //Persona con el ID más grande
        {
            insertarAlFinal(nuevaPersona);
        }

        else
        {
            NodoPersona * temporal = primeraPersona;
            while (temporal < nueva)
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
        NodoPersona * temporal = primeraPersona;
        while (temporal != NULL)
        {
            std::cout << "ID: " << temporal->dato->id << " " << "Nombre: " << temporal->dato->nombre.toStdString() << " " << temporal->dato->apellido.toStdString() << endl;
            temporal = temporal->siguiente;
        }
    }

    int cantPersonas()
    {
        NodoPersona * temporal = primeraPersona;
        int contador = 0;
        while (temporal != NULL)
        {
            contador++;
            temporal = temporal->siguiente;
        }
        return contador;
    }

    NodoPersona * buscarPersona(int id)
    {
        if (primeraPersona != NULL)
        {
            NodoPersona * temporal = primeraPersona;

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

struct Mundo
{

    AVLtree<NodoPersona*> arbol;
    ListaPersonas * listaPersonas;
    Mundo() {}

    void generarPersonas(int cant);
    //retorna la persona o la ultima hoja buscada
    NodoPersona* encontrarPersonaEnArbol(AVLnode<NodoPersona*> *node, int id){
        if(node==NULL)
            return NULL;
        else if(node->key->dato->id==id)
            return node->key;
        else if(node->key->dato->id>id)
            return (node->right==NULL)?node->key : encontrarPersonaEnArbol(node->right,id);
        else if(node->key->dato->id<id)
            return (node->left==NULL)?node->key : encontrarPersonaEnArbol(node->left,id);
    }

    Persona* encontrarPersona(int id){
        PersonaLista *aux=encontrarPersonaEnArbol(arbol.root,id);

        if(aux->dato->id>id)
            while(aux->dato->id>id)
                aux=aux->anterior;
        else if(aux->dato->id<id)
            while(aux->dato->id<id)
                aux=aux->siguiente;

        if(aux->dato->id==id)
            return aux->dato;
        else
            return NULL;

    }



};



#endif // ESTRUCTURAS_H
