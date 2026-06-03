/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *panelControles;
    QLabel *labelTitulo;
    QLabel *labelNivel;
    QLabel *labelPuntuacion;
    QLabel *labelLanzamientos;
    QLabel *labelFuerza;
    QSlider *sliderFuerza;
    QLabel *labelAngulo;
    QSlider *sliderAngulo;
    QPushButton *botonLanzar;
    QPushButton *botonBarrer;
    QPushButton *botonCambiarNivel;
    QPushButton *botonReiniciar;
    QHBoxLayout *layoutGuardar;
    QPushButton *botonGuardar;
    QPushButton *botonCargar;
    QPushButton *botonMusica;
    QLabel *labelEstado;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1080, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(760, 520));

        horizontalLayout->addWidget(graphicsView);

        panelControles = new QVBoxLayout();
        panelControles->setObjectName("panelControles");
        labelTitulo = new QLabel(centralwidget);
        labelTitulo->setObjectName("labelTitulo");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelTitulo->setFont(font);

        panelControles->addWidget(labelTitulo);

        labelNivel = new QLabel(centralwidget);
        labelNivel->setObjectName("labelNivel");

        panelControles->addWidget(labelNivel);

        labelPuntuacion = new QLabel(centralwidget);
        labelPuntuacion->setObjectName("labelPuntuacion");

        panelControles->addWidget(labelPuntuacion);

        labelLanzamientos = new QLabel(centralwidget);
        labelLanzamientos->setObjectName("labelLanzamientos");

        panelControles->addWidget(labelLanzamientos);

        labelFuerza = new QLabel(centralwidget);
        labelFuerza->setObjectName("labelFuerza");

        panelControles->addWidget(labelFuerza);

        sliderFuerza = new QSlider(centralwidget);
        sliderFuerza->setObjectName("sliderFuerza");
        sliderFuerza->setMinimum(80);
        sliderFuerza->setMaximum(430);
        sliderFuerza->setValue(260);
        sliderFuerza->setOrientation(Qt::Horizontal);

        panelControles->addWidget(sliderFuerza);

        labelAngulo = new QLabel(centralwidget);
        labelAngulo->setObjectName("labelAngulo");

        panelControles->addWidget(labelAngulo);

        sliderAngulo = new QSlider(centralwidget);
        sliderAngulo->setObjectName("sliderAngulo");
        sliderAngulo->setMinimum(-35);
        sliderAngulo->setMaximum(35);
        sliderAngulo->setValue(0);
        sliderAngulo->setOrientation(Qt::Horizontal);

        panelControles->addWidget(sliderAngulo);

        botonLanzar = new QPushButton(centralwidget);
        botonLanzar->setObjectName("botonLanzar");

        panelControles->addWidget(botonLanzar);

        botonBarrer = new QPushButton(centralwidget);
        botonBarrer->setObjectName("botonBarrer");

        panelControles->addWidget(botonBarrer);

        botonCambiarNivel = new QPushButton(centralwidget);
        botonCambiarNivel->setObjectName("botonCambiarNivel");

        panelControles->addWidget(botonCambiarNivel);

        botonReiniciar = new QPushButton(centralwidget);
        botonReiniciar->setObjectName("botonReiniciar");

        panelControles->addWidget(botonReiniciar);

        layoutGuardar = new QHBoxLayout();
        layoutGuardar->setObjectName("layoutGuardar");
        botonGuardar = new QPushButton(centralwidget);
        botonGuardar->setObjectName("botonGuardar");

        layoutGuardar->addWidget(botonGuardar);

        botonCargar = new QPushButton(centralwidget);
        botonCargar->setObjectName("botonCargar");

        layoutGuardar->addWidget(botonCargar);


        panelControles->addLayout(layoutGuardar);

        botonMusica = new QPushButton(centralwidget);
        botonMusica->setObjectName("botonMusica");

        panelControles->addWidget(botonMusica);

        labelEstado = new QLabel(centralwidget);
        labelEstado->setObjectName("labelEstado");
        labelEstado->setMinimumSize(QSize(250, 80));
        labelEstado->setWordWrap(true);

        panelControles->addWidget(labelEstado);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        panelControles->addItem(verticalSpacer);


        horizontalLayout->addLayout(panelControles);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mundo de Chilly Willy - Fuerza y Angulo", nullptr));
        labelTitulo->setText(QCoreApplication::translate("MainWindow", "Controles", nullptr));
        labelNivel->setText(QCoreApplication::translate("MainWindow", "Nivel: 1", nullptr));
        labelPuntuacion->setText(QCoreApplication::translate("MainWindow", "Jugador: 0 | IA: 0", nullptr));
        labelLanzamientos->setText(QCoreApplication::translate("MainWindow", "Lanzamientos: 3", nullptr));
        labelFuerza->setText(QCoreApplication::translate("MainWindow", "Fuerza: 260", nullptr));
        labelAngulo->setText(QCoreApplication::translate("MainWindow", "Angulo: 0", nullptr));
        botonLanzar->setText(QCoreApplication::translate("MainWindow", "Lanzar piedra", nullptr));
        botonBarrer->setText(QCoreApplication::translate("MainWindow", "Barrer / Espacio", nullptr));
        botonCambiarNivel->setText(QCoreApplication::translate("MainWindow", "Cambiar nivel", nullptr));
        botonReiniciar->setText(QCoreApplication::translate("MainWindow", "Reiniciar", nullptr));
        botonGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        botonCargar->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        botonMusica->setText(QCoreApplication::translate("MainWindow", "Musica: ON/OFF", nullptr));
        labelEstado->setText(QCoreApplication::translate("MainWindow", "Listo para jugar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
