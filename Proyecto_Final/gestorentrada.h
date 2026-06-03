#ifndef GESTORENTRADA_H
#define GESTORENTRADA_H

#include <QSet>

class GestorEntrada
{
public:
    void presionar(int tecla);
    void soltar(int tecla);
    bool teclaPresionada(int tecla) const;
    bool flechaArriba() const;
    bool flechaAbajo() const;
    bool flechaIzquierda() const;
    bool flechaDerecha() const;
    bool espacio() const;
    char leerTecla() const;

private:
    QSet<int> teclas;
};

#endif
