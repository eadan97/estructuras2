#include "hilo.h"

Hilo::Hilo(QObject *parent)
    : QThread(parent)
{

}

void Hilo::run()
{
    while(true){
    int aleatorio = 0;
    srand (time(NULL));

    if (pausa)
    {
        this->sleep(1);
    }

    while (!pausa)
    {
        aleatorio = rand() % 10000000;
        emit aleatorioDeSalvacion(aleatorio);

        this->sleep(segundos);
    }}
}
