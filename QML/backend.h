#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class BackEnd : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString fileNombres READ fileNombres WRITE setFileNombres NOTIFY fileNombresChanged)
    //Q_PROPERTY(QString fileApellidos READ fileApellidos WRITE setFileApellidos NOTIFY fileApellidosChanged)
    //Q_PROPERTY(QString fileProfesiones READ fileProfesiones WRITE setfileProfesiones NOTIFY fileProfesionesChanged)
public:
    explicit BackEnd(QObject *parent = nullptr);

    QString fileNombres();

signals:

public slots:


private:
    //QString m_fileNombre;
    //QString m_fileApellidos;
    //QString m_fileProfesiones;
    //QString m_fileCreencias;
    //QString m_filePaises;
};


#endif // BACKEND_H
