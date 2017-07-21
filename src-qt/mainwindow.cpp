#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <errno.h>
#include <cfdg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <variation.h>
#include <cstdio>
#include "cf-util.h"
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

bool MainWindow::confirmModify() {
    QMessageBox box;
    box.setText("You have unsaved changes which may be lost.");
    box.setInformativeText("Save your changes?");
    box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Save);
    int button = box.exec();
    switch(button) {
    case QMessageBox::Save:
        // save file and continue dangerous action
        this->saveFile();
        return true;
        break;
    case QMessageBox::Discard:
        // don't save file, but continue dangerous action
        return true;
        break;
    case QMessageBox::Cancel:
        // abort dangerous action
        return false;
        break;
    default:
        // this should never happen, unless I'm a grapefruit
        gerr("Unrecognized button! Aborting...");
        // Don't do it if you don't know what they said
        return false;
    }
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
    if(!confirmModify())
        return;
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
    if(!confirmModify())
        return;
    this->setWindowTitle("New Document - ContextFree");
    ui->code->document()->clearUndoRedoStacks();
    ui->code->document()->setPlainText("");
}
