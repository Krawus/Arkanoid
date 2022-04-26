INCLUDEPATH += "C:/SFML-2.5.1/include"
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        Ball.cpp \
        Bricks.cpp \
        Racket.cpp \
        main.cpp

HEADERS += \
    Ball.h \
    Bricks.h \
    Logo.h \
    MyText.h \
    PowerUp.h \
    Racket.h
