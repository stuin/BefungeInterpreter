/*
╔═══════════════════════════════════════════════════╗
║* * * * * * * * * * * * * * * * * * * * * * * * * *║
║*                                                 *║
║*      Kagof Befunge-93 Interpreter v1.2.0        *║
║*      copyright (c) Karl Goffin 2016-2017        *║
║*    released under the open source MIT license   *║
║*                                                 *║
║*   http://github.com/Kagof/BefungeInterpreter    *║
║*                                                 *║
║*                                                 *║
║* * * * * * * * * * * * * * * * * * * * * * * * * *║
╚═══════════════════════════════════════════════════╝
                                                   */



#ifndef CODETORUS_H
#define CODETORUS_H

#include <QString>

#include "mainwindow.h"

class CodeTorus
{
public:
    enum direction{UP, DOWN, LEFT, RIGHT};
    CodeTorus(MainWindow *parent, int width, int height, QString chars);

    char getChar(int row, int col);
    void putChar(char c, int row, int col);
    void setChars(QString chars);
    void changeDirection(direction newDrctn);
    void reflectDirection();
    int getX();
    int getY();
    int position();
    char getCurrentChar();
    void next();
    QString getChars();
    int getHeight();
    int getWidth();

private:
    MainWindow *parent;
    QString chars;
    int width, height;
    direction drctn;
    int x;
    int y;
    char currentChar;
};

#endif // CODETORUS_H
