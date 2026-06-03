QT += core gui widgets multimedia

CONFIG += c++17

TARGET = MundoChillyWillyQt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    fisica.cpp \
    vector2d.cpp \
    objetobase.cpp \
    personaje.cpp \
    chillywilly.cpp \
    smedley.cpp \
    pescadodorado.cpp \
    piedracurling.cpp \
    casa.cpp \
    zona.cpp \
    pista.cpp \
    nivel.cpp \
    nivel1.cpp \
    nivel2.cpp \
    agenteia.cpp \
    gestorentrada.cpp \
    gestorpersistencia.cpp \
    juego.cpp

HEADERS += \
    mainwindow.h \
    fisica.h \
    vector2d.h \
    objetobase.h \
    personaje.h \
    chillywilly.h \
    smedley.h \
    pescadodorado.h \
    piedracurling.h \
    casa.h \
    zona.h \
    pista.h \
    nivel.h \
    nivel1.h \
    nivel2.h \
    agenteia.h \
    gestorentrada.h \
    gestorpersistencia.h \
    juego.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    recursos.qrc
