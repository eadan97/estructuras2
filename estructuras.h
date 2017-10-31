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
    int pecados[7]={0,0,0,0,0,0,0};
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
    int compare (const NodoPersona * a, const NodoPersona* b)
    {
      if ( *(NodoPersona*)a <  *(NodoPersona*)b ) return -1;
      if ( *(NodoPersona*)a == *(NodoPersona*)b ) return 0;
      if ( *(NodoPersona*)a >  *(NodoPersona*)b ) return 1;
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

struct PersonaArbolNodo
{
    PersonaLista*dato;
    PersonaArbolNodo*izquierdo;
    PersonaArbolNodo*derecho;
    PersonaArbolNodo(PersonaLista *personaLista) {
        this->dato=personaLista;
    }
};

struct PersonaArbol
{
    PersonaArbolNodo*raiz;
    QVector<PersonaLista*> listaDelArbol;

    void generarArbol(){
        double logaritmo= log(listaDelArbol.size()+1)/log(2);//Logaritmo en base 2 de x+1
        double intpart;
        if( modf( logaritmo, &intpart) == 0){//Si el logaritmo dio un numero entero
            qSort(listaDelArbol);
            int medio = (listaDelArbol.size()-1)/2;
            raiz=new PersonaArbolNodo(listaDelArbol[medio]);
            agregarAlArbol(raiz,medio, medio);
        }
    }
    void agregarAlArbol(PersonaArbolNodo*arbol, int dif, int pos){
        dif=dif/2;
        if(dif==0)
            return;
        arbol->izquierdo=new PersonaArbolNodo(listaDelArbol[pos-dif]);
        arbol->derecho=new PersonaArbolNodo(listaDelArbol[pos+dif]);
        agregarAlArbol(arbol->izquierdo,dif,pos-dif);
        agregarAlArbol(arbol->derecho,dif,pos+dif);

    }
    PersonaArbol() {}
};

struct Mundo
{

    AVLtree<NodoPersona*> arbol;
    ListaPersonas * listaPersonas;
    Mundo() {}

    void generarPersonas(int cant);
    //retorna la persona o la ultima hoja buscada
    PersonaLista* encontrarPersonaEnArbol(PersonaArbolNodo *node, int id){
        if(node==NULL)
            return NULL;
        else if(node->dato->dato->id==id)
            return node->key;
        else if(node->dato->dato->id>id)
            return (node->derecho==NULL)?node->dato : encontrarPersonaEnArbol(node->derecho,id);
        else if(node->key->dato->id<id)
            return (node->izquierdo==NULL)?node->dato : encontrarPersonaEnArbol(node->izquierdo,id);
    }

    Persona* encontrarPersona(int id){
        PersonaLista *aux=encontrarPersonaEnArbol(arbol.raiz,id);

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

    void crearArbol(){

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
                hijoActual->pecados[j] = persona->pecados[j] / 2;
            }

        }

    }

    void sumarPecadosAPersona(Persona * persona)
    {
        int aleatorio;
        srand (time(NULL));
        for (int i = 0; i < 7 ; i++)
        {
            aleatorio = rand() % 100;
            persona->pecados[i] = aleatorio;

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
        NodoPersona * temporal = listaPersonas->primeraPersona;
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




#endif // ESTRUCTURAS_H
