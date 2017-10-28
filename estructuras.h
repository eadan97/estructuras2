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
    Persona*siguiente;
    Persona*anterior;
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

struct PersonaArbol
{
    PersonaLista*dato;
    Persona*izquierdo;
    Persona*derecho;
    PersonaArbol(PersonaLista *personaLista) {
        this->dato=personaLista;
    }
};
struct Mundo
{

    PersonaArbol*arbolPrimero;
    PersonaLista*listaPrimero;
    Mundo() {}


};



#endif // ESTRUCTURAS_H
