#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

class AsyncRenderer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
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
    private:
        bool confirmModify();
        AsyncRenderer *r;
};

#endif // MAINWINDOW_H
