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



#include "interpreter.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

Interpreter::Interpreter(MainWindow *parent, CodeTorus *torus)
{
    this->parent = parent;
    this->torus = torus;
    st = new std::stack<char>();
    stringmode = false;
    unsupCharMode = ABORT;
    divideByZeroMode = ASK;
    modByZeroMode = ASK;

}

void Interpreter::step()
{
    char c = torus->getCurrentChar();
    if (stringmode && c != '"'){
        push(c);
        torus->next();
        return;
    }

    switch (c) {
    case(' '): {  // do nothing
        torus->next();
        return;
    }
    case('+'): {  // add
        int a = (int) pop();
        int b = (int) pop();
        push((char)(a+b));
        torus->next();
        return;
    }
    case('-'): {  // subtract
        int a = (int) pop();
        int b = (int) pop();
        push((char)(b-a));
        torus->next();
        return;
    }
    case('*'): {  // multiply
        int a = (int) pop();
        int b = (int) pop();
        push((char)(a*b));
        torus->next();
        return;
    }
    case('/'): {  // divide
        int a = (int) pop();
        int b = (int) pop();
        if (a!=0) push((char)(b/a));
        else handleDivideByZero();
        //TODO: else: ask for input if a=0
        torus->next();
        return;
    }
    case('%'): {  // modulo
        int a = (int) pop();
        int b = (int) pop();
        if (a != 0) push((char)(b % a));
        else handleModulusZero(a, b);
        torus->next();
        return;
    }
    case('!'): {  // logical not
        int a = (int) pop();
        if (a==0) push((char)1);
        else push((char)0);
        torus->next();
        return;
    }
    case('`'): {  // greater than
        int a = (int) pop();
        int b = (int) pop();
        if (b>a) push((char)1);
        else push((char)0);
        torus->next();
        return;
    }
    case('>'): {  // direction right
        torus->changeDirection(CodeTorus::RIGHT);
        torus->next();
        return;
    }
    case('<'): {  // direction left
        torus->changeDirection(CodeTorus::LEFT);
        torus->next();
        return;
    }
    case('^'): {  // direction up
        torus->changeDirection(CodeTorus::UP);
        torus->next();
        return;
    }
    case('v'): {  // direction down
        torus->changeDirection(CodeTorus::DOWN);
        torus->next();
        return;
    }
    case('?'): {  // random direction
        torus->changeDirection((CodeTorus::direction)parent->randomBetweenZeroAndThree());  //generate random number between 0-3 as a direction
        torus->next();
        return;
    }
    case('_'): {  // horizontal if
        int a = (int) pop();
        if (a == 0) torus->changeDirection(CodeTorus::RIGHT);
        else torus->changeDirection(CodeTorus::LEFT);
        torus->next();
        return;
    }
    case('|'): {  // vertical if
        int a = (int) pop();
        if (a == 0) torus->changeDirection(CodeTorus::DOWN);
        else torus->changeDirection(CodeTorus::UP);
        torus->next();
        return;
    }
    case('"'): {  // accept text input (stringmode)
        stringmode = !stringmode;
        torus->next();
        return;
    }
    case(':'): {  // duplicate
        bool startsEmpty = (st->empty());
        char c = pop();
        if (!startsEmpty) push(c);  // only actually want to push it twice if the stack was empty
        push(c);
        torus->next();
        return;
    }
    case('\\'): {  // swap
        char c = pop();
        char d = pop();
        push(c);
        push(d);
        torus->next();
        return;
    }
    case('$'): {  // pop & discard
        pop();
        torus->next();
        return;
    }
    case('.'): {  // pop & output as integer
        int i = (int)pop();
        output(i);
        torus->next();
        return;
    }
    case(','): {  // pop & output as ASCII char
        char c = pop();
        output(c);
        torus->next();
        return;
    }
    case('#'): {  // trampoline
        torus->next();
        torus->next();
        return;
    }
    case('g'): {  // get value
        int y = (int)pop();
        int x = (int)pop();
        push(torus->getChar(x,y));

        torus->next();
        return;
    }
    case('p'): {  // put value
        int y = (int) pop();
        int x = (int) pop();
        char v = pop();
        torus->putChar(v, x, y);

        torus->next();
        return;
    }
    case('&'): {  // get integer input
        int i = parent->inputInt();
        push((char) i);
        torus->next();
        return;
    }
    case('~'): {  // get ASCII char input
        char c = parent->inputChar();
        push(c);
        torus->next();
        return;
    }
    case('@'): {  // End program
        parent->programFinished();
        return;
    }
    case('0'): {  // push this number
        push(char(0));
        torus->next();
        return;
    }
    case('1'): {  // push this number
        push(char(1));
        torus->next();
        return;
    }
    case('2'): {  // push this number
        push(char(2));
        torus->next();
        return;
    }
    case('3'): {  // push this number
        push(char(3));
        torus->next();
        return;
    }
    case('4'): {  // push this number
        push(char(4));
        torus->next();
        return;
    }
    case('5'): {  // push this number
        push(char(5));
        torus->next();
        return;
    }
    case('6'): {  // push this number
        push(char(6));
        torus->next();
        return;
    }
    case('7'): {  // push this number
        push(char(7));
        torus->next();
        return;
    }
    case('8'): {  // push this number
        push(char(8));
        torus->next();
        return;
    }
    case('9'): {  // push this number
        push(char(9));
        torus->next();
        return;
    }
    }
    switch (unsupCharMode) {

    case(ABORT): {
        parent->programFinished();
        parent->invalidCharDialog(c);
        return;
    }
    case(IGNORE): {
        torus->next();
        return;
    }
    case(REFLECT): {
        torus->reflectDirection();
        torus->next();
        return;
    }
    }
}

QString Interpreter::stackToQString()
{
    if (st->empty()) return QString("");
    std::stack<char> *backStack = new std::stack<char>();
    char tmp;
    std::string preOut("");

    // first push the whole stack to a temporary stack, so we can read it bottom to top
    while (!st->empty()) {
        backStack->push(st->top());
        st->pop();
    }

    tmp = backStack->top();
    st->push(tmp);
    backStack->pop();

    // add decimal value of first character
    std::stringstream ss;
    ss << std::dec << (int)tmp;
    std::string sttmp;
    ss >> sttmp;
    preOut.append(sttmp.c_str());

    // if it is a visible character, show that in the stack.
    if (tmp >= ' ' && tmp <= '~') {
        preOut.append(" (");
        preOut.insert(preOut.end(), tmp);
        preOut.append(")");
    }

    //for all other characters ( this is just so that our stack representation will be comma separated)
    while (!backStack->empty()) {
        tmp = backStack->top();
        st->push(tmp);
        backStack->pop();

        preOut.append(" , ");

        //add decimal value
        std::stringstream ss;
        ss << std::dec << (int)tmp;
        std::string sttmp;
        ss >> sttmp;
        preOut.append(sttmp.c_str());

        // if it is a visible character, show that in the stack.
        if (tmp >= ' ' && tmp <= '~') {
            preOut.append(" (");
            preOut.insert(preOut.end(), tmp);
            preOut.append(")");
        }
    }
    delete backStack;

    return QString(preOut.c_str());
}

void Interpreter::push(char c)
{
    st->push(c);
    if (!parent->isStarted()) parent->setStackBoxText(stackToQString());
}

char Interpreter::pop()
{
    if (st->empty()) return (char) 0;

    char tmp = st->top();
    st->pop();
    if (!parent->isStarted()) parent->setStackBoxText(stackToQString());
    return tmp;
}

QString Interpreter::getOutputStr()
{
    return outputStr;
}

void Interpreter::clearOutputString()
{
    outputStr = QString("");
}

void Interpreter::setUnsupportedCharMode(Interpreter::unsupportedCharMode md)
{
    this->unsupCharMode = md;
}

void Interpreter::setDivZeroMode(Interpreter::divideOrModByZeroMode md)
{
    this->divideByZeroMode = md;
}

void Interpreter::setModZeroMode(Interpreter::divideOrModByZeroMode md)
{
    this->modByZeroMode = md;
}

void Interpreter::handleDivideByZero()
{
    switch(divideByZeroMode) {
    case(ASK):{
        int i = parent->inputInt();
        push((char)i);
        return;
    }
    case(PUSHZERO):{
        push((char)0);
        return;
    }
    case(CRASH):{
        //should never happen, but put here to prevent compiler warning
        return;
    }
    }
}

void Interpreter::handleModulusZero(int a, int b)
{
    switch(modByZeroMode) {
    case(ASK):{
        int i = parent->inputInt();
        push((char)i);
        return;
    }
    case(PUSHZERO):{
        push((char)0);
        return;
    }
    case(CRASH):{
        push((char)(b % a));  // this will make the program crash
        return;
    }
    }
}

void Interpreter::output(char c)
{
    if (parent->isStarted()) outputStr = outputStr + c;
    else parent->output(c);
}

void Interpreter::output(int i)
{
    if (parent->isStarted()) outputStr.append(std::to_string(i).c_str());
    else parent->output(i);
}
