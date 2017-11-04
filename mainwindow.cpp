#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <time.h>
#include <thread>

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

    ui->tblPecadosFamilia->setColumnWidth(0, 40);
    ui->tblPecadosFamilia->setColumnWidth(1, 70);
    ui->tblPecadosFamilia->setColumnWidth(2, 70);
    ui->tblPecadosFamilia->setColumnWidth(3, 50);
    ui->tblPecadosFamilia->setColumnWidth(4, 70);
    ui->tblPecadosFamilia->setColumnWidth(5, 70);
    ui->tblPecadosFamilia->setColumnWidth(6, 40);
    ui->tblPecadosFamilia->setColumnWidth(7, 70);
    ui->tblPecadosFamilia->setColumnWidth(8, 70);


    startDialog=new StartDialog(this);
    mundo=new Mundo();
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

void MainWindow::afterLoad(){


    //startDialog->exec();
    QString qNombres="C:/Users/eadan/nombres.txt";
    QString qApellidos="C:/Users/eadan/apellidos.txt";
    QString qPaises="C:/Users/eadan/paises.txt";
    QString qCreencias="C:/Users/eadan/creencias.txt";
    QString qProfesiones="C:/Users/eadan/profesiones.txt";
    procesarArchivo(nombres,qNombres);
    procesarArchivo(apellidos,qApellidos);
    procesarArchivo(paises,qPaises);
    procesarArchivo(creencias,qCreencias);
    procesarArchivo(profesiones,qProfesiones);


    //TODO: hacer esto en hilos, speed is the key.

    //procesarArchivo(nombres,startDialog->fileNombres);
    //procesarArchivo(apellidos,startDialog->fileApellidos);
    //procesarArchivo(paises,startDialog->filePaises);
    arreglarPaises();
    //procesarArchivo(creencias,startDialog->fileCreencias);
    //procesarArchivo(profesiones,startDialog->fileProfesiones);

    mundo->generarPersonas(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Mundo::generarPersona(){
    //srand (time(NULL));
    int newId=rand() % 10000000;
    while (ids.indexOf(newId)!=-1) {
        //srand (time(NULL));
        newId=rand() % 10000000;
    }

    //srand (time(NULL));
    QString nombre=nombres[rand()% nombres.size()];

    //srand (time(NULL));
    QString apellido=apellidos[rand()%apellidos.size()];

    //srand (time(NULL));
    QString pais=paises[rand()%paises.size()];

    //srand (time(NULL));
    QString creencia=creencias[rand()%creencias.size()];

    //srand (time(NULL));
    QString profesion=profesiones[rand()%profesiones.size()];

    QString correo=paisCorreo[pais];

    Persona* nueva=new Persona(newId,nombre,apellido,pais,creencia,profesion,correo);



    mundo->agregarPersona(nueva);


    NodoListaPersona*auxPL=mundo->listaPersonas->primeraPersona;
    AVLtree<Persona*>*familia=new AVLtree<Persona*>;
    while (auxPL!=NULL) {
        Persona*auxDato=auxPL->dato;
        if(auxDato!=nueva&&auxDato->apellido==apellido&&auxDato->pais==pais)
            familia->insert(auxDato);
        auxPL=auxPL->siguiente;
    }
    //todo: creo que el arbol de la familia no deberia ser un puntero, y si no, hay que borrar los datos.
    //srand(time(NULL));
    int cantHijos=rand()%9;

    AVLnode<Persona*>*aux=familia->root;

    while (cantHijos>0&&familia->root!=0) {
        int seleccion=0;
        do{
            if (aux==0){
                aux=familia->root;}
            //srand(time(NULL));
            seleccion=rand()%3;
            if (seleccion==0){
               aux=(aux->left==NULL)?aux:aux->left;}
            else if(seleccion==2){
                aux=(aux->right==NULL)?aux:aux->right;}
        }while(seleccion!=1);

        if(!(aux->key->esDescendiente(nueva)||aux->key==nueva))
            nueva->hijos.append(aux->key);
        familia->deleteKey(aux->key);
        cantHijos-=1;
        aux=familia->root;
    }

}


void MainWindow::on_btnGenerarPersonas_clicked()
{
    int cantidad = ui->spnGenerarPersonas->value();
    ui->spnGenerarPersonas->setValue(0);
    mundo->generarPersonas(cantidad);

}

void MainWindow::on_btnAgregarPecados_clicked()
{
    mundo->sumarPecadosAMundo();

}

void MainWindow::on_btnPecadosFamilia_clicked()
{
    int id = ui->txtPecadosFamiliaID->text().toInt();
}
