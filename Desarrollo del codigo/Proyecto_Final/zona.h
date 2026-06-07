#ifndef ZONA_H
#define ZONA_H

#include "vector2d.h"
#include "fisica.h"

#include <QGraphicsScene>
#include <QRectF>
#include <memory>

class PiedraCurling;

class Zona
{
public:
    Zona(Vector2D posicion, int ancho, int alto, float friccion);
    virtual ~Zona();

    bool contiene(float px, float py) const;
    virtual void aplicarEfecto(PiedraCurling &piedra) const;
    virtual void dibujar(QGraphicsScene *scene) const = 0;

protected:
    Vector2D pos;
    int ancho;
    int alto;
    float friccion;
    std::unique_ptr<Fisica> fisica;
};

class HieloNormal : public Zona
{
public:
    HieloNormal(Vector2D posicion, int ancho, int alto);
    void dibujar(QGraphicsScene *scene) const override;
};

class HieloResbaladizo : public Zona
{
public:
    HieloResbaladizo(Vector2D posicion, int ancho, int alto);
    void aplicarEfecto(PiedraCurling &piedra) const override;
    void dibujar(QGraphicsScene *scene) const override;
};

class NieveEspesa : public Zona
{
public:
    NieveEspesa(Vector2D posicion, int ancho, int alto);
    void aplicarEfecto(PiedraCurling &piedra) const override;
    void dibujar(QGraphicsScene *scene) const override;
};

class ZonaMagica : public Zona
{
public:
    ZonaMagica(Vector2D posicion, int ancho, int alto);
    void aplicarEfecto(PiedraCurling &piedra) const override;
    void dibujar(QGraphicsScene *scene) const override;
};

#endif
