#ifndef HILO_H
#define HILO_H

#include <QThread>
#include <QObject>

class Hilo : public QThread
{
    Q_OBJECT
public:
    Hilo(int segundos , QObject *parent = nullptr);
    void run(){    int aleatorio = 0;
                   srand (time(NULL));

                   if (pausa)
                   {
                       this->sleep(1);
                   }

                   while (!pausa)
                   {
                       aleatorio = rand() % 10000000;
                       emit aleatorioDeSalvacion(aleatorio);

                       this->sleep(misSegundos);
                   }
              }
    bool pausa;
    int misSegundos;

signals:
    void aleatorioDeSalvacion(int);

public slots:
};

#endif // HILO_H
