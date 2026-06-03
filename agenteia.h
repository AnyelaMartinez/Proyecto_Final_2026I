#ifndef AGENTEIA_H
#define AGENTEIA_H

class Casa;
class PiedraCurling;

class AgenteIA
{
public:
    AgenteIA();

    void percibir(int nivelActual);
    void analizar();
    void actuar(PiedraCurling &piedra, const Casa &casa);
    void ajustarDificultad(bool fallo);

private:
    float margenError;
    int nivelDificultad;
};

#endif
