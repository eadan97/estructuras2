#ifndef HILO_H
#define HILO_H

#include <QThread>
#include <QObject>

class Hilo : public QThread
{
    Q_OBJECT
public:
    Hilo(int segundos , QObject *parent = nullptr);
    void run();
    bool pausa;
    int misSegundos;

signals:
    void aleatorioDeSalvacion(int);

public slots:
};

#endif // HILO_H
