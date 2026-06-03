#ifndef GESTORPERSISTENCIA_H
#define GESTORPERSISTENCIA_H

#include <QString>

class Juego;

class GestorPersistencia
{
public:
    bool guardar(const QString &archivo, const Juego &juego) const;
    bool cargar(const QString &archivo, Juego &juego) const;
};

#endif
