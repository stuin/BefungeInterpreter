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



#include <QFile>
#include <QSaveFile>
#include <QIODevice>

#include <fstream>
#include <string>
#include <ios>
#include <cstddef>

#include "file.h"


File::File(MainWindow* parent, QString dir)
{
    this->parent = parent;
    this->dir = dir;
    this->loadFile();
}

bool File::saveFile(QString sourceBoxText)
{
    return saveFileAs(dir, sourceBoxText);
}

bool File::saveFileAs(QString newDir, QString sourceBoxText)
{
    QSaveFile file(newDir);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;  // return false if file fails to open
    }
    if (-1 == file.write(sourceBoxText.toStdString().c_str())) {
        return false;  // return false if cannot write text for some reason
    }
    bool successful = file.commit();  // return whether the save was successful & closes file

    return successful;
}

void File::setDir(QString newDir)
{
    this->dir = newDir;
}

bool File::loadFile() {
    width = -1;
    height = 0;
    std::ifstream in(dir.toStdString());
    if (!in.is_open()){
        return false;  // return false if the file failed to open.
    }

    //clear the current source
    parent->setSourceBoxText(QString());

    //get the height & width of the input
    std::string currentLine;
    int numLines = 0;
    while (in.is_open() && std::getline(in, currentLine)){
        if ((int)currentLine.length() > width){
            width = (int)currentLine.length();
        }
        numLines ++;
    }
    if (numLines > height) {
        height = numLines;
    }


    // return to the beginning of the file
    in.clear();
    in.seekg(0, std::ios::beg);

    //input into the UI
    while (in.is_open() && std::getline(in, currentLine)){
        int i;
        for (i = 0; i < (int)currentLine.length(); i++){
            parent->addToSourceBox(currentLine.at(i));
        }
        while (i < width){
            parent->addToSourceBox(' ');
            i++;
        }
        parent->addToSourceBox('\n');
    }

    std::string tmp = dir.toStdString();

    std::size_t lastSlash = tmp.find_last_of("/\\");
    filepath = tmp.substr(0,lastSlash);
    filename = tmp.substr(lastSlash+1);

    return true;
}

int File::getWidth()
{
    return width;
}

int File::getHeight()
{
    return height;
}

QString File::getDir()
{
    return dir;
}

std::string File::getFilename()
{
    return filename;
}

std::string File::getFilepath()
{
    return filepath;
}
