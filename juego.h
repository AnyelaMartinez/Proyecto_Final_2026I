#ifndef JUEGO_H
#define JUEGO_H

#include "agenteia.h"
#include "casa.h"
#include "chillywilly.h"
#include "gestorentrada.h"
#include "gestorpersistencia.h"
#include "nivel1.h"
#include "nivel2.h"
#include "pescadodorado.h"
#include "piedracurling.h"
#include "pista.h"
#include "smedley.h"

#include <QGraphicsScene>
#include <QString>

class Juego
{
public:
    Juego();

    void iniciar(QGraphicsScene *scene);
    void ejecutar(float dt);
    void cambiarNivel();
    bool verificarVictoria() const;
    bool verificarDerrota() const;
    bool guardar(const QString &archivo) const;
    bool cargar(const QString &archivo);

    void lanzarJugador(float fuerza, float angulo);
    void barrer();
    void moverChilly(int dx, int dy);
    void presionarTecla(int tecla);
    void soltarTecla(int tecla);
    void reiniciar();

    int getNivelActual() const;
    int getPuntuacionJugador() const;
    int getPuntuacionOponente() const;
    int getLanzamientosRestantes() const;
    QString estadoTexto() const;
    void setEstado(int nivel, int puntosJugador, int puntosOponente, int lanzamientos);

private:
    void dibujarTodo();
    void actualizarColisiones();
    void procesarFinDeLanzamiento();
    void procesarTurnoIA(float dt);
    void mantenerDentroDePista();
    void turnoIA();

    QGraphicsScene *scene;
    int nivelActual;
    int puntuacionJugador;
    int puntuacionOponente;
    int lanzamientosRestantes;
    bool esperandoResultado;
    bool iaAnimando;
    bool turnoJugador;
    QString mensajeEstado;

    Pista pista;
    Casa casa;
    PiedraCurling piedra;
    PiedraCurling piedraIA;
    ChillyWilly chilly;
    Smedley smedley;
    PescadoDorado pescado;
    Nivel1 nivel1;
    Nivel2 nivel2;
    AgenteIA agenteIA;
    GestorEntrada entrada;
    GestorPersistencia persistencia;
};

#endif
