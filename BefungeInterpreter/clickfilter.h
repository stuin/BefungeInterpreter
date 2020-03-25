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

#ifndef CLICKFILTER_H
#define CLICKFILTER_H

#include <QObject>
#include <QEvent>
#include <QPlainTextEdit>
class MainWindow;

/*
 * this class intercepts click events on the QPlainTextEdit sourceBox
 * */
class ClickFilter : public QObject
{
    Q_OBJECT
public:
    ClickFilter(MainWindow* parentMainWindow, QObject *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:

private:
    MainWindow *parentMainWindow;
};

#endif // CLICKFILTER_H
