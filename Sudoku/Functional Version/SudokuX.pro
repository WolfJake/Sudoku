#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T00:17:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuX
TEMPLATE = app


SOURCES += main.cpp\
        sudoku.cpp \
    qpushbuttongrid.cpp

HEADERS  += sudoku.h \
    qpushbuttongrid.h

FORMS    += sudoku.ui \
    qpushbuttongrid.ui
