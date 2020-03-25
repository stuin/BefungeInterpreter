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



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCharFormat>
#include <QMouseEvent>
#include <QTextCursor>
#include <random>
#include <unordered_map>
#include <utility>

class File;
class CodeTorus;
class Interpreter;
class ClickFilter;

enum Mode{EDIT, RUN};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addToSourceBox(char c);
    void replaceAt(char c, int i);
    void setSourceBoxText(QString s);
    QString getSourceBoxText();
    void setStackBoxText(QString s);
    void output(char c);
    void output(int i);

    void programFinished();
    void invalidCharDialog(char c);

    bool isRunning();
    bool isStarted();
    bool isInRunMode();
    char inputChar();
    int inputInt();

    int randomBetweenZeroAndThree();

    bool toggleBreakpoint(int location);
    void highlightBreakpoint(QTextCursor curs, bool breakpoint, bool standalone = true);


private slots:
    void on_actionLoad_File_triggered();

    void on_runRadioButton_toggled(bool checked);

    void on_sourceBox_textChanged();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_sourceBox_redoAvailable(bool b);

    void on_sourceBox_copyAvailable(bool b);

    void on_sourceBox_undoAvailable(bool b);

    void on_menuFile_aboutToShow();

    void on_menuEdit_aboutToShow();

    void on_menuOptions_aboutToShow();

    void on_sourceBox_modificationChanged(bool arg1);

    void on_actionOverwrite_Mode_triggered(bool checked);

    void on_stepButton_clicked();

    void on_startButton_clicked();

    void on_debugButton_clicked();

    void on_speedBox_valueChanged(int arg1);

    void on_slowButton_clicked();

    void on_inputSubmitButton_clicked();

    void on_LFButton_clicked();

    void on_actionIgnore_triggered(bool checked);

    void on_actionReflect_triggered(bool checked);

    void on_actionSave_File_triggered();

    void on_actionKeep_Padding_From_Run_triggered(bool checked);

    void on_actionKeep_Runtime_Changes_triggered(bool checked);

    void on_actionSave_File_As_triggered();

    void on_actionClose_File_triggered();

    void on_actionAsk_For_Input_triggered(bool checked);

    void on_actionPush_Zero_triggered(bool checked);

    void on_actionAsk_For_Input_2_triggered(bool checked);

    void on_actionPush_Zero_2_triggered(bool checked);

    void on_actionCrash_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    File* f;
    CodeTorus* torus;
    Interpreter* terp;

    ClickFilter* clickFilter;

    int slowTime;

    QTextCharFormat *currentCharFormat;
    QTextCharFormat *defaultFormat;
    QTextCharFormat *breakpointFormat;
    QTextCharFormat *cursorAndBreakpointFormat;

    QTextCharFormat *directionFormat;
    QTextCharFormat *directionFormatPC;
    QTextCharFormat *quoteFormat;
    QTextCharFormat *quoteFormatPC;
    QTextCharFormat *mathFormat;
    QTextCharFormat *mathFormatPC;
    QTextCharFormat *putGetFormat;
    QTextCharFormat *putGetFormatPC;
    QTextCharFormat *inOutFormat;
    QTextCharFormat *inOutFormatPC;
    QTextCharFormat *logicFormat;
    QTextCharFormat *logicFormatPC;
    QTextCharFormat *stackManipFormat;
    QTextCharFormat *stackManipFormatPC;
    QTextCharFormat *endFormat;
    QTextCharFormat *endFormatPC;
    QTextCharFormat *trampolineFormat;
    QTextCharFormat *trampolineFormatPC;
    QTextCharFormat *numberFormat;
    QTextCharFormat *numberFormatPC;
    QTextCharFormat *invalidFormat;
    QTextCharFormat *invalidFormatPC;

    QTextCursor *cursor;

    std::unordered_map<int, std::unordered_map<int, int>> breakpoints;
    bool isBreakpoint(int location);
    void addBreakpoint(int location);
    void removeBreakpoint(int location);

    void syntaxHighlightSource();
    void syntaxHighlight(QTextCursor *cursor, bool standalone = true);
    void syntaxHighlightPC(QTextCursor *cursor, bool standalone = true);

    QString tmpOriginalProgram;

    std::mt19937 rand_gen;

    bool keepPadding;
    bool keepRuntimeChanges;

    bool savePrompt;
    bool fileIsOpen;
    Mode mode;
    bool undo, redo, copy;
    bool modified;
    bool running;
    bool started;
    bool submitted;
    bool resettable;

    void closeEvent(QCloseEvent *event);
    void highlightBreakpoints();
};

#endif // MAINWINDOW_H
