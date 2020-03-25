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



#include <QApplication>
#include <QString>
#include <iostream>
#include <string>

#include "mainwindow.h"
#include "interpreter.h"
#include "codetorus.h"

int main(int argc, char *argv[])
{
    bool testmode = false;
    //testmode = true;

    QApplication a(argc, argv);
    MainWindow w;

    if (testmode){
        CodeTorus* t = new CodeTorus(&w,0,0,QString(" "));
        Interpreter i(&w, t);
        i.push('a');
        i.push('f');
        i.push('\n');
        i.push('n');

        QString s = i.stackToQString();
        std::cout << s.toStdString().c_str() << std::endl;

        return 0;
    }


    w.show();

    return a.exec();
}
