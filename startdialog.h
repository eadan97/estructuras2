#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    QString fileNombres;
    QString fileApellidos;
    QString filePaises;
    QString fileCreencias;
    QString fileProfesiones;


signals:
    /*void fileNombresChanged(QString newFile);
    void fileApellidosChanged(QString newFile);
    void filePaisesChanged(QString newFile);
    void fileCreenciasChanged(QString newFile);
    void fileProfesionesChanged(QString newFile);*/

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_btnNombres_clicked();

    bool allFilesSelected();

    void on_btnApellidos_clicked();

    void on_btnPaises_clicked();

    void on_btnCreencias_clicked();

    void on_btnProfesiones_clicked();

private:
    Ui::StartDialog *ui;
    void findFile(QString &string,QPushButton*button);


};

#endif // STARTDIALOG_H
