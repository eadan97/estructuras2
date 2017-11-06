#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QDateTime>
#include <persona.h>
#include <listapersonas.h>
#include <arbolpersonas.h>
#include <avl.h>
#include <thread>
#include <QDebug>
using namespace std;

struct Mundo
{

    ArbolPersonas *arbol= new ArbolPersonas();
    ListaPersonas * listaPersonas = new ListaPersonas;
    QList<int> ids;
    Mundo() {}

    void agregarPersona(Persona* persona){
        listaPersonas->insertarPersona(persona);
        ids+=persona->id;
    }

    void generarPersona();
    void generarPersonas(int cant){
        std::vector<std::thread> ts;
        for(int i=0;i<cant;++i){
            //ts.push_back(std::thread([=]{this->generarPersona();}));
            generarPersona();
        }
        crearArbol();

        //for (auto& th : ts) th.join();
    }
    //retorna la persona o la ultima hoja buscada
    NodoListaPersona* encontrarPersonaEnArbol(NodoArbolPersona *node, int id){
        if(node==NULL)
            return NULL;
        else if(node->dato->dato->id==id)
            return node->dato;
        else if(node->dato->dato->id>id)
            return (node->derecho==NULL)?node->dato : encontrarPersonaEnArbol(node->derecho,id);
        else if(node->dato->dato->id<id)
            return (node->izquierdo==NULL)?node->dato : encontrarPersonaEnArbol(node->izquierdo,id);
    }

    NodoListaPersona* encontrarPersona(int id){
        NodoListaPersona *aux=encontrarPersonaEnArbol(arbol->raiz,id);
        if(aux==NULL||aux->dato==NULL)
            aux = listaPersonas->primeraPersona;

        if (aux->dato->id == id)
            return aux;

        if(aux->dato->id<id){
            while (aux != NULL)
            {
                if (aux->dato->id == id)
                    return aux;

                aux = aux->siguiente;
            }
            return NULL;
        }

        else if(aux->dato->id>id){
            while (aux != NULL)
            {
                if (aux->dato->id == id)
                    return aux;

                aux = aux->anterior;
            }
            return NULL;
        }

    }

    void crearArbol(){
        arbol=NULL;
        arbol=new ArbolPersonas();//hacer arbol nuevo
        QList<int> idsEnArbol;//ids que estan en el arbol
        int cantPersonasAlArbol=listaPersonas->cantPersonas()/100;//1%

        /*if(cantPersonasAlArbol==0)
            cantPersonasAlArbol+=1;*/
        bool hayArbol=false;
        do{ //Si no se ha generado el arbol y si no se ha llegado a la cantidad deseada
            //srand(time(NULL));
            int sub=rand()% ids.size();
            int id=ids[sub];//id a seleccionar

            NodoListaPersona*persona=encontrarPersona(id);


            if(idsEnArbol.indexOf(id)==-1){//si no esta en el arbol
                arbol->listaDelArbol+=persona;//agregarlo al arbol
                idsEnArbol+=id;
                cantPersonasAlArbol-=1;
            }
            hayArbol=arbol->generarArbol();
        }while(cantPersonasAlArbol>0||!(hayArbol));

    }

    void sumarPecadosANietos(QVector<Persona*> hijos)
    {
        for (int i = 0 ; i < hijos.size() ; i++)
        {
            sumarPecadosAHijos(hijos.at(i));
        }
    }

    void sumarPecadosAHijos(Persona * persona)
    {

        for (int i = 0; i < persona->hijos.size() ; i++)
        {
            Persona * hijoActual = persona->hijos.at(i);

            for (int j = 0 ; j < 7 ; j++)
            {
                hijoActual->pecados[j] += persona->pecados[j] / 2;
            }

        }

    }

    void sumarPecadosAPersona(Persona * persona)
    {
        int aleatorio;
        //srand (time(NULL));
        for (int i = 0; i < 7 ; i++)
        {
            aleatorio = rand() % 101;
            persona->pecados[i] += aleatorio;

        }
        sumarPecadosAHijos(persona);
        sumarPecadosANietos(persona->hijos);
    }

    //D: Función que recorre la lista de humanos y le suma a sus pecados
    //E: Ninguna
    //S: Ninguna
    //R: Ninguna
    void sumarPecadosAMundo()
    {
        NodoListaPersona * temporal = listaPersonas->primeraPersona;
        while (temporal != NULL)
        {
            sumarPecadosAPersona(temporal->dato);
            temporal = temporal->siguiente;
        }
    }

    void resetearPecados(Persona * persona)
    {
        for (int i = 0 ; i < 7 ; i++)
        {
            persona->pecados[i] = 0;
        }
    }

    //D: Función que retorna una QList con punteros a persona del país ingresado
    QList<Persona *> personasDePais(QString pais)
    {
        QList<Persona *> personas;
        NodoListaPersona * temporal = listaPersonas->primeraPersona;
        while (temporal != NULL)
        {
            if (temporal->dato->pais.compare(pais) == 0)
                personas.append(temporal->dato);

            temporal = temporal->siguiente;
        }
        return personas;
    }

    //D: Dada una QList de personas, los ingresa en una lista doblemente enlazada y los ordena en orden descendente de acuerdo a sus pecados
    ListaPersonas * ordenarPecadoresDePais(QList<Persona *> personas)
    {
        ListaPersonas * pecadoresOrdenados;
        for (int i = 0 ; i < personas.size() ; i++)
        {
            pecadoresOrdenados->insertarPorPecados(personas[i]);
        }
        return pecadoresOrdenados;
    }


    //D: Función que retorna una QList con los punteros al 25% más pecador de un país
    //E: Un país (QString)
    //S: Una QList con los punteros al 25% más pecador de un país
    //R: Que el país exista
    QList<Persona *> * masPecadoresDePais(QString pais)
    {
        QList <Persona *> * masPecadores;
        int cantPersonasPais = personasDePais(pais).size();
        int veintiCincoPorCiento = cantPersonasPais * 0.25; //asumiendo que ya está redondeado
        ListaPersonas * pecadores = ordenarPecadoresDePais(personasDePais(pais));
        for (int i = 0; i < veintiCincoPorCiento ; i++)
        {
            masPecadores->append(pecadores->primeraPersona->dato);
            pecadores->borrarAlInicio();
        }
        return masPecadores;
    }

};

struct NodoID
{
    int id;
    NodoID * siguiente;
    NodoID * anterior;

    NodoID(int id)
    {
        this->id = id;
        siguiente = anterior = NULL;
    }
};

struct ListaIDS
{
    NodoID * primerID;
    NodoID * ultimoID;

    ListaIDS()
    {
        primerID = ultimoID = NULL;
    }

    void insertarAlInicio(int idNuevo)
    {
        NodoID * nuevo = new NodoID(idNuevo);

        if (primerID == NULL)
        {
            primerID = ultimoID = nuevo;
        }

        else
        {
            primerID->anterior = nuevo;
            primerID->anterior->siguiente = primerID;
            primerID = primerID->anterior;
        }
    }

    void insertarAlFinal(int idNuevo)
    {
        NodoID * nuevo = new NodoID(idNuevo);

        if (primerID == NULL)
        {
            primerID = ultimoID = nuevo;
        }

        else
        {
            ultimoID->siguiente = nuevo;
            ultimoID->siguiente->anterior = ultimoID;
            ultimoID = ultimoID->siguiente;
        }
    }

    void insertarID(int idNuevo)
    {
        if (!yaExiste(idNuevo))
        {
            NodoID * nuevo = new NodoID(idNuevo);

            if (primerID->id > idNuevo)
            {
                insertarAlInicio(idNuevo);
            }

            else if (ultimoID->id < idNuevo)
            {
                insertarAlFinal(idNuevo);
            }

            else
            {
                NodoID * temporal = primerID;
                while(temporal->id < idNuevo)
                {
                    temporal = temporal->siguiente;
                }
                temporal->anterior->siguiente = nuevo;
                nuevo->siguiente = temporal;
                nuevo->anterior = temporal->anterior;
                temporal->anterior = nuevo;
            }
        }

    }

    bool yaExiste(int id)
    {
        if (primerID != NULL)
        {
            NodoID * temporal = primerID;
            while (temporal != NULL)
            {
                if (temporal->id == id)
                    return true;

                temporal = temporal->siguiente;
            }
            return false;
        }

        else
            return false;
    }
};

struct Infierno
{
    ListaPersonas * listaPersonas;
    AVLtree<Persona*> * arbolInfierno = new AVLtree<Persona*>;


};


















#endif // ESTRUCTURAS_H
