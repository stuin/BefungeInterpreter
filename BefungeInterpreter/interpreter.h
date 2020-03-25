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



#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <stack>

#include "mainwindow.h"
#include "codetorus.h"



class Interpreter
{
public:
    enum unsupportedCharMode{ABORT, IGNORE, REFLECT};
    enum divideOrModByZeroMode{ASK, PUSHZERO, CRASH};
    Interpreter(MainWindow *parent, CodeTorus *torus);
    void step();
    QString stackToQString();
    void push(char c);
    char pop();
    QString getOutputStr();
    void clearOutputString();
    void setUnsupportedCharMode(unsupportedCharMode md);
    void setDivZeroMode(divideOrModByZeroMode md);
    void setModZeroMode(divideOrModByZeroMode md);

private:
    unsupportedCharMode unsupCharMode;
    divideOrModByZeroMode divideByZeroMode;
    divideOrModByZeroMode modByZeroMode;
    bool stringmode;
    MainWindow* parent;
    CodeTorus* torus;
    std::stack<char>* st;
    QString outputStr;
    void handleDivideByZero();
    void handleModulusZero(int a, int b);
    void output(char c);
    void output(int i);

};

#endif // INTERPRETER_H
