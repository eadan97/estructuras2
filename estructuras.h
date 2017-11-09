#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QDateTime>
#include <persona.h>
#include <listapersonas.h>
#include <arbolpersonas.h>
#include <avl.h>
#include <thread>
#include <QDebug>
#include <heap.h>
using namespace std;

struct Infierno
{
    ListaPersonas * listaPersonas=new ListaPersonas();
    //Heap * heapInfierno = new Heap();
    AVLtree<NodoListaPersona*> * arbol = new AVLtree<NodoListaPersona*>;

    NodoListaPersona*encontrarPersona(int id){
        NodoListaPersona*aux=encontrarPersonaEnArbol(arbol->root, id);

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

    template <class T>
    NodoListaPersona* encontrarPersonaEnArbol(AVLnode<T> *node, int id){
        if(node==NULL)
            return NULL;
        else if(node->key->dato->id==id)
            return node->key;
        else if(node->key->dato->id>id)
            return (node->right==NULL)?node->key : encontrarPersonaEnArbol(node->right,id);
        else if(node->key->dato->id<id)
            return (node->left==NULL)?node->key : encontrarPersonaEnArbol(node->left,id);
    }


    void crearArbol(){
        arbol=NULL;
        arbol=new AVLtree<NodoListaPersona*>;//hacer arbol nuevo
        QList<int> idsEnArbol;//ids que estan en el arbol
        int cantPersonasAlArbol=listaPersonas->cantPersonas();
        cantPersonasAlArbol/=100;//1%

        if(cantPersonasAlArbol==0)
            cantPersonasAlArbol++;


        do{ //Si no se ha generado el arbol y si no se ha llegado a la cantidad deseada
            //srand(time(NULL));
            int id=rand()% 10000000;
            if(idsEnArbol.indexOf(id)==-1){//si no esta en el arbol
                idsEnArbol+=id;
                NodoListaPersona*persona=encontrarPersona(id);
                if(persona!=NULL){
                    arbol->insert(persona);//agregarlo al arbol
                    cantPersonasAlArbol-=1;
                }
            }

        }while(cantPersonasAlArbol>0);

    }

};


struct Mundo
{
    Infierno  * infierno=new Infierno();
    ArbolPersonas *arbol= new ArbolPersonas();
    ListaPersonas * listaPersonas = new ListaPersonas;
    QList<int> ids;
    Mundo() {

    }

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
        for (int i = 0 ; i < hijos.size() ; ++i)
        {
            sumarPecadosAHijos(hijos.at(i));
        }
    }

    void sumarPecadosAHijos(Persona * persona)
    {

        for (int i = 0; i < persona->hijos.size() ; ++i)
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
        for (int i = 0 ; i < personas.size() ; ++i)
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
        ListaPersonas * pecadores = ordenarPecadores(personasDePais(pais));
        for (int i = 0; i < veintiCincoPorCiento ; ++i)
        {
            masPecadores->append(pecadores->primeraPersona->dato);
            pecadores->borrarAlInicio();
        }
        return masPecadores;
    }

    void agregarPecadoresAInfierno(QString pais)
    {
        QList<Persona * > listaParaHeap = personasDePais(pais);

        HeapPecados heap=HeapPecados();

        foreach (Persona*var, listaParaHeap) {
            heap.insert(var);
        }

        int cantidad25=heap.getSize()*0.25;


        if (cantidad25==0)
            return;


        for (int i = 0 ; i < cantidad25+1 ; ++i)
        {
            Persona*aux=heap.remove();
            listaPersonas->borrarPersona(aux->id);
            ids.removeAll(aux->id);
            infierno->listaPersonas->insertarPersona(aux);
            //guardar persona condenada
        }
        infierno->crearArbol();
        crearArbol();
        //TODO: enviar correo
    }
    void agregarAlParaiso(int idAleatorio)
    {
        if (!listaDeSalvados->contains(idAleatorio))
        {
            listaDeSalvados->append(idAleatorio);
            if(listaPersonas->buscarPersona(idAleatorio) != NULL)
            {

            }
        }

        cout << "La persona con el ID: " << idAleatorio << " ya fue salvada" << endl;

    }
    
};



















#endif // ESTRUCTURAS_H
