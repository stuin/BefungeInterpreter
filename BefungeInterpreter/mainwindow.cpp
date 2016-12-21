#include <QString>
#include <QStringList>
#include <QChar>
#include <QFileDialog>
#include <QDir>
#include <QBrush>
#include <QColor>
#include <QTextOption>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextFormat>

#include <iostream>
#include <chrono>
#include <thread>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include "codetorus.h"
#include "interpreter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(2000,1200);
    MainWindow::setWindowTitle(QString("Kagof Befunge Interpreter"));

    ui->actionSave_File->setEnabled(false);

    currentCharFormat = new QTextCharFormat();
    currentCharFormat->setBackground(QBrush(Qt::cyan));

    ui->sourceBox->setWordWrapMode(QTextOption::NoWrap);
    defaultFormat = new QTextCharFormat(ui->sourceBox->currentCharFormat());

    mode = EDIT;
    fileIsOpen = false;
    undo = false;
    redo = false;
    copy = false;
    slowTime = ui->speedBox->value();

    running = false;
    started = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToSourceBox(char c)
{
    ui->sourceBox->insertPlainText(QString(c));
}

void MainWindow::setSourceBoxText(QString s)
{
    ui->sourceBox->setPlainText(s);
}

void MainWindow::setStackBoxText(QString s)
{
    ui->stackBox->setPlainText(s);
}

void MainWindow::output(char c)
{
    ui->outputBox->insertPlainText(QString(c));
}

void MainWindow::output(int i)
{
    ui->outputBox->insertPlainText(QString(std::to_string(i).c_str()));
}

void MainWindow::programFinished()
{
    if (started) ui->outputBox->setPlainText(QString(terp->getOutputStr()));
    running = false;
    started = false;
    ui->stepButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->debugButton->setEnabled(false);
    ui->slowButton->setEnabled(false);

    this->repaint();
    qApp->processEvents();
}

bool MainWindow::isRunning()
{
    return running;
}

bool MainWindow::isStarted()
{
    return started;
}


void MainWindow::on_actionLoad_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                          "Select Befunge-93 source file to load",
                                                          QDir::currentPath(),
                                                          tr("Befunge file (*.bf);; Text file (*.txt);;  All files (*.*)"));
    f = new File(this, filePath);
    fileIsOpen = true;
    ui->actionSave_File->setEnabled(true);
    ui->sourceBox->document()->setModified(false);
}

/*
 * turns on/off run mode.
 * */
void MainWindow::on_runRadioButton_toggled(bool checked)
{
    ui->editRadioButton->toggled(!checked);
    ui->sourceBox->setReadOnly(checked);  // user can't edit the text when in run mode.

    //Run Mode:
    if (checked) {

        //if we already opened the file, and haven't changed anything, can use previously obtained values
        if (fileIsOpen && !this->windowTitle().endsWith(QString("*"))) torus = new CodeTorus(this, f->getWidth(), f->getHeight(), ui->sourceBox->toPlainText());

        else{
            QString st = ui->sourceBox->toPlainText();

            //ending with a newline character. the upcoming for loop does not work without it
            if (!st.endsWith("\n")) {
                st.append(QChar('\n'));
                this->setSourceBoxText(st);
            }

            //find the width and height of this text
            int longest = -1;
            int current = 0;
            int numLines = 0;
            for (int i = 0; i < st.length(); i++){
                if (st.at(i).toLatin1()=='\n'){
                    if (current > longest) longest = current;
                    current = 0;
                    numLines++;
                }
                else current ++;
            }

            //remove the trailing newline, so that the split does not create a blank line at the end
            if (st.endsWith("\n")) {
                st.chop(1);
                this->setSourceBoxText(st);
            }

            QStringList sl = st.split(QChar('\n'));

            //pad each line with spaces, so that they are all the same length
            for (QStringList::iterator it = sl.begin(); it != sl.end(); it++) {
                while (it->length() < longest){
                    it->append(QChar(' '));
                }
            }

            st = sl.join(QChar('\n'));

            //re-append a trailing newline
            if (!st.endsWith("\n")) {
                st.append(QChar('\n'));
                this->setSourceBoxText(st);
            }
            this->setSourceBoxText(st);

            //create the torus & interpreter
            torus = new CodeTorus(this, longest, numLines, st);
            terp = new Interpreter(this, torus);
        }

        //highlight the first element
        cursor = new QTextCursor(ui->sourceBox->document());
        cursor->setPosition(1, QTextCursor::KeepAnchor);
        cursor->setCharFormat(*currentCharFormat);
        cursor->clearSelection();
        delete cursor;

        //we don't want the user to try to manually edit the source text when in run mode
        mode = RUN;
        ui->actionCut->setEnabled(false);
        ui->actionUndo->setEnabled(false);
        ui->actionRedo->setEnabled(false);
        ui->actionPaste->setEnabled(false);

    }
    else {
        mode = EDIT;
        ui->stackBox->clear();
        ui->inputBox->clear();
        ui->outputBox->clear();
        delete torus;
        delete terp;

        cursor = new QTextCursor(ui->sourceBox->document());
        cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        cursor->setCharFormat(*defaultFormat);
        cursor->clearSelection();
        delete cursor;
    }
    ui->sourceBox->setUndoRedoEnabled(checked);

    ui->startButton->setEnabled(checked);
    ui->debugButton->setEnabled(checked);
    ui->stepButton->setEnabled(checked);
    ui->slowButton->setEnabled(checked);
    ui->speedBox->setEnabled(checked);
    ui->speedLabel->setEnabled(checked);

    ui->inputLabel->setEnabled(checked);
    ui->stackLabel->setEnabled(checked);
    ui->outputLabel->setEnabled(checked);
}

void MainWindow::on_sourceBox_textChanged()
{
    ui->runRadioButton->setEnabled(((int)ui->sourceBox->toPlainText().length() != 0));
}

void MainWindow::on_actionCopy_triggered()
{
    ui->sourceBox->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->sourceBox->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    if (mode == EDIT) ui->sourceBox->paste();
    else ui->inputBox->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->sourceBox->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->sourceBox->redo();
}

void MainWindow::on_sourceBox_redoAvailable(bool b)
{
    redo = b;
}

void MainWindow::on_sourceBox_copyAvailable(bool b)
{
    copy = b;
}

void MainWindow::on_sourceBox_undoAvailable(bool b)
{
    undo = b;
}

void MainWindow::on_menuEdit_aboutToShow()
{
    ui->actionCopy->setEnabled(copy);
    ui->actionPaste->setEnabled(ui->sourceBox->canPaste());
    if (mode == EDIT){
        ui->actionCut->setEnabled(copy);
        ui->actionUndo->setEnabled(undo);
        ui->actionRedo->setEnabled(redo);
        ui->actionOverwrite_Mode->setEnabled(true);
    }
    else {
        ui->actionCut->setEnabled(false);
        ui->actionRedo->setEnabled(false);
        ui->actionUndo->setEnabled(false);
        ui->actionOverwrite_Mode->setEnabled(false);
    }
}

void MainWindow::on_sourceBox_modificationChanged(bool arg1)
{
    if (arg1) {
        if (fileIsOpen) {
            std::string tmpstr = "Kagof Befunge Interpreter - " + f->getFilename() + " *";
            MainWindow::setWindowTitle(QString(tmpstr.c_str()));
        }
        else MainWindow::setWindowTitle(QString("Kagof Befunge Interpreter *"));
    }
    else {
        if (fileIsOpen) {
            std::string tmpstr = "Kagof Befunge Interpreter - " + f->getFilename();
            MainWindow::setWindowTitle(QString(tmpstr.c_str()));
        }
        else MainWindow::setWindowTitle(QString("Kagof Befunge Interpreter"));
    }
}

void MainWindow::on_actionOverwrite_Mode_triggered(bool checked)
{
    ui->sourceBox->setOverwriteMode(checked);
}

void MainWindow::on_stepButton_clicked()
{
    terp->step();
    cursor = new QTextCursor(ui->sourceBox->document());
    cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor->setCharFormat(*defaultFormat);
    cursor->clearSelection();
    delete cursor;
    cursor = new QTextCursor(ui->sourceBox->document());
    cursor->setPosition(torus->position());
    cursor->setPosition(torus->position()+1, QTextCursor::KeepAnchor);
    cursor->setCharFormat(*currentCharFormat);
    cursor->clearSelection();
    delete cursor;
}

void MainWindow::on_startButton_clicked()
{
    started = !started;
    while (started) {
        terp->step();
    }
    cursor = new QTextCursor(ui->sourceBox->document());
    cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor->setCharFormat(*defaultFormat);
    cursor->clearSelection();
    delete cursor;
    cursor = new QTextCursor(ui->sourceBox->document());
    cursor->setPosition(torus->position());
    cursor->setPosition(torus->position()+1, QTextCursor::KeepAnchor);
    cursor->setCharFormat(*currentCharFormat);
    cursor->clearSelection();
    delete cursor;
}

void MainWindow::on_speedBox_valueChanged(int arg1)
{
    slowTime = arg1;
}

void MainWindow::on_slowButton_clicked()
{
    running = !running;
    if (running) {
        ui->slowButton->setText(QString("Stop"));
        while (running) {
            on_stepButton_clicked();

            //update the UI
            this->repaint();
            qApp->processEvents();

            //wait for the desired amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(slowTime));
        }
        ui->slowButton->setText(QString("Slow"));
    }
    else {
        ui->slowButton->setText(QString("Slow"));
        this->repaint();
        qApp->processEvents();
    }
}
