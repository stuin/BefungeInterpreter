/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                 *
 *      Kagof Befunge-93 Interpreter v1.0.0        *
 *        copyright (c) Karl Goffin 2016           *
 *    released under the open source MIT license   *
 *                                                 *
 *   http://github.com/Kagof/BefungeInterpreter    *
 *                                                 *
 *                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


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
    Interpreter(MainWindow *parent, CodeTorus *torus);
    void step();
    QString stackToQString();
    void push(char c);
    char pop();
    QString getOutputStr();
    void setUnsupportedCharMode(unsupportedCharMode md);

private:
    unsupportedCharMode unsupCharMode;
    bool stringmode;
    MainWindow* parent;
    CodeTorus* torus;
    std::stack<char>* st;
    QString outputStr;
    void output(char c);
    void output(int i);

};

#endif // INTERPRETER_H
