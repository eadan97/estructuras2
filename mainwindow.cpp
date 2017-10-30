#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

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

        PersonaLista*aux=mundo->listaPrimero;
        AVLtree<Persona*>famila=new AVLtree<Persona*>;
        while (aux!=NULL) {
            Persona*auxDato=aux->dato;
            if(auxDato->apellido==apellido&&auxDato->pais==pais)
                famila.insert(auxDato);
            aux=aux->siguiente;
        }




    }
}
