#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderimpl.h"
#include <errno.h>
#include <cfdg.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <variation.h>
#include <cstdio>
#include <commandLineSystem.h>
#include <QtDebug>
#include <QGraphicsItem>
#include <pthread.h>
#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include "qtcanvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->code->setStyleSheet("font: 12px monospace");
    ui->output->setRenderHint(QPainter::Antialiasing);
    scene = new QGraphicsScene(this);
    ui->output->setScene(scene);
    QMetaObject::connectSlotsByName(this);
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(updateUi()));
    t->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

struct runArgs {
        shared_ptr<Renderer> rend;
        QtCanvas *canv;
};

void* asyncRun(void *runArgsStruct) {
    struct runArgs *args = reinterpret_cast<struct runArgs*>(runArgsStruct);
    args->rend->run(args->canv, false);
    return nullptr;
}

void MainWindow::runCode() {

    ofstream fs("/tmp/tmp.cfdg");
    if (!fs) {
        perror("Couldn't open tempfile");
        return;
    }
    fs << ui->code->toPlainText().toStdString() << std::endl;
    foreach (QGraphicsItem *item, scene->items())
        scene->removeItem(item);
    std::shared_ptr<QtCanvas> canv(new QtCanvas(ui->output->width(), ui->output->height()));
    ui->runButton->setIcon(QIcon::fromTheme("process-working"));
//    pthread_t *pt = new pthread_t;
//    pthread_attr_t *attr = new pthread_attr_t ;
//    pthread_attr_init(attr);
//    pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
//    struct runArgs args = (struct runArgs){rend, canv};
//    pthread_create(pt, attr, asyncRun, &args);
    ui->runButton->setText("Building...");
    ui->runButton->setDisabled(true);
    AsyncRenderer *r = new AsyncRenderer(ui->output->width(), ui->output->height(), canv, scene);
    connect(r, &AsyncRenderer::done, this, &MainWindow::doneRender);
    QRectF ibr = scene->itemsBoundingRect();
    ui->output->setSceneRect(ibr);
    scene->setSceneRect(ibr);
    //ui->runButton->setIcon(QIcon::fromTheme("media-playback-start"));
    //qDebug() << ui->output->items() << endl;
}

void MainWindow::openFile() {
    qDebug() << "Open file" << endl;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("CFDG file (*.cfdg);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        this->setWindowTitle(fileName.remove(0, fileName.lastIndexOf("/")+1) + " - ContextFree");
        QTextStream istream(&file);
        QString c;
        c.append(istream.readAll());
        ui->code->document()->clearUndoRedoStacks();
        ui->code->document()->setPlainText(c);
    }
}

void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("CFDG file (*.cfdg);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream ostream(&file);
        ostream << ui->code->document()->toPlainText();
    }
}

void MainWindow::newFile() {

}

void MainWindow::updateUi() {
    QApplication::processEvents();
}

void MainWindow::doneRender() {
    if(unlink("/tmp/tmp.cfdg"))
        perror("Unlinking tempfile");
    ui->runButton->setEnabled(true);
    ui->runButton->setText("Build");
}


