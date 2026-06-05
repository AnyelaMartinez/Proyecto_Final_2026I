#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    musica(new QSoundEffect(this)),
    musicaActiva(false)
{
    ui->setupUi(this);
    configurarEscena();
    conectarInterfaz();
    iniciarMusica();
    actualizarPanel();
    ui->stackedWidget->setCurrentIndex(0); // arranca en el menu
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    juego.presionarTecla(event->key());
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    juego.soltarTecla(event->key());
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::actualizarJuego()
{
    // Solo ejecutar la logica del juego cuando estamos en la pagina de juego
    if (ui->stackedWidget->currentIndex() == 1) {
        juego.ejecutar(0.016f);
        actualizarPanel();
        // Detectar fin del juego
        if (juego.getEstadoJuego() != Juego::EnCurso) {
            mostrarPantallaFin();
        }
    }
}

void MainWindow::guardarJuego()
{
    if (juego.guardar(archivoGuardado())) {
        ui->labelEstado->setText("Partida guardada correctamente.");
    } else {
        QMessageBox::warning(this, "Guardar", "No se pudo guardar la partida.");
    }
}

void MainWindow::cargarJuego()
{
    if (juego.cargar(archivoGuardado())) {
        actualizarPanel();
    } else {
        QMessageBox::warning(this, "Cargar", "No se pudo cargar la partida.");
    }
}

void MainWindow::alternarMusica()
{
    if (musicaActiva) {
        musica->stop();
        musicaActiva = false;
        ui->labelEstado->setText("Musica pausada.");
    } else {
        musica->play();
        musicaActiva = true;
        ui->labelEstado->setText("Musica activada.");
    }
}

void MainWindow::actualizarPanel()
{
    ui->labelNivel->setText(QString("Nivel: %1").arg(juego.getNivelActual()));
    ui->labelPuntuacion->setText(QString("Jugador: %1 | IA: %2")
                                     .arg(juego.getPuntuacionJugador())
                                     .arg(juego.getPuntuacionOponente()));
    if (juego.getNivelActual() == 1) {
        ui->labelLanzamientos->setText(QString("Meta: 30 puntos"));
    } else {
        ui->labelLanzamientos->setText(QString("Lanzamientos: %1").arg(juego.getLanzamientosRestantes()));
    }
    if (juego.getNivelActual() == 2) {
        int seg = static_cast<int>(juego.getTiempoRestanteNivel2());
        if (seg < 0) seg = 0;
        ui->labelTiempo->setText(QString("Tiempo: %1s").arg(seg));
        ui->labelTiempo->setVisible(true);
    } else {
        ui->labelTiempo->setVisible(false);
    }
    ui->labelEstado->setText(juego.estadoTexto());
}

void MainWindow::irAJugar()
{
    juego.reiniciar();
    actualizarPanel();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::irAMenuPrincipal()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::volverAJugarDesdeFin()
{
    juego.reiniciar();
    actualizarPanel();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::salirDelJuego()
{
    QApplication::quit();
}

void MainWindow::mostrarPantallaFin()
{
    bool gano = (juego.getEstadoJuego() == Juego::GanoJugador);
    if (gano) {
        ui->labelFinTitulo->setText("¡Ganaste!");
        ui->labelFinTitulo->setStyleSheet("color: rgb(20, 130, 30);");
    } else {
        ui->labelFinTitulo->setText("Game Over");
        ui->labelFinTitulo->setStyleSheet("color: rgb(180, 30, 30);");
    }
    ui->labelFinPuntaje->setText(QString("Tu: %1   |   IA: %2")
                                     .arg(juego.getPuntuacionJugador())
                                     .arg(juego.getPuntuacionOponente()));
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::configurarEscena()
{
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);

    // Que los botones no roben el foco del teclado
    ui->botonJugar->setFocusPolicy(Qt::NoFocus);
    ui->botonSalir->setFocusPolicy(Qt::NoFocus);
    ui->botonGuardar->setFocusPolicy(Qt::NoFocus);
    ui->botonCargar->setFocusPolicy(Qt::NoFocus);
    ui->botonMusica->setFocusPolicy(Qt::NoFocus);
    ui->botonMenuPrincipal->setFocusPolicy(Qt::NoFocus);
    ui->botonVolverJugar->setFocusPolicy(Qt::NoFocus);
    ui->botonVolverMenu->setFocusPolicy(Qt::NoFocus);

    juego.iniciar(scene);
}

void MainWindow::conectarInterfaz()
{
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    // Pagina Menu
    connect(ui->botonJugar, &QPushButton::clicked, this, &MainWindow::irAJugar);
    connect(ui->botonSalir, &QPushButton::clicked, this, &MainWindow::salirDelJuego);
    // Pagina Juego
    connect(ui->botonGuardar, &QPushButton::clicked, this, &MainWindow::guardarJuego);
    connect(ui->botonCargar, &QPushButton::clicked, this, &MainWindow::cargarJuego);
    connect(ui->botonMusica, &QPushButton::clicked, this, &MainWindow::alternarMusica);
    connect(ui->botonMenuPrincipal, &QPushButton::clicked, this, &MainWindow::irAMenuPrincipal);
    // Pagina Fin
    connect(ui->botonVolverJugar, &QPushButton::clicked, this, &MainWindow::volverAJugarDesdeFin);
    connect(ui->botonVolverMenu, &QPushButton::clicked, this, &MainWindow::irAMenuPrincipal);
}

void MainWindow::iniciarMusica()
{
    musica->setSource(QUrl("qrc:/sonidos/musica.wav"));
    musica->setLoopCount(QSoundEffect::Infinite);
    musica->setVolume(0.35f);
    musica->play();
    musicaActiva = true;
}

QString MainWindow::archivoGuardado() const
{
    return QDir(QCoreApplication::applicationDirPath()).filePath("partida_chilly.dat");
}
