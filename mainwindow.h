#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>
#include <estructuras.h>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void afterLoad();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_btnGenerarPersonas_clicked();

    void on_btnAgregarPecados_clicked();

    void on_btnPecadosFamilia_clicked();
    void agregarATablaPecadosFamilia(QTableWidget * tbl, QStringList lista);

private:
    Ui::MainWindow *ui;

    StartDialog* startDialog;

    void procesarArchivo(QStringList&list,QString fileDir);
    void arreglarPaises();

    void refrescarTopsPecadores();
    void pintarMapa();

};

#endif // MAINWINDOW_H
