#include "gestorpersistencia.h"

#include "juego.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

bool GestorPersistencia::guardar(const QString &archivo, const Juego &juego) const
{
    QJsonObject obj;
    obj["nivelActual"] = juego.getNivelActual();
    obj["puntuacionJugador"] = juego.getPuntuacionJugador();
    obj["puntuacionOponente"] = juego.getPuntuacionOponente();
    obj["lanzamientosRestantes"] = juego.getLanzamientosRestantes();

    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(QJsonDocument(obj).toJson());
    return true;
}

bool GestorPersistencia::cargar(const QString &archivo, Juego &juego) const
{
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        return false;
    }

    const QJsonObject obj = doc.object();
    juego.setEstado(obj["nivelActual"].toInt(1),
                    obj["puntuacionJugador"].toInt(0),
                    obj["puntuacionOponente"].toInt(0),
                    obj["lanzamientosRestantes"].toInt(3));
    return true;
}
