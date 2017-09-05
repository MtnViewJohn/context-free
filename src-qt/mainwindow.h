#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

class AsyncRenderer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        QTimer t;
        QString currentFile;
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        Ui::MainWindow *ui;
        QGraphicsScene *scene;
        bool saveFile();
        bool saveFileAs();
        void openFile();
        void newFile();
    public slots:
        void runCode();
        void saveFileAction();
        void saveFileAsAction();
        void openFileAction();
        void newFileAction();
        void showPrefs();

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
        AsyncRenderer *r = NULL;
};

#endif // MAINWINDOW_H
