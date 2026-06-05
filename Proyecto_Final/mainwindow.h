#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "juego.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMainWindow>
#include <QSoundEffect>
#include <QTimer>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void actualizarJuego();
    void guardarJuego();
    void cargarJuego();
    void alternarMusica();
    void actualizarPanel();
    void irAJugar();
    void irAMenuPrincipal();
    void volverAJugarDesdeFin();
    void salirDelJuego();

private:
    void configurarEscena();
    void conectarInterfaz();
    void iniciarMusica();
    void mostrarPantallaFin();
    QString archivoGuardado() const;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    Juego juego;
    QSoundEffect *musica;
    bool musicaActiva;
};

#endif
