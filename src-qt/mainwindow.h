#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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
        void updateUi();
        void doneRender();
};

#endif // MAINWINDOW_H
