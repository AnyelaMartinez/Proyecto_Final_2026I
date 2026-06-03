#ifndef FISICA_H
#define FISICA_H

class PiedraCurling;

class Fisica
{
public:
    virtual ~Fisica();
    virtual void aplicar(PiedraCurling &piedra, float dt) = 0;
};

class FisicaFriccion : public Fisica
{
public:
    explicit FisicaFriccion(float coeficiente = 0.48f);
    void aplicar(PiedraCurling &piedra, float dt) override;
    float getCoeficiente() const;

private:
    float mu;
};

class FisicaColisionElastica : public Fisica
{
public:
    explicit FisicaColisionElastica(float restitucion = 0.75f);
    void aplicar(PiedraCurling &piedra, float dt) override;
    void aplicarContra(PiedraCurling &piedra, float normalX, float normalY) const;

private:
    float e;
};

class FisicaPerturbacion : public Fisica
{
public:
    FisicaPerturbacion(float amplitud = 35.0f, float frecuencia = 6.0f, float fase = 0.0f);
    void aplicar(PiedraCurling &piedra, float dt) override;

private:
    float A;
    float omega;
    float phi;
    float tiempo;
};

#endif
