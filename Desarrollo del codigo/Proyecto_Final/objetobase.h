#ifndef OBJETOBASE_H
#define OBJETOBASE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>

class ObjetoBase
{
public:
    ObjetoBase(int xInicial = 0, int yInicial = 0, const QString &spriteInicial = QString());
    virtual ~ObjetoBase();

    virtual void actualizar(float dt);
    virtual void dibujar(QGraphicsScene *scene) = 0;

    int getX() const;
    int getY() const;
    bool estaActivo() const;
    void setActivo(bool valor);
    void setPosicion(int nuevaX, int nuevaY);
    void limpiarGrafico();

protected:
    int x;
    int y;
    QString sprite;
    bool activo;
    QGraphicsItem *grafico;
};

#endif
