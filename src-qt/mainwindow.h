#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

class AsyncRendQt;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        QTimer fpsTimer;
        QString currentFile;
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        Ui::MainWindow *ui;
        QGraphicsScene *scene;
        bool saveFile();
        bool saveFileAs();
        void openFile();
        void newFile();
        void exportFile();
    public slots:
        void runCode();
        void saveFileAction();
        void saveFileAsAction();
        void openFileAction();
        void newFileAction();
        void showPrefs();
        void exportFileAction();

        void doneRender();
        void stop();
        void abortRender();
        void showmsg(const char *msg);
        void updateRect();
        void incFrame();

        void startPlayback(bool shouldPlay);
        void setFrame(int frame);
    private:

        bool confirmModify(bool newFile);
        AsyncRendQt *r = NULL;
};

#endif // MAINWINDOW_H
