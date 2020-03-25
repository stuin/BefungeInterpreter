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



#ifndef FILE_H
#define FILE_H
#include <QString>
#include <vector>
#include <string>

#include "mainwindow.h"

class File
{
public:
    static const int DEFAULT_WIDTH = 80;
    static const int DEFAULT_HEIGHT = 25;
    File(MainWindow* parent, QString dir);
    bool saveFile(QString sourceBoxText);
    bool saveFileAs(QString newDir, QString sourceBoxText);

    void setDir(QString newDir);
    bool loadFile();
    int getWidth();
    int getHeight();
    QString getDir();
    std::string getFilename();
    std::string getFilepath();

private:
    MainWindow *parent;
    QString dir;
    int width, height;
    std::string filename, filepath;

};

#endif // FILE_H
