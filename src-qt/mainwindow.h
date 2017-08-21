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
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        Ui::MainWindow *ui;
        QGraphicsScene *scene;
    public slots:
        void runCode();
        void saveFile();
        void openFile();
        void newFile();
        void doneRender();
        void stop();
        void abortRender();
        void showmsg(const char *msg);
        void updateRect();
        void incFrame();

        void startPlayback(bool shouldPlay);
        void setFrame(int frame);
    private:
        bool confirmModify();
        AsyncRenderer *r = NULL;
};

#endif // MAINWINDOW_H
