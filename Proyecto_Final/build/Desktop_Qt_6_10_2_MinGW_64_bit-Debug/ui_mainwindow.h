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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *layoutCentral;
    QStackedWidget *stackedWidget;
    QWidget *pageMenu;
    QVBoxLayout *layoutMenu;
    QSpacerItem *spacerItem;
    QLabel *labelTituloMenu;
    QLabel *labelSubtituloMenu;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem2;
    QPushButton *botonJugar;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem4;
    QPushButton *botonSalir;
    QSpacerItem *spacerItem5;
    QSpacerItem *spacerItem6;
    QWidget *pageGame;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *panelControles;
    QLabel *labelTitulo;
    QLabel *labelNivel;
    QLabel *labelPuntuacion;
    QLabel *labelLanzamientos;
    QLabel *labelTiempo;
    QLabel *labelControles;
    QHBoxLayout *layoutGuardar;
    QPushButton *botonGuardar;
    QPushButton *botonCargar;
    QPushButton *botonMusica;
    QPushButton *botonMenuPrincipal;
    QLabel *labelEstado;
    QSpacerItem *spacerItem7;
    QWidget *pageFin;
    QVBoxLayout *layoutFin;
    QSpacerItem *spacerItem8;
    QLabel *labelFinTitulo;
    QLabel *labelFinPuntaje;
    QSpacerItem *spacerItem9;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem10;
    QPushButton *botonVolverJugar;
    QSpacerItem *spacerItem11;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem12;
    QPushButton *botonVolverMenu;
    QSpacerItem *spacerItem13;
    QSpacerItem *spacerItem14;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutCentral = new QVBoxLayout(centralwidget);
        layoutCentral->setContentsMargins(0, 0, 0, 0);
        layoutCentral->setObjectName("layoutCentral");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageMenu = new QWidget();
        pageMenu->setObjectName("pageMenu");
        layoutMenu = new QVBoxLayout(pageMenu);
        layoutMenu->setObjectName("layoutMenu");
        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutMenu->addItem(spacerItem);

        labelTituloMenu = new QLabel(pageMenu);
        labelTituloMenu->setObjectName("labelTituloMenu");
        labelTituloMenu->setAlignment(Qt::AlignCenter);

        layoutMenu->addWidget(labelTituloMenu);

        labelSubtituloMenu = new QLabel(pageMenu);
        labelSubtituloMenu->setObjectName("labelSubtituloMenu");
        labelSubtituloMenu->setAlignment(Qt::AlignCenter);

        layoutMenu->addWidget(labelSubtituloMenu);

        spacerItem1 = new QSpacerItem(20, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutMenu->addItem(spacerItem1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem2);

        botonJugar = new QPushButton(pageMenu);
        botonJugar->setObjectName("botonJugar");

        hboxLayout->addWidget(botonJugar);

        spacerItem3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem3);


        layoutMenu->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        spacerItem4 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem4);

        botonSalir = new QPushButton(pageMenu);
        botonSalir->setObjectName("botonSalir");

        hboxLayout1->addWidget(botonSalir);

        spacerItem5 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem5);


        layoutMenu->addLayout(hboxLayout1);

        spacerItem6 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutMenu->addItem(spacerItem6);

        stackedWidget->addWidget(pageMenu);
        pageGame = new QWidget();
        pageGame->setObjectName("pageGame");
        horizontalLayout = new QHBoxLayout(pageGame);
        horizontalLayout->setObjectName("horizontalLayout");
        graphicsView = new QGraphicsView(pageGame);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(760, 520));

        horizontalLayout->addWidget(graphicsView);

        panelControles = new QVBoxLayout();
        panelControles->setObjectName("panelControles");
        labelTitulo = new QLabel(pageGame);
        labelTitulo->setObjectName("labelTitulo");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelTitulo->setFont(font);

        panelControles->addWidget(labelTitulo);

        labelNivel = new QLabel(pageGame);
        labelNivel->setObjectName("labelNivel");

        panelControles->addWidget(labelNivel);

        labelPuntuacion = new QLabel(pageGame);
        labelPuntuacion->setObjectName("labelPuntuacion");

        panelControles->addWidget(labelPuntuacion);

        labelLanzamientos = new QLabel(pageGame);
        labelLanzamientos->setObjectName("labelLanzamientos");

        panelControles->addWidget(labelLanzamientos);

        labelTiempo = new QLabel(pageGame);
        labelTiempo->setObjectName("labelTiempo");
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        labelTiempo->setFont(font1);

        panelControles->addWidget(labelTiempo);

        labelControles = new QLabel(pageGame);
        labelControles->setObjectName("labelControles");
        QFont font2;
        font2.setPointSize(10);
        labelControles->setFont(font2);
        labelControles->setWordWrap(true);

        panelControles->addWidget(labelControles);

        layoutGuardar = new QHBoxLayout();
        layoutGuardar->setObjectName("layoutGuardar");
        botonGuardar = new QPushButton(pageGame);
        botonGuardar->setObjectName("botonGuardar");

        layoutGuardar->addWidget(botonGuardar);

        botonCargar = new QPushButton(pageGame);
        botonCargar->setObjectName("botonCargar");

        layoutGuardar->addWidget(botonCargar);


        panelControles->addLayout(layoutGuardar);

        botonMusica = new QPushButton(pageGame);
        botonMusica->setObjectName("botonMusica");

        panelControles->addWidget(botonMusica);

        botonMenuPrincipal = new QPushButton(pageGame);
        botonMenuPrincipal->setObjectName("botonMenuPrincipal");

        panelControles->addWidget(botonMenuPrincipal);

        labelEstado = new QLabel(pageGame);
        labelEstado->setObjectName("labelEstado");
        labelEstado->setMinimumSize(QSize(220, 80));
        labelEstado->setWordWrap(true);

        panelControles->addWidget(labelEstado);

        spacerItem7 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        panelControles->addItem(spacerItem7);


        horizontalLayout->addLayout(panelControles);

        stackedWidget->addWidget(pageGame);
        pageFin = new QWidget();
        pageFin->setObjectName("pageFin");
        layoutFin = new QVBoxLayout(pageFin);
        layoutFin->setObjectName("layoutFin");
        spacerItem8 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutFin->addItem(spacerItem8);

        labelFinTitulo = new QLabel(pageFin);
        labelFinTitulo->setObjectName("labelFinTitulo");
        labelFinTitulo->setAlignment(Qt::AlignCenter);

        layoutFin->addWidget(labelFinTitulo);

        labelFinPuntaje = new QLabel(pageFin);
        labelFinPuntaje->setObjectName("labelFinPuntaje");
        labelFinPuntaje->setAlignment(Qt::AlignCenter);

        layoutFin->addWidget(labelFinPuntaje);

        spacerItem9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutFin->addItem(spacerItem9);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        spacerItem10 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem10);

        botonVolverJugar = new QPushButton(pageFin);
        botonVolverJugar->setObjectName("botonVolverJugar");

        hboxLayout2->addWidget(botonVolverJugar);

        spacerItem11 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem11);


        layoutFin->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        spacerItem12 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem12);

        botonVolverMenu = new QPushButton(pageFin);
        botonVolverMenu->setObjectName("botonVolverMenu");

        hboxLayout3->addWidget(botonVolverMenu);

        spacerItem13 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem13);


        layoutFin->addLayout(hboxLayout3);

        spacerItem14 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutFin->addItem(spacerItem14);

        stackedWidget->addWidget(pageFin);

        layoutCentral->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mundo de Chilly Willy", nullptr));
        pageMenu->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"QWidget#pageMenu {\n"
"  background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"              stop:0 rgb(110, 150, 210), stop:0.5 rgb(180, 215, 240), stop:1 rgb(230, 245, 255));\n"
"}\n"
"QLabel#labelTituloMenu {\n"
"  color: rgb(180, 30, 30);\n"
"  font-size: 42pt;\n"
"  font-weight: bold;\n"
"}\n"
"QLabel#labelSubtituloMenu {\n"
"  color: rgb(40, 60, 100);\n"
"  font-size: 14pt;\n"
"  font-style: italic;\n"
"}\n"
"QPushButton {\n"
"  background-color: rgba(255, 255, 255, 230);\n"
"  border: 3px solid rgb(50, 80, 130);\n"
"  border-radius: 14px;\n"
"  color: rgb(20, 50, 100);\n"
"  font-weight: bold;\n"
"  font-size: 16pt;\n"
"  padding: 14px 40px;\n"
"  min-width: 220px;\n"
"}\n"
"QPushButton:hover {\n"
"  background-color: rgb(220, 240, 255);\n"
"  border-color: rgb(180, 30, 30);\n"
"}\n"
"QPushButton:pressed {\n"
"  background-color: rgb(180, 215, 240);\n"
"}\n"
"        ", nullptr));
        labelTituloMenu->setText(QCoreApplication::translate("MainWindow", "\342\235\204 Mundo de Chilly Willy \342\235\204", nullptr));
        labelSubtituloMenu->setText(QCoreApplication::translate("MainWindow", "Curling en el polo norte", nullptr));
        botonJugar->setText(QCoreApplication::translate("MainWindow", "Jugar", nullptr));
        botonSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        labelTitulo->setText(QCoreApplication::translate("MainWindow", "Mundo de Chilly Willy", nullptr));
        labelNivel->setText(QCoreApplication::translate("MainWindow", "Nivel: 1", nullptr));
        labelPuntuacion->setText(QCoreApplication::translate("MainWindow", "Jugador: 0 | IA: 0", nullptr));
        labelLanzamientos->setText(QCoreApplication::translate("MainWindow", "Lanzamientos: 3", nullptr));
        labelTiempo->setText(QCoreApplication::translate("MainWindow", "Tiempo: 90s", nullptr));
        labelControles->setText(QCoreApplication::translate("MainWindow", "Controles:\n"
"- Flechas izq/der: girar angulo\n"
"- Espacio: lanzar (Nivel 1) / barrer (Nivel 2)", nullptr));
        botonGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        botonCargar->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        botonMusica->setText(QCoreApplication::translate("MainWindow", "Musica: ON/OFF", nullptr));
        botonMenuPrincipal->setText(QCoreApplication::translate("MainWindow", "Men\303\272 principal", nullptr));
        labelEstado->setText(QCoreApplication::translate("MainWindow", "Listo para jugar", nullptr));
        pageFin->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"QWidget#pageFin {\n"
"  background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"              stop:0 rgb(110, 150, 210), stop:0.5 rgb(180, 215, 240), stop:1 rgb(230, 245, 255));\n"
"}\n"
"QLabel#labelFinTitulo {\n"
"  font-size: 48pt;\n"
"  font-weight: bold;\n"
"}\n"
"QLabel#labelFinPuntaje {\n"
"  color: rgb(40, 60, 100);\n"
"  font-size: 18pt;\n"
"  font-weight: bold;\n"
"}\n"
"QPushButton {\n"
"  background-color: rgba(255, 255, 255, 230);\n"
"  border: 3px solid rgb(50, 80, 130);\n"
"  border-radius: 14px;\n"
"  color: rgb(20, 50, 100);\n"
"  font-weight: bold;\n"
"  font-size: 14pt;\n"
"  padding: 12px 30px;\n"
"  min-width: 200px;\n"
"}\n"
"QPushButton:hover {\n"
"  background-color: rgb(220, 240, 255);\n"
"  border-color: rgb(180, 30, 30);\n"
"}\n"
"        ", nullptr));
        labelFinTitulo->setText(QCoreApplication::translate("MainWindow", "\302\241Ganaste!", nullptr));
        labelFinPuntaje->setText(QCoreApplication::translate("MainWindow", "Tu: 0 | IA: 0", nullptr));
        botonVolverJugar->setText(QCoreApplication::translate("MainWindow", "Volver a jugar", nullptr));
        botonVolverMenu->setText(QCoreApplication::translate("MainWindow", "Men\303\272 principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
