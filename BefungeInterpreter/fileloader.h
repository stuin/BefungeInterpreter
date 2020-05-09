#ifndef FILELOADER_H
#define FILELOADER_H

#include <QAction>
#include "mainwindow.h"

class FileLoader : public QAction {
    Q_OBJECT
public:
    FileLoader(QString filepath, MainWindow *source) : QAction(filepath, source) {
        connect(this, &QAction::triggered, this, &FileLoader::loadFile);
    }

    ~FileLoader() {

    }

public slots:
    void loadFile() {
        QString filepath = text();
        if(filepath != "") {
            MainWindow *w = ((MainWindow*)parentWidget());
            w->loadFile(filepath);
        }
    }
};

#endif // FILELOADER_H
