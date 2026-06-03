#include "juego.h"

#include <QGraphicsScene>
#include <Qt>

Juego::Juego()
    : scene(nullptr),
    nivelActual(1),
    puntuacionJugador(0),
    puntuacionOponente(0),
    lanzamientosRestantes(3),
    esperandoResultado(false),
    iaAnimando(false),
    turnoJugador(true),
    mensajeEstado("Listo para lanzar"),
    pista(760, 510),
    casa(Vector2D(650, 255), 80),
    piedra(90, 255),
    piedraIA(90, 210),
    chilly(80, 360),
    smedley(430, 120),
    pescado(350, 360),
    nivelActivo(&nivel1)
{
}

void Juego::iniciar(QGraphicsScene *nuevaScene)
{
    scene = nuevaScene;
    if (scene) {
        scene->setSceneRect(0, 0, pista.getAncho(), pista.getAlto());
    }
    dibujarTodo();
}

void Juego::ejecutar(float dt)
{
    if (entrada.flechaArriba()) {
        moverChilly(0, -4);
    }
    if (entrada.flechaAbajo()) {
        moverChilly(0, 4);
    }
    if (entrada.flechaIzquierda()) {
        moverChilly(-4, 0);
    }
    if (entrada.flechaDerecha()) {
        moverChilly(4, 0);
    }
    if (entrada.espacio()) {
        barrer();
    } else {
        chilly.dejarDeBarrer();
    }

    nivelActivo->actualizar(dt);

    if (iaAnimando) {
        procesarTurnoIA(dt);
    }

    pista.aplicarZona(piedra);
    if (chilly.estaBarriendo()) {
        piedra.setFriccion(0.18f);
        nivelActivo->procesarBarrido();
    }

    piedra.actualizar(dt);
    chilly.actualizar(dt);
    smedley.actualizar(dt);
    pescado.actualizar(dt);
    smedley.interferir(piedra);
    actualizarColisiones();
    mantenerDentroDePista();
    procesarFinDeLanzamiento();
}

void Juego::cambiarNivel()
{
    nivelActual = nivelActual == 1 ? 2 : 1;
    if (nivelActual == 1) {
        nivelActivo = &nivel1;
    } else {
        nivelActivo = &nivel2;
    }
    piedra.reiniciar();
    mensajeEstado = nivelActual == 1
                        ? "Nivel 1: vista superior, prepara fuerza y angulo."
                        : "Nivel 2: vista lateral, usa barrido con espacio.";
    dibujarTodo();
}

bool Juego::verificarVictoria() const
{
    return lanzamientosRestantes <= 0 && puntuacionJugador >= puntuacionOponente;
}

bool Juego::verificarDerrota() const
{
    return lanzamientosRestantes <= 0 && puntuacionJugador < puntuacionOponente;
}

bool Juego::guardar(const QString &archivo) const
{
    return GestorPersistencia::instancia().guardar(archivo, *this);
}

bool Juego::cargar(const QString &archivo)
{
    const bool ok = GestorPersistencia::instancia().cargar(archivo, *this);
    if (ok) {
        dibujarTodo();
        mensajeEstado = "Partida cargada.";
    }
    return ok;
}

void Juego::lanzarJugador(float fuerza, float angulo)
{
    if (!piedra.detenido() || !turnoJugador || lanzamientosRestantes <= 0) {
        return;
    }

    chilly.lanzar(piedra, fuerza, angulo);
    esperandoResultado = true;
    --lanzamientosRestantes;
    mensajeEstado = "Chilly Willy lanzo la piedra.";
}

void Juego::barrer()
{
    chilly.barrer();
    mensajeEstado = "Barrido activo: baja la friccion temporalmente.";
}

void Juego::moverChilly(int dx, int dy)
{
    chilly.mover(dx, dy);
    int nuevoX = chilly.getX();
    int nuevoY = chilly.getY();
    nuevoX = qMax(25, qMin(pista.getAncho() - 25, nuevoX));
    nuevoY = qMax(35, qMin(pista.getAlto() - 35, nuevoY));
    chilly.setPosicion(nuevoX, nuevoY);
}

void Juego::presionarTecla(int tecla)
{
    entrada.presionar(tecla);
}

void Juego::soltarTecla(int tecla)
{
    entrada.soltar(tecla);
}

void Juego::reiniciar()
{
    nivelActual = 1;
    nivelActivo = &nivel1;
    puntuacionJugador = 0;
    puntuacionOponente = 0;
    lanzamientosRestantes = 3;
    esperandoResultado = false;
    iaAnimando = false;
    turnoJugador = true;
    mensajeEstado = "Juego reiniciado.";
    piedra.reiniciar();
    piedraIA.reiniciar(90, 210);
    piedraIA.setActivo(false);
    chilly.setPosicion(80, 360);
    smedley.setPosicion(430, 120);
    pescado.reiniciar(350, 360);
    dibujarTodo();
}

int Juego::getNivelActual() const
{
    return nivelActual;
}

int Juego::getPuntuacionJugador() const
{
    return puntuacionJugador;
}

int Juego::getPuntuacionOponente() const
{
    return puntuacionOponente;
}

int Juego::getLanzamientosRestantes() const
{
    return lanzamientosRestantes;
}

QString Juego::estadoTexto() const
{
    return mensajeEstado;
}

void Juego::setEstado(int nivel, int puntosJugador, int puntosOponente, int lanzamientos)
{
    nivelActual = nivel;
    if (nivelActual == 1) {
        nivelActivo = &nivel1;
    } else {
        nivelActivo = &nivel2;
    }
    puntuacionJugador = puntosJugador;
    puntuacionOponente = puntosOponente;
    lanzamientosRestantes = lanzamientos;
    piedra.reiniciar();
}

void Juego::dibujarTodo()
{
    if (!scene) {
        return;
    }
    scene->clear();
    piedra.limpiarGrafico();
    piedraIA.limpiarGrafico();
    chilly.limpiarGrafico();
    smedley.limpiarGrafico();
    pescado.limpiarGrafico();
    nivelActivo->dibujar(scene);
    if (nivelActual == 2) {
        casa.dibujar(scene);
    }
    pescado.dibujar(scene);
    chilly.dibujar(scene);
    smedley.dibujar(scene);
    piedra.dibujar(scene);
    piedraIA.dibujar(scene);
    piedraIA.setActivo(iaAnimando);
}

void Juego::actualizarColisiones()
{
    const int dx = chilly.getX() - pescado.getX();
    const int dy = chilly.getY() - pescado.getY();
    if (pescado.estaActivo() && dx * dx + dy * dy < 1600) {
        pescado.otorgarBonus(chilly);
        mensajeEstado = "Chilly recogio el pescado dorado: bonus activo.";
    }
}

void Juego::procesarFinDeLanzamiento()
{
    if (esperandoResultado && piedra.detenido()) {
        const int puntos = casa.calcularPuntos(piedra);
        puntuacionJugador += puntos;
        esperandoResultado = false;
        turnoJugador = false;
        mensajeEstado = QString("Lanzamiento terminado. Chilly gano %1 puntos. Ahora lanza la IA.").arg(puntos);
        turnoIA();
    }
}

void Juego::procesarTurnoIA(float dt)
{
    pista.aplicarZona(piedraIA);
    piedraIA.actualizar(dt);

    if (piedraIA.getX() < 10 || piedraIA.getX() > pista.getAncho() - 10
        || piedraIA.getY() < 10 || piedraIA.getY() > pista.getAlto() - 10) {
        piedraIA.reiniciar(90, 210);
        piedraIA.setActivo(false);
        iaAnimando = false;
        turnoJugador = true;
        piedra.reiniciar();
        mensajeEstado = "La piedra de la IA salio de la pista. Turno de Chilly.";
        return;
    }

    if (piedraIA.detenido()) {
        const int puntosIA = casa.calcularPuntos(piedraIA);
        agenteIA.registrarResultado(300.0f, 0.0f, piedraIA.distanciaA(casa));
        puntuacionOponente += puntosIA;
        agenteIA.ajustarDificultad(puntosIA == 0);
        piedraIA.setActivo(false);
        iaAnimando = false;
        turnoJugador = true;
        piedra.reiniciar();
        mensajeEstado = QString("La IA gano %1 puntos. Turno de Chilly.").arg(puntosIA);
    }
}

void Juego::mantenerDentroDePista()
{
    if (piedra.getX() < 10 || piedra.getX() > pista.getAncho() - 10
        || piedra.getY() < 10 || piedra.getY() > pista.getAlto() - 10) {
        piedra.reiniciar();
        esperandoResultado = false;
        mensajeEstado = "La piedra salio de la pista.";
    }
}

void Juego::turnoIA()
{
    agenteIA.percibir(nivelActual);
    agenteIA.analizar();
    piedraIA.reiniciar(90, 210);
    piedraIA.setActivo(true);
    agenteIA.actuar(piedraIA, casa);
    iaAnimando = true;
}
