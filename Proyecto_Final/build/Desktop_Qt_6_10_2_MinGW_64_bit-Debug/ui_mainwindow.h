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
    QLabel *labelControles;
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
        MainWindow->resize(1000, 650);
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

        labelControles = new QLabel(centralwidget);
        labelControles->setObjectName("labelControles");
        QFont font1;
        font1.setPointSize(10);
        labelControles->setFont(font1);
        labelControles->setWordWrap(true);

        panelControles->addWidget(labelControles);

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
        labelEstado->setMinimumSize(QSize(220, 80));
        labelEstado->setWordWrap(true);

        panelControles->addWidget(labelEstado);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        panelControles->addItem(verticalSpacer);


        horizontalLayout->addLayout(panelControles);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mundo de Chilly Willy", nullptr));
        labelTitulo->setText(QCoreApplication::translate("MainWindow", "Mundo de Chilly Willy", nullptr));
        labelNivel->setText(QCoreApplication::translate("MainWindow", "Nivel: 1", nullptr));
        labelPuntuacion->setText(QCoreApplication::translate("MainWindow", "Jugador: 0 | IA: 0", nullptr));
        labelLanzamientos->setText(QCoreApplication::translate("MainWindow", "Lanzamientos: 3", nullptr));
        labelControles->setText(QCoreApplication::translate("MainWindow", "Controles:\n"
"- Flechas izq/der: girar angulo\n"
"- Espacio: lanzar (Nivel 1) / barrer (Nivel 2)", nullptr));
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
