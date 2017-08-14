#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <errno.h>
#include <cfdg.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <variation.h>
#include <cstdio>
#include "cf-util.h"
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
    ui->cancelButton->setVisible(false);
    ui->code->setStyleSheet("font: 12px monospace");
    ui->output->setRenderHint(QPainter::Antialiasing);
    ui->output->setTransform(ui->output->transform().scale(1, -1));
    scene = new QGraphicsScene(this);
    ui->output->setScene(scene);
    ui->framesBox->setValue(1);
    ui->framesBox->setRange(1, 1000000);
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

    ofstream fs("/tmp/tmp.cfdg");
    if (!fs) {
        perror("Couldn't open tempfile");
        return;
    }
    fs << ui->code->toPlainText().toStdString() << std::endl;

    foreach (QGraphicsItem *item, scene->items())
        scene->removeItem(item);

    std::shared_ptr<QtCanvas> canv(new QtCanvas(ui->output->width(), ui->output->height()));

    ui->runButton->setText("Building...");
    ui->cancelButton->setVisible(true);
    ui->runButton->setIcon(QIcon::fromTheme("process-working"));
    ui->runButton->setDisabled(true);

    r = new AsyncRenderer(ui->output->width(), ui->output->height(), ui->framesBox->value(), canv, scene, this);
    connect(r, SIGNAL(done()), this, SLOT(doneRender()));
    connect(r, SIGNAL(aborted()), this, SLOT(abortRender()));
    connect(r, SIGNAL(updateRect()), this, SLOT(updateRect()));

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
    ui->code->document()->clearUndoRedoStacks();
    ui->code->document()->setPlainText("");
    this->setWindowTitle("New Document - ContextFree");
}

void MainWindow::doneRender() {
    qDebug() << "Done rendering";
    if(unlink("/tmp/tmp.cfdg"))
        perror("Unlinking tempfile");
    ui->cancelButton->setVisible(false);
    ui->runButton->setEnabled(true);
    ui->runButton->setText("Build");
    ui->runButton->setIcon(QIcon::fromTheme("media-playback-start"));
    delete r;
}

void MainWindow::stop() {
    r->cleanup();
}

void MainWindow::abortRender() {
    qDebug() << "Aborted rendering";
    if(unlink("/tmp/tmp.cfdg"))
        perror("Unlinking tempfile");
    ui->cancelButton->setVisible(false);
    ui->runButton->setEnabled(true);
    ui->runButton->setText("Build");
    ui->runButton->setIcon(QIcon::fromTheme("media-playback-start"));
}

void MainWindow::showmsg(const char* msg) {
    ui->statusBar->showMessage(msg, 1000);
    delete msg;
}

void MainWindow::updateRect() {
    QRectF ibr = scene->itemsBoundingRect();
    ui->output->setSceneRect(ibr);
    scene->setSceneRect(ibr);
}
