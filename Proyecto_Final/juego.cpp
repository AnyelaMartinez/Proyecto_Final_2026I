#include "juego.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QPen>
#include <Qt>
#include <QtMath>

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
    piedra(90, 255),
    piedraIA(90, 210),
    chilly(50, 280),
    smedley(430, 120),
    pescado(350, 360),
    nivelActivo(&nivel1),
    medidorFuerza(200.0f),
    medidorDir(1),
    espacioAnterior(false),
    medidorFondo(nullptr),
    medidorRelleno(nullptr),
    medidorLabel(nullptr),
    anguloLanzamiento(0.0f),
    flechaLinea(nullptr),
    flechaIzq(nullptr),
    flechaDer(nullptr)
{
}

void Juego::iniciar(QGraphicsScene *nuevaScene)
{
    scene = nuevaScene;
    if (scene) {
        Pista &p = nivelActivo->getPista();
        scene->setSceneRect(0, 0, p.getAncho(), p.getAlto());
    }
    dibujarTodo();
}

void Juego::ejecutar(float dt)
{
    if (nivelActual == 1) {
        // Nivel 1: medidor de fuerza oscila, Espacio lanza, flechas giran el angulo
        actualizarMedidor(dt);
        if (entrada.flechaIzquierda()) {
            anguloLanzamiento += 60.0f * dt;
        }
        if (entrada.flechaDerecha()) {
            anguloLanzamiento -= 60.0f * dt;
        }
        anguloLanzamiento = qBound(-45.0f, anguloLanzamiento, 45.0f);
        actualizarFlechaAngulo();
        bool espacioActual = entrada.espacio();
        if (espacioActual && !espacioAnterior) {
            lanzarJugador(medidorFuerza, anguloLanzamiento);
        }
        espacioAnterior = espacioActual;
        chilly.dejarDeBarrer();
    } else {
        // Nivel 2: flechas mueven a Chilly, Espacio barre
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
    }

    nivelActivo->actualizar(dt);

    if (iaAnimando) {
        procesarTurnoIA(dt);
    }

    nivelActivo->getPista().aplicarZona(piedra);
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
        chilly.setPosicion(50, 280);
    } else {
        nivelActivo = &nivel2;
        chilly.setPosicion(80, 360);
    }
    espacioAnterior = true;
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
    Pista &p = nivelActivo->getPista();
    nuevoX = qMax(25, qMin(p.getAncho() - 25, nuevoX));
    nuevoY = qMax(35, qMin(p.getAlto() - 35, nuevoY));
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
    chilly.setPosicion(50, 280);
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
    medidorFondo = nullptr;
    medidorRelleno = nullptr;
    medidorLabel = nullptr;
    flechaLinea = nullptr;
    flechaIzq = nullptr;
    flechaDer = nullptr;
    nivelActivo->dibujar(scene);
    pescado.dibujar(scene);
    chilly.dibujar(scene);
    smedley.dibujar(scene);
    piedra.dibujar(scene);
    piedraIA.dibujar(scene);
    piedraIA.setActivo(iaAnimando);
    if (nivelActual == 1) {
        crearMedidor();
        crearFlechaAngulo();
    }
}

void Juego::crearMedidor()
{
    if (!scene) return;
    medidorFondo = scene->addRect(180, 470, 400, 22,
                                  QPen(QColor(50, 80, 130), 2),
                                  QBrush(QColor(220, 230, 245, 230)));
    medidorFondo->setZValue(20);

    float pct = qBound(0.0f, (medidorFuerza - 100.0f) / 700.0f, 1.0f);
    float w = pct * 400.0f;
    medidorRelleno = scene->addRect(180, 470, w, 22,
                                    QPen(Qt::NoPen),
                                    QBrush(QColor(50, 150, 255, 220)));
    medidorRelleno->setZValue(21);

    QFont fonte("Arial", 9, QFont::Bold);
    medidorLabel = scene->addSimpleText("FUERZA  (Espacio para lanzar)", fonte);
    medidorLabel->setBrush(QBrush(QColor(40, 60, 100)));
    medidorLabel->setPos(180, 450);
    medidorLabel->setZValue(20);
}

void Juego::actualizarMedidor(float dt)
{
    if (!turnoJugador || esperandoResultado || lanzamientosRestantes <= 0) {
        return;
    }

    medidorFuerza += medidorDir * 600.0f * dt;
    if (medidorFuerza >= 800.0f) {
        medidorFuerza = 800.0f;
        medidorDir = -1;
    } else if (medidorFuerza <= 100.0f) {
        medidorFuerza = 100.0f;
        medidorDir = 1;
    }

    if (!medidorRelleno) return;

    float pct = qBound(0.0f, (medidorFuerza - 100.0f) / 700.0f, 1.0f);
    float w = pct * 400.0f;
    medidorRelleno->setRect(180, 470, w, 22);

    int r = static_cast<int>(255 * qMin(1.0f, 2 * pct));
    int g = static_cast<int>(255 * qMin(1.0f, 2 * (1 - pct)));
    medidorRelleno->setBrush(QBrush(QColor(r, g, 50, 230)));
}

void Juego::crearFlechaAngulo()
{
    if (!scene) return;
    QPen pen(QColor(255, 200, 0, 240), 3);
    flechaLinea = scene->addLine(0, 0, 0, 0, pen);
    flechaIzq = scene->addLine(0, 0, 0, 0, pen);
    flechaDer = scene->addLine(0, 0, 0, 0, pen);
    flechaLinea->setZValue(10);
    flechaIzq->setZValue(10);
    flechaDer->setZValue(10);
    actualizarFlechaAngulo();
}

void Juego::actualizarFlechaAngulo()
{
    if (!flechaLinea) return;

    bool visible = (turnoJugador && !esperandoResultado && piedra.detenido()
                    && lanzamientosRestantes > 0 && !iaAnimando);
    flechaLinea->setVisible(visible);
    flechaIzq->setVisible(visible);
    flechaDer->setVisible(visible);
    if (!visible) return;

    float rad = qDegreesToRadians(anguloLanzamiento);
    float startX = piedra.getX();
    float startY = piedra.getY();
    float L = 75.0f;
    float tipX = startX + L * std::cos(rad);
    float tipY = startY - L * std::sin(rad);
    flechaLinea->setLine(startX, startY, tipX, tipY);

    float headLen = 14.0f;
    float headRad = qDegreesToRadians(150.0f);
    float leftX = tipX + headLen * std::cos(rad + headRad);
    float leftY = tipY - headLen * std::sin(rad + headRad);
    flechaIzq->setLine(tipX, tipY, leftX, leftY);
    float rightX = tipX + headLen * std::cos(rad - headRad);
    float rightY = tipY - headLen * std::sin(rad - headRad);
    flechaDer->setLine(tipX, tipY, rightX, rightY);
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
        const int puntos = nivel1.getCasa().calcularPuntos(piedra);
        puntuacionJugador += puntos;
        esperandoResultado = false;
        turnoJugador = false;
        mensajeEstado = QString("Lanzamiento terminado. Chilly gano %1 puntos. Ahora lanza la IA.").arg(puntos);
        turnoIA();
    }
}

void Juego::procesarTurnoIA(float dt)
{
    Pista &p = nivelActivo->getPista();
    p.aplicarZona(piedraIA);
    piedraIA.actualizar(dt);

    if (piedraIA.getX() < 10 || piedraIA.getX() > p.getAncho() - 10
        || piedraIA.getY() < 10 || piedraIA.getY() > p.getAlto() - 10) {
        piedraIA.reiniciar(90, 210);
        piedraIA.setActivo(false);
        iaAnimando = false;
        turnoJugador = true;
        piedra.reiniciar();
        mensajeEstado = "La piedra de la IA salio de la pista. Turno de Chilly.";
        return;
    }

    if (piedraIA.detenido()) {
        Casa &c = nivel1.getCasa();
        const int puntosIA = c.calcularPuntos(piedraIA);
        agenteIA.registrarResultado(piedraIA.distanciaA(c));
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
    Pista &p = nivelActivo->getPista();
    if (piedra.getX() < 10 || piedra.getX() > p.getAncho() - 10
        || piedra.getY() < 10 || piedra.getY() > p.getAlto() - 10) {
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
    agenteIA.actuar(piedraIA, nivel1.getCasa());
    iaAnimando = true;
}
