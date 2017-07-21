#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <errno.h>
#include <cfdg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <variation.h>
#include <cstdio>
#include <commandLineSystem.h>
#include <QtDebug>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include <QMessageBox>
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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::runCode() {

    int fd = open("/tmp/tmp.cfdg", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Couldn't open tempfile: ");
        return;
    }
    write(fd, ui->code->toPlainText().toStdString().c_str(), ui->code->toPlainText().length());
    ::close(fd);
    CommandLineSystem sys;
    cfdg_ptr design = CFDG::ParseFile("/tmp/tmp.cfdg", &sys, 7394);
    if(design == nullptr) {
        std::cerr << "OH NOES!" << std::endl;
        if(unlink("/tmp/tmp.cfdg"))
            perror("Unlinking tempfile: ");
        return;
    }
    std::shared_ptr<Renderer> rend(design->renderer(design, ui->output->width(),
                                                    ui->output->height(), 0.0001,
                                                    4,
                                                    2.0));
    foreach (QGraphicsItem *item, scene->items())
        scene->removeItem(item);
    QtCanvas canv(ui->output->width(), ui->output->height(), scene);
    rend->run(&canv, false);
    QRectF ibr = scene->itemsBoundingRect();
    ui->output->setSceneRect(ibr);
    scene->setSceneRect(ibr);

    //qDebug() << ui->output->items() << endl;
    if(unlink("/tmp/tmp.cfdg"))
        perror("Unlinking tempfile: ");
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
