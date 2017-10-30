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
    int pecados[7];
    Persona *hijos[];

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
};

/*struct PersonaArbol
{
    PersonaLista*dato;
    Persona*izquierdo;
    Persona*derecho;
    PersonaArbol(PersonaLista *personaLista) {
        this->dato=personaLista;
    }
};*/
struct Mundo
{

    AVLtree<PersonaLista*> arbol;
    PersonaLista*listaPrimero;
    Mundo() {}

    void generarPersonas(int cant);
    //retorna la persona o la ultima hoja buscada
    PersonaLista* encontrarPersonaEnArbol(AVLnode<PersonaLista*> *node, int id){
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
