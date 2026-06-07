#include "juego.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QPen>
#include <QRandomGenerator>
#include <Qt>
#include <QtMath>

Juego::Juego()
    : scene(nullptr),
    nivelActual(1),
    puntuacionJugador(0),
    puntuacionOponente(0),
    lanzamientosRestantes(5),
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
    flechaDer(nullptr),
    nivel2EsperandoComienzo(false),
    estadoJuego(EnCurso)
{
}

Juego::EstadoJuego Juego::getEstadoJuego() const
{
    return estadoJuego;
}

void Juego::setDificultad(Dificultad d)
{
    switch (d) {
    case Facil:
        agenteIA.setMargenError(15.0f); // IA falla mucho
        chilly.setInestabilidad(0.05f); // jugador apunta casi perfecto
        break;
    case Medio:
        agenteIA.setMargenError(5.0f);
        chilly.setInestabilidad(0.20f);
        break;
    case Dificil:
        agenteIA.setMargenError(2.0f);  // IA muy precisa
        chilly.setInestabilidad(0.40f); // jugador tiembla mas
        break;
    }
}

void Juego::setupNivel2()
{
    nivelActual = 2;
    nivelActivo = &nivel2;
    chilly.setPosicion(120, 400);
    smedley.setPosicion(620, 400);
    smedley.setPatronVertical(false);
    smedley.setActivo(true);
    pescado.reiniciar(380, 400);
    pescado.setModoRandom(false, 310, 470, 395, 405);
    piedraIA.setActivo(false);
    piedra.reiniciar(80, 400);
    piedra.setFriccion(0.45f);
    puntuacionJugador = 0;
    puntuacionOponente = 0;
    lanzamientosRestantes = 5;
    nivel2EsperandoComienzo = true;
    esperandoResultado = false;
    turnoJugador = true;
    iaAnimando = false;
    espacioAnterior = true;
    nivel2.setTiempoRestante(90.0f);
}

void Juego::iniciar(QGraphicsScene *nuevaScene)
{
    scene = nuevaScene;
    if (scene) {
        Pista &p = nivelActivo->getPista();
        scene->setSceneRect(0, 0, p.getAncho(), p.getAlto());
    }
    // Cargar efectos de sonido (solo una vez)
    if (!sonidoLanzar) {
        sonidoLanzar = std::make_unique<QSoundEffect>();
        sonidoLanzar->setSource(QUrl("qrc:/sonidos/whoosh.wav"));
        sonidoLanzar->setVolume(1.0);
        sonidoPez = std::make_unique<QSoundEffect>();
        sonidoPez->setSource(QUrl("qrc:/sonidos/sparkle.wav"));
        sonidoPez->setVolume(1.0);
        sonidoChoque = std::make_unique<QSoundEffect>();
        sonidoChoque->setSource(QUrl("qrc:/sonidos/thump.wav"));
        sonidoChoque->setVolume(1.0);
    }
    randomizarCasa();
    dibujarTodo();
}

void Juego::randomizarCasa()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    int randX = 540 + rng->bounded(121); // 540-660
    int randY = 150 + rng->bounded(231); // 150-380
    nivel1.getCasa().setCentro(Vector2D(static_cast<float>(randX), static_cast<float>(randY)));
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
        // Nivel 2
        actualizarCopos(dt);
        actualizarMedidor(dt);

        // Si el tiempo se acabo y el jugador esta esperando -> game over
        if (nivel2EsperandoComienzo && nivel2.getTiempoRestante() <= 0.0f) {
            nivel2EsperandoComienzo = false;
            lanzamientosRestantes = 0;
            mostrarResultadoFinalNivel2();
        }

        if (nivel2EsperandoComienzo) {
            // Esperando que el jugador apriete Espacio para lanzar
            chilly.setPosicion(120, 400);
            bool espacioActual = entrada.espacio();
            if (espacioActual && !espacioAnterior) {
                piedra.aplicarFuerza(medidorFuerza, 0.0f);
                esperandoResultado = true;
                nivel2EsperandoComienzo = false;
                --lanzamientosRestantes;
                mensajeEstado = QString("MANTEN Espacio mientras la piedra rueda para que llegue mas lejos.");
            }
            espacioAnterior = espacioActual;
            chilly.dejarDeBarrer();
        } else if (turnoJugador) {
            // Chilly sigue a la piedra, Espacio barre
            chilly.setPosicion(piedra.getX() + 45, 400);
            if (entrada.espacio()) {
                barrer();
            } else {
                chilly.dejarDeBarrer();
            }
        } else {
            // Turno de la IA
            chilly.dejarDeBarrer();
        }
    }

    nivelActivo->actualizar(dt);

    if (iaAnimando) {
        if (nivelActual == 1) {
            procesarTurnoIA(dt);
        } else {
            procesarTurnoIANivel2(dt);
        }
    }

    nivelActivo->getPista().aplicarZona(piedra);
    if (chilly.estaBarriendo()) {
        float friccion = chilly.tieneBonus() ? 0.08f : 0.18f;
        piedra.setFriccion(friccion);
        nivelActivo->procesarBarrido();
    }

    piedra.actualizar(dt * 0.7f);
    chilly.actualizar(dt);
    smedley.actualizar(dt);
    pescado.actualizar(dt);
    if (smedley.interferir(piedra) && sonidoChoque) sonidoChoque->play();
    actualizarColisiones();
    mantenerDentroDePista();
    procesarFinDeLanzamiento();
}

void Juego::cambiarNivel()
{
    if (nivelActual == 2) {
        mensajeEstado = "Reinicia para volver al Nivel 1.";
        return;
    }
    if (esperandoResultado || iaAnimando) {
        mensajeEstado = "Espera a que termine el turno actual.";
        return;
    }
    if (lanzamientosRestantes > 0) {
        mensajeEstado = "Termina los lanzamientos del Nivel 1 primero.";
        return;
    }
    if (puntuacionJugador <= puntuacionOponente) {
        mensajeEstado = "No puedes pasar al Nivel 2 sin ganar el Nivel 1.";
        return;
    }

    // Pasar a Nivel 2
    nivelActual = 2;
    nivelActivo = &nivel2;
    chilly.setPosicion(120, 400);
    smedley.setPosicion(620, 400);
    smedley.setPatronVertical(false);
    smedley.setActivo(true);
    pescado.reiniciar(380, 400);
    pescado.setModoRandom(false, 310, 470, 395, 405);
    piedraIA.setActivo(false);
    piedra.reiniciar(80, 400);
    piedra.setFriccion(0.45f);
    puntuacionJugador = 0;
    puntuacionOponente = 0;
    lanzamientosRestantes = 5;
    nivel2EsperandoComienzo = true;
    esperandoResultado = false;
    turnoJugador = true;
    iaAnimando = false;
    espacioAnterior = true;
    mensajeEstado = "Nivel 2: Espacio = lanzar / barrer. Barrer baja la friccion (la piedra se desliza mas).";
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

bool Juego::guardar(const QString &archivo)
{
    bool ok = GestorPersistencia::instancia().guardar(archivo, *this);
    if (ok) {
        mensajeEstado = "Partida guardada.";
    }
    return ok;
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
    if (sonidoLanzar) sonidoLanzar->play();
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
    lanzamientosRestantes = 5;
    esperandoResultado = false;
    iaAnimando = false;
    turnoJugador = true;
    nivel2EsperandoComienzo = false;
    estadoJuego = EnCurso;
    nivel2.setTiempoRestante(90.0f);
    mensajeEstado = "Juego reiniciado.";
    piedra.reiniciar();
    piedraIA.reiniciar(90, 210);
    piedraIA.setActivo(false);
    chilly.setPosicion(50, 280);
    smedley.setPosicion(430, 120);
    smedley.setPatronVertical(true);
    smedley.setActivo(true);
    pescado.reiniciar(350, 360);
    pescado.setModoRandom(true, 150, 600, 100, 450);
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

float Juego::getTiempoRestanteNivel2() const
{
    return nivel2.getTiempoRestante();
}

QString Juego::estadoTexto() const
{
    return mensajeEstado;
}

void Juego::setEstado(int nivel, int puntosJugador, int puntosOponente, int lanzamientos, float tiempoRestante)
{
    nivelActual = nivel;
    puntuacionJugador = puntosJugador;
    puntuacionOponente = puntosOponente;
    lanzamientosRestantes = lanzamientos;
    esperandoResultado = false;
    iaAnimando = false;
    turnoJugador = true;
    espacioAnterior = true;
    piedraIA.setActivo(false);

    if (nivelActual == 1) {
        nivelActivo = &nivel1;
        chilly.setPosicion(50, 280);
        smedley.setPosicion(430, 120);
        smedley.setPatronVertical(true);
        smedley.setActivo(true);
        pescado.reiniciar(350, 360);
        pescado.setModoRandom(true, 150, 600, 100, 450);
        piedra.reiniciar();
        nivel2EsperandoComienzo = false;
    } else {
        nivelActivo = &nivel2;
        chilly.setPosicion(120, 400);
        smedley.setPosicion(620, 400);
        smedley.setPatronVertical(false);
        smedley.setActivo(true);
        pescado.reiniciar(380, 400);
        pescado.setModoRandom(false, 310, 470, 395, 405);
        piedra.reiniciar(80, 400);
        piedra.setFriccion(0.45f);
        nivel2.setTiempoRestante(tiempoRestante);
        nivel2EsperandoComienzo = true;
    }
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
    copos.clear();
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
    } else {
        crearCopos();
        crearMedidor();
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
    bool deberiaActivo;
    if (nivelActual == 1) {
        deberiaActivo = (turnoJugador && !esperandoResultado && lanzamientosRestantes > 0);
    } else {
        deberiaActivo = nivel2EsperandoComienzo;
    }

    if (medidorFondo) medidorFondo->setVisible(deberiaActivo);
    if (medidorRelleno) medidorRelleno->setVisible(deberiaActivo);
    if (medidorLabel) medidorLabel->setVisible(deberiaActivo);

    if (!deberiaActivo) return;

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
        if (sonidoPez) sonidoPez->play();
    }
}

void Juego::procesarFinDeLanzamiento()
{
    if (!esperandoResultado || !piedra.detenido()) {
        return;
    }

    if (nivelActual == 1) {
        const int puntos = nivel1.getCasa().calcularPuntos(piedra);
        puntuacionJugador += puntos;
        esperandoResultado = false;
        turnoJugador = false;
        mensajeEstado = QString("Chilly gano %1 puntos (total: %2). Ahora lanza la IA.").arg(puntos).arg(puntuacionJugador);
        turnoIA();
    } else {
        esperandoResultado = false;
        turnoJugador = false;
        int distJugador = qAbs(piedra.getX() - 660);
        int puntos = 0;
        if (distJugador < 50) puntos = 10;
        else if (distJugador < 100) puntos = 6;
        else if (distJugador < 160) puntos = 3;
        puntuacionJugador += puntos;
        mensajeEstado = QString("Tu piedra paro a %1 px. +%2 puntos. Turno de la IA.").arg(distJugador).arg(puntos);
        iniciarTurnoIANivel2();
    }
}

void Juego::iniciarTurnoIANivel2()
{
    piedraIA.reiniciar(80, 400);
    piedraIA.setFriccion(0.45f);
    piedraIA.setActivo(true);
    // Distancia objetivo ~580 px, multiplicador ~0.55 considerando los parches de nieve
    float fuerza = 320.0f + (QRandomGenerator::global()->generateDouble() * 60.0 - 30.0);
    piedraIA.aplicarFuerza(fuerza, 0.0f);
    iaAnimando = true;
}

void Juego::procesarTurnoIANivel2(float dt)
{
    Pista &p = nivelActivo->getPista();
    p.aplicarZona(piedraIA);
    piedraIA.actualizar(dt * 0.7f);
    if (smedley.interferir(piedraIA) && sonidoChoque) sonidoChoque->play();

    bool fueraDePista = (piedraIA.getX() < 10 || piedraIA.getX() > p.getAncho() - 10);
    if (!fueraDePista && !piedraIA.detenido()) {
        return;
    }

    int distIA = fueraDePista ? 999 : qAbs(piedraIA.getX() - 660);
    int puntosIA = 0;
    if (distIA < 50) puntosIA = 10;
    else if (distIA < 100) puntosIA = 6;
    else if (distIA < 160) puntosIA = 3;
    puntuacionOponente += puntosIA;
    agenteIA.registrarResultado(static_cast<float>(distIA), static_cast<float>(piedraIA.getX()), 660.0f);
    iaAnimando = false;
    piedraIA.setActivo(false);

    if (lanzamientosRestantes <= 0 || nivel2.getTiempoRestante() <= 0.0f) {
        mostrarResultadoFinalNivel2();
    } else {
        piedra.reiniciar(80, 400);
        nivel2EsperandoComienzo = true;
        turnoJugador = true;
        espacioAnterior = true;
        mensajeEstado = QString("La IA hizo %1 puntos. Te quedan %2 lanzamientos. Presiona Espacio.").arg(puntosIA).arg(lanzamientosRestantes);
    }
}

void Juego::mostrarResultadoFinalNivel2()
{
    if (puntuacionJugador > puntuacionOponente) {
        estadoJuego = GanoJugador;
        mensajeEstado = QString("Fin Nivel 2 - Ganaste! Tu: %1, IA: %2").arg(puntuacionJugador).arg(puntuacionOponente);
    } else {
        estadoJuego = GanoIA;
        mensajeEstado = QString("Fin Nivel 2 - Perdiste. Tu: %1, IA: %2").arg(puntuacionJugador).arg(puntuacionOponente);
    }
}

void Juego::crearCopos()
{
    if (!scene) return;
    QRandomGenerator rng(12345u);
    for (int i = 0; i < 60; i++) {
        Copo c;
        c.x = rng.bounded(760);
        c.y = rng.bounded(510);
        c.velY = 30.0f + rng.bounded(40);
        c.radio = 2 + rng.bounded(3);
        c.item = scene->addEllipse(c.x - c.radio, c.y - c.radio, c.radio * 2, c.radio * 2,
                                   QPen(Qt::NoPen), QBrush(QColor(255, 255, 255, 200)));
        c.item->setZValue(2);
        copos.push_back(c);
    }
}

void Juego::actualizarCopos(float dt)
{
    for (auto &c : copos) {
        c.y += c.velY * dt;
        if (c.y > 510) {
            c.y = -10;
        }
        if (c.item) {
            c.item->setRect(c.x - c.radio, c.y - c.radio, c.radio * 2, c.radio * 2);
        }
    }
}

void Juego::procesarTurnoIA(float dt)
{
    Pista &p = nivelActivo->getPista();
    p.aplicarZona(piedraIA);
    piedraIA.actualizar(dt * 0.7f);

    bool fueraDePista = (piedraIA.getX() < 10 || piedraIA.getX() > p.getAncho() - 10
                         || piedraIA.getY() < 10 || piedraIA.getY() > p.getAlto() - 10);
    if (!fueraDePista && !piedraIA.detenido()) {
        return;
    }

    Casa &c = nivel1.getCasa();
    int puntosIA = 0;
    if (!fueraDePista) {
        puntosIA = c.calcularPuntos(piedraIA);
        agenteIA.registrarResultado(piedraIA.distanciaA(c), piedraIA.getX(), c.centroCasa().x);
        agenteIA.ajustarDificultad(puntosIA == 0);
    } else {
        agenteIA.registrarResultado(1000.0f, static_cast<float>(piedraIA.getX()), c.centroCasa().x);
        agenteIA.ajustarDificultad(true);
    }
    puntuacionOponente += puntosIA;
    piedraIA.reiniciar(90, 210);
    piedraIA.setActivo(false);
    iaAnimando = false;
    turnoJugador = true;
    piedra.reiniciar();
    espacioAnterior = true;

    if (lanzamientosRestantes <= 0) {
        // Fin del Nivel 1: gana quien tenga mas puntos
        if (puntuacionJugador > puntuacionOponente) {
            setupNivel2();
            mensajeEstado = QString("Ganaste el Nivel 1 (%1 a %2)! Pasaste al Nivel 2.")
                                .arg(puntuacionJugador).arg(puntuacionOponente);
            dibujarTodo();
        } else {
            estadoJuego = GanoIA;
            if (puntuacionJugador < puntuacionOponente) {
                mensajeEstado = QString("Fin Nivel 1 - Perdiste. Tu: %1, IA: %2")
                .arg(puntuacionJugador).arg(puntuacionOponente);
            } else {
                mensajeEstado = QString("Empate %1-%2. Intentalo de nuevo.")
                .arg(puntuacionJugador).arg(puntuacionOponente);
            }
        }
    } else {
        // Siguiente ronda: nueva posicion de la casa
        randomizarCasa();
        dibujarTodo();
        if (fueraDePista) {
            mensajeEstado = QString("La IA fallo. Tu: %1 / IA: %2. Te quedan %3 tiros.")
            .arg(puntuacionJugador).arg(puntuacionOponente).arg(lanzamientosRestantes);
        } else {
            mensajeEstado = QString("La IA gano %1 puntos. Tu: %2 / IA: %3. Te quedan %4 tiros.")
            .arg(puntosIA).arg(puntuacionJugador).arg(puntuacionOponente).arg(lanzamientosRestantes);
        }
    }
}

void Juego::mantenerDentroDePista()
{
    Pista &p = nivelActivo->getPista();
    bool fuera = (piedra.getX() < 10 || piedra.getX() > p.getAncho() - 10
                  || piedra.getY() < 10 || piedra.getY() > p.getAlto() - 10);
    if (!fuera) return;

    // En ambos niveles, paramos la piedra donde se salio. Asi procesarFinDeLanzamiento
    // calcula 0 puntos (si quedo fuera de la casa) y le pasa el turno a la IA normalmente.
    piedra.setVelocidad(Vector2D(0, 0));
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
