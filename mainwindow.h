#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>
#include <estructuras.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void showStartDialog();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    StartDialog* startDialog;

    void procesarArchivo(QStringList&list,QString fileDir);
    void arreglarPaises();


};

#endif // MAINWINDOW_H
