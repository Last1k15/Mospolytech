QT       += core gui uiplugin designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 plugin release dll

TEMPLATE = lib

INSTALLS += target

SOURCES += \
    iconEditor.cpp \
    iconeditorplugin.cpp

HEADERS += \
    iconeditorplugin.h \
    iconEditor.h
