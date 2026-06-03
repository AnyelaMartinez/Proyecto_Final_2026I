#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    juego.presionarTecla(event->key());
    if (event->key() == Qt::Key_Space) {
        barrer();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    juego.soltarTecla(event->key());
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::actualizarJuego()
{
    juego.ejecutar(0.016f);
    actualizarPanel();
}

void MainWindow::lanzarPiedra()
{
    juego.lanzarJugador(ui->sliderFuerza->value(), ui->sliderAngulo->value());
    actualizarPanel();
}

void MainWindow::barrer()
{
    juego.barrer();
    actualizarPanel();
}

void MainWindow::cambiarNivel()
{
    juego.cambiarNivel();
    actualizarPanel();
}

void MainWindow::reiniciarJuego()
{
    juego.reiniciar();
    actualizarPanel();
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
    ui->labelLanzamientos->setText(QString("Lanzamientos: %1").arg(juego.getLanzamientosRestantes()));
    ui->labelFuerza->setText(QString("Fuerza: %1").arg(ui->sliderFuerza->value()));
    ui->labelAngulo->setText(QString("Angulo: %1 grados").arg(ui->sliderAngulo->value()));
    ui->labelEstado->setText(juego.estadoTexto());
}

void MainWindow::configurarEscena()
{
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);
    juego.iniciar(scene);
}

void MainWindow::conectarInterfaz()
{
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    connect(ui->botonLanzar, &QPushButton::clicked, this, &MainWindow::lanzarPiedra);
    connect(ui->botonBarrer, &QPushButton::clicked, this, &MainWindow::barrer);
    connect(ui->botonCambiarNivel, &QPushButton::clicked, this, &MainWindow::cambiarNivel);
    connect(ui->botonReiniciar, &QPushButton::clicked, this, &MainWindow::reiniciarJuego);
    connect(ui->botonGuardar, &QPushButton::clicked, this, &MainWindow::guardarJuego);
    connect(ui->botonCargar, &QPushButton::clicked, this, &MainWindow::cargarJuego);
    connect(ui->botonMusica, &QPushButton::clicked, this, &MainWindow::alternarMusica);
    connect(ui->sliderFuerza, &QSlider::valueChanged, this, &MainWindow::actualizarPanel);
    connect(ui->sliderAngulo, &QSlider::valueChanged, this, &MainWindow::actualizarPanel);
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
    return QDir(QCoreApplication::applicationDirPath()).filePath("partida_chilly.json");
}
