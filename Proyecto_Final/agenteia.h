#ifndef AGENTEIA_H
#define AGENTEIA_H

#include <QVector>

class Casa;
class PiedraCurling;

struct Percepcion
{
    float piedraX;
    float piedraY;
    float objetivoX;
    float objetivoY;
};

struct Decision
{
    float fuerza;
    float angulo;
};

struct Lanzamiento
{
    float fuerza;
    float angulo;
    float distanciaFinal;
    float xFinal;
};

class AgenteIA
{
public:
    AgenteIA();

    void percibir(int nivelActual);
    Percepcion percibirEstado(const PiedraCurling &piedra, const Casa &casa);
    void analizar();
    Decision razonar(const Percepcion &percepcion);
    void actuar(PiedraCurling &piedra, const Casa &casa);
    void ajustarDificultad(bool fallo);
    void registrarResultado(float distanciaFinal, float xFinal, float xObjetivo);
    void calcularCorreccion(float xObjetivo);
    void setMargenError(float m);

private:
    float margenError;
    int nivelDificultad;
    float sesgoAngulo;
    float sesgoFuerza;
    Decision ultimaDecision;
    QVector<Lanzamiento> historial;
};

#endif
