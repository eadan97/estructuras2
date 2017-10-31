#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <time.h>

QStringList nombres;
QStringList apellidos;
QStringList paises;
QHash<QString, QString> paisCorreo;
QStringList creencias;
QStringList profesiones;

Mundo* mundo;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Persona*p=new Persona(1,"a","a","a","a","a","a");
    //PersonaLista*pl=new PersonaLista(p);

    ui->setupUi(this);
    startDialog=new StartDialog(this);
}


void MainWindow::procesarArchivo(QStringList &list, QString fileDir){
    QFile file(fileDir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        list+=line;
    }

}

void MainWindow::arreglarPaises(){
    for(int i=0; i<paises.size(); ++i){
        QStringList pais=paises.at(i).split(',');
        paisCorreo[pais.at(0)]=pais.at(1);
        paises[i]=pais[0];
    }

}

void MainWindow::showStartDialog(){
    startDialog->exec();
    //TODO: hacer esto en hilos, speed is the key.
    procesarArchivo(nombres,startDialog->fileNombres);
    procesarArchivo(apellidos,startDialog->fileApellidos);
    procesarArchivo(paises,startDialog->filePaises);
    arreglarPaises();
    procesarArchivo(creencias,startDialog->fileCreencias);
    procesarArchivo(profesiones,startDialog->fileProfesiones);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void Mundo::generarPersonas(int cant){
    for(int i=0;i<cant;++i){
        srand (time(NULL));
        int newId=rand() % 10000000;
        while (encontrarPersona(newId)!=NULL) {
            srand (time(NULL));
            newId=rand() % 10000000;
        }

        srand (time(NULL));
        QString nombre=nombres[rand()% nombres.size()];

        srand (time(NULL));
        QString apellido=apellidos[rand()%apellidos.size()];

        srand (time(NULL));
        QString pais=paises[rand()%paises.size()];

        srand (time(NULL));
        QString creencia=creencias[rand()%creencias.size()];

        srand (time(NULL));
        QString profesion=profesiones[rand()%profesiones.size()];

        QString correo=paisCorreo[pais];

        Persona* nueva=new Persona(newId,nombre,apellido,pais,creencia,profesion,correo);

        NodoPersona*auxPL=mundo->listaPersonas->primeraPersona;
        AVLtree<Persona*>*familia=new AVLtree<Persona*>;
        while (auxPL!=NULL) {
            Persona*auxDato=auxPL->dato;
            if(auxDato->apellido==apellido&&auxDato->pais==pais)
                familia->insert(auxDato);
            auxPL=auxPL->siguiente;
        }
        //todo: creo que el arbol de la familia no deberia ser un puntero, y si no, hay que borrar los datos.
        //hacer random para decidir random (0 iz, 1 este, 2 derecha)
        srand(time(NULL));
        int cantHijos=rand()%9;
        AVLnode<Persona*>*aux=familia->root;
        while (cantHijos>0||familia->root==NULL) {
            srand(time(NULL));
            int seleccion=rand()%3;
            while(seleccion!=1){
                if (seleccion==0)
                    aux=aux->left;
                else if(seleccion==2)
                    aux=aux->right;
                if (aux==NULL)
                    aux==familia->root;
            }

            if(!(aux->key->esDescendiente(nueva)))
                nueva->hijos.append(aux->key);
            familia->deleteKey(aux->key);
            cantHijos-=1;
        }

        //todo: random para saber la cantidad de hijos, hacer random para decidir random (0 iz, 1 este, 2 derecha), hacer lista para ver si este ya se testeo para ser hijo, hacer funcion para saber si es decendiente en pesona
        
        

    }

}
