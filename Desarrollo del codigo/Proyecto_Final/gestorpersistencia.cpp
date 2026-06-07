#include "gestorpersistencia.h"

#include "juego.h"

#include <QDataStream>
#include <QFile>
#include <stdexcept>

GestorPersistencia::GestorPersistencia()
{
}

GestorPersistencia &GestorPersistencia::instancia()
{
    static GestorPersistencia gestor;
    return gestor;
}

bool GestorPersistencia::guardar(const QString &archivo, const Juego &juego) const
{
    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar la partida");
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_12);
    out << juego.getNivelActual()
        << juego.getPuntuacionJugador()
        << juego.getPuntuacionOponente()
        << juego.getLanzamientosRestantes()
        << juego.getTiempoRestanteNivel2();
    return true;
}

bool GestorPersistencia::cargar(const QString &archivo, Juego &juego) const
{
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("No existe una partida guardada para cargar");
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_12);

    int nivel = 1;
    int jugador = 0;
    int oponente = 0;
    int lanzamientos = 5;
    float tiempoRestante = 90.0f;
    in >> nivel >> jugador >> oponente >> lanzamientos >> tiempoRestante;

    if (in.status() != QDataStream::Ok) {
        throw std::runtime_error("El archivo de partida esta corrupto");
    }
    if (nivel < 1 || nivel > 2) {
        throw std::out_of_range("Nivel invalido en el archivo de partida");
    }
    if (lanzamientos < 0 || lanzamientos > 20) {
        throw std::out_of_range("Cantidad de lanzamientos invalida");
    }

    juego.setEstado(nivel, jugador, oponente, lanzamientos, tiempoRestante);
    return true;
}
