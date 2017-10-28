#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

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

void MainWindow::showStartDialog(){
    startDialog->exec();
    //TODO: hacer esto en hilos, speed is the key.
    procesarArchivo(nombres,startDialog->fileNombres);
    procesarArchivo(apellidos,startDialog->fileApellidos);
    procesarArchivo(paises,startDialog->filePaises);
    procesarArchivo(creencias,startDialog->fileCreencias);
    procesarArchivo(profesiones,startDialog->fileProfesiones);
}

MainWindow::~MainWindow()
{
    delete ui;
}
