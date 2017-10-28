#include "startdialog.h"
#include "ui_startdialog.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

}

StartDialog::~StartDialog()
{
    delete ui;
}

bool StartDialog::allFilesSelected(){
    return !fileNombres.isEmpty()&&
            !fileApellidos.isEmpty()&&
            !filePaises.isEmpty()&&
            !fileCreencias.isEmpty()&&
            !fileProfesiones.isEmpty();
}
void StartDialog::on_buttonBox_accepted()
{
    if(!allFilesSelected())
        return;
    accept();
}

void StartDialog::on_buttonBox_rejected()
{
    exit(EXIT_FAILURE);
}
void StartDialog::findFile(QString &string,QPushButton*button){
    QString file = QFileDialog::getOpenFileName(this, tr("Seleccionar Archivo"), QDir::homePath() , tr("Archivos de texto (*.txt)"));
    string=file;
    button->setText(file);
}
void StartDialog::on_btnNombres_clicked()
{
    findFile(fileNombres, (ui->btnNombres));
}

void StartDialog::on_btnApellidos_clicked()
{
    findFile(fileApellidos, (ui->btnApellidos));
}

void StartDialog::on_btnPaises_clicked()
{
    findFile(filePaises, (ui->btnPaises));
}

void StartDialog::on_btnCreencias_clicked()
{
    findFile(fileCreencias ,(ui->btnCreencias));

}

void StartDialog::on_btnProfesiones_clicked()
{
    findFile(fileProfesiones, (ui->btnProfesiones));

}
