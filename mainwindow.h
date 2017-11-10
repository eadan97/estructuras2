#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>
#include <estructuras.h>
#include <QTableWidget>
#include "hilo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void afterLoad();
    void agregarAlParaisoVentana(int);

public:
    explicit MainWindow(QWidget *parent = 0);
    Hilo * hiloDeAleatorio;

    ~MainWindow();
    void refrescarTopsPecadores();
    void refrescarPersonasEnIniferno();
    void refrescarPersonasEnParaiso();
    void pintarMapa();
    void refrescarListaNoNacidos();
private slots:
    void closeEvent(QCloseEvent *event);
    void on_btnGenerarPersonas_clicked();
    void on_btnAgregarPecados_clicked();
    void on_btnPecadosFamilia_clicked();
    void agregarATable(QTableWidget * tbl, QStringList lista);
    void on_btnCondenarPais_clicked();
    void procesarArchivo(QStringList&list,QString fileDir);
    void arreglarPaises();

    void conectarHilo();

    void on_btnPlay_clicked();

    void on_btnPausa_clicked();

    void on_secSalvacion_valueChanged(int arg1);

    void on_btnConsultaPaisApellido_clicked();

private:
    Ui::MainWindow *ui;
    StartDialog* startDialog;
};

#endif
