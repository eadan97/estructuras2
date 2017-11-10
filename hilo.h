#ifndef HILO_H
#define HILO_H

#include <QThread>
#include <QObject>

class Hilo : public QThread
{
    Q_OBJECT
public:
    Hilo(QObject *parent = nullptr);
    int segundos;
    void run();
    bool pausa;

signals:
    void aleatorioDeSalvacion(int);

public slots:
};

#endif // HILO_H
