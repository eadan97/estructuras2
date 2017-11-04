#ifndef PERSONA_H
#define PERSONA_H
//Estructura de Persona
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
    //int cantHijos;

    //Constructor
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


    //D: Busca la persona pasada por parametro para ver si es descendiente de this
    //E: Puntero a la persona a buscar
    //S: Si es descendiente o no
    bool esDescendiente(Persona*aBuscar){
        if(esHijo(aBuscar)||esNieto(aBuscar))
            return true;
        return false;
    }

    //Ver esDescendiente
    bool esHijo(Persona*aBuscar){
        for (int i=0; i<hijos.size(); ++i ) {
            if(aBuscar==hijos[i])
                return true;
        }
        return false;
    }

    //Ver esDescendiente
    bool esNieto(Persona*aBuscar){
        for (int i=0; i<hijos.size(); ++i ) {
            if(hijos[i]->esHijo(aBuscar))
                return true;
        }
        return false;
    }



    bool operator < (const Persona& str) const
    {
        return (id < str.id);
    }
    bool operator <= (const Persona& str) const
    {
        return (id <= str.id);
    }
    bool operator == (const Persona& str) const
    {
        return (id == str.id);
    }
    bool operator > (const Persona& str) const
    {
        return (id > str.id);
    }
    bool operator >= (const Persona& str) const
    {
        return (id >= str.id);
    }
};

#endif // PERSONA_H
