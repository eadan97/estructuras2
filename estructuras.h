#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QDateTime>
#include<avl.h>
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
struct PersonaLista
{
    Persona*dato;
    PersonaLista*siguiente;
    PersonaLista*anterior;
    PersonaLista(Persona *persona) {
        this->dato=persona;
    }

    //Para poder comparar 2 PersonaLista por el id de la persona contenida en dato
    bool operator < (const PersonaLista& str) const
    {
        return (dato->id < str.dato->id);
    }
    bool operator <= (const PersonaLista& str) const
    {
        return (dato->id <= str.dato->id);
    }
    bool operator == (const PersonaLista& str) const
    {
        return (dato->id == str.dato->id);
    }
    bool operator > (const PersonaLista& str) const
    {
        return (dato->id > str.dato->id);
    }
    bool operator >= (const PersonaLista& str) const
    {
        return (dato->id >= str.dato->id);
    }
    int compare (const PersonaLista * a, const PersonaLista* b)
    {
      if ( *(PersonaLista*)a <  *(PersonaLista*)b ) return -1;
      if ( *(PersonaLista*)a == *(PersonaLista*)b ) return 0;
      if ( *(PersonaLista*)a >  *(PersonaLista*)b ) return 1;
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

    PersonaArbol arbol;
    PersonaLista*listaPrimero;
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


};



#endif // ESTRUCTURAS_H
