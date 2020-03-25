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



#include "codetorus.h"

CodeTorus::CodeTorus(MainWindow *parent, int width, int height, QString chars)
{
    this->parent = parent;
    this->width = width;
    this->height = height;
    this->chars = chars;
    this->drctn = RIGHT;
    this->x = 0;
    this->y = 0;
    this->currentChar = getChar(x, y);
}

char CodeTorus::getChar(int x, int y)
{
    if (y < height && x < width){
        return chars.at(x + (width + 1)*y).toLatin1();
    }
    else return (char) 0;
}

void CodeTorus::putChar(char c, int x, int y)
{
    if (y < height && x < width){
        chars.replace(x + (width+1)*y, 1, new QChar(c),1);
        parent->replaceAt(c, x + (width+1)*y);
    }

/* TODO:
 * adjust size of torus if user tries to insert element outside torus range.
 * */
/*
    if (row >= height){
        height = row + 1;
        QString appender;
        for (int i = 0; i < width; i++)
    }
*/
}

void CodeTorus::setChars(QString chars)
{
    this->chars = chars;
}

void CodeTorus::changeDirection(direction newDrctn)
{
    this->drctn = newDrctn;
}

void CodeTorus::reflectDirection()
{
    if (drctn == UP) drctn = DOWN;
    else if (drctn == DOWN) drctn = UP;
    else if (drctn == LEFT) drctn = RIGHT;
    else if (drctn == RIGHT) drctn = LEFT;
}

int CodeTorus::getX()
{
    return x;
}

int CodeTorus::getY()
{
    return y;
}

int CodeTorus::position()
{
    return x + (width + 1)*y;
}

char CodeTorus::getCurrentChar()
{
    return currentChar;
}

void CodeTorus::next()
{
    switch(drctn) {
        case(RIGHT):
        {
            x = (x + 1) % width;
            break;
        }
        case(LEFT):
        {
            if (x == 0) x = width - 1;
            else x = x - 1;
            break;
        }
        case(UP):
        {
            if (y == 0) y = height - 1;
            else y = y - 1;
            break;
        }
        case(DOWN):
        {
            y = (y + 1) % height;
            break;
        }
    }
    currentChar = getChar(x, y);
}

QString CodeTorus::getChars()
{
    return chars;
}

int CodeTorus::getHeight()
{
    return height;
}

int CodeTorus::getWidth()
{
    return width;
}
