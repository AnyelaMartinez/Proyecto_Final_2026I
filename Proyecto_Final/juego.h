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

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QString>

#include <vector>

class Juego
{
public:
    enum EstadoJuego {
        EnCurso,
        GanoJugador,
        GanoIA
    };

    Juego();

    void iniciar(QGraphicsScene *scene);
    void ejecutar(float dt);
    void cambiarNivel();
    EstadoJuego getEstadoJuego() const;
    bool verificarVictoria() const;
    bool verificarDerrota() const;
    bool guardar(const QString &archivo);
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
    float getTiempoRestanteNivel2() const;
    QString estadoTexto() const;
    void setEstado(int nivel, int puntosJugador, int puntosOponente, int lanzamientos, float tiempoRestante);

private:
    void dibujarTodo();
    void actualizarColisiones();
    void procesarFinDeLanzamiento();
    void procesarTurnoIA(float dt);
    void mantenerDentroDePista();
    void turnoIA();
    void crearMedidor();
    void actualizarMedidor(float dt);
    void crearFlechaAngulo();
    void actualizarFlechaAngulo();
    void crearCopos();
    void actualizarCopos(float dt);
    void iniciarTurnoIANivel2();
    void procesarTurnoIANivel2(float dt);
    void mostrarResultadoFinalNivel2();
    void setupNivel2();
    void randomizarCasa();

    QGraphicsScene *scene;
    int nivelActual;
    int puntuacionJugador;
    int puntuacionOponente;
    int lanzamientosRestantes;
    bool esperandoResultado;
    bool iaAnimando;
    bool turnoJugador;
    QString mensajeEstado;

    PiedraCurling piedra;
    PiedraCurling piedraIA;
    ChillyWilly chilly;
    Smedley smedley;
    PescadoDorado pescado;
    Nivel1 nivel1;
    Nivel2 nivel2;
    Nivel *nivelActivo;
    AgenteIA agenteIA;
    GestorEntrada entrada;

    // Medidor de fuerza estilo golf (Nivel 1)
    float medidorFuerza;
    int medidorDir;
    bool espacioAnterior;
    QGraphicsRectItem *medidorFondo;
    QGraphicsRectItem *medidorRelleno;
    QGraphicsSimpleTextItem *medidorLabel;

    // Flecha de angulo (Nivel 1)
    float anguloLanzamiento;
    QGraphicsLineItem *flechaLinea;
    QGraphicsLineItem *flechaIzq;
    QGraphicsLineItem *flechaDer;

    // Estado del Nivel 2
    bool nivel2EsperandoComienzo;
    EstadoJuego estadoJuego;

    // Copos de nieve cayendo (Nivel 2)
    struct Copo {
        QGraphicsEllipseItem *item;
        float x;
        float y;
        float velY;
        int radio;
    };
    std::vector<Copo> copos;
};

#endif
