#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "asyncrenderer.h"
#include "settings_dialog.h"
#include "qtcanvas.h"
#include "qtsystem.h"
#include "exformats.h"

#include <cfdg.h>
#include <commandLineSystem.h>
#include <pngCanvas.h>
#include <SVGCanvas.h>
#include <aggCanvas.h>

#include <errno.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <variation.h>
#include <cstdio>
#include <QtDebug>
#include <QGraphicsItem>
#include <pthread.h>
#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QCloseEvent>

extern QDebug operator<<(QDebug out, const std::string& str);

// File i/o
QString readFileFromDisk(QString fname) {
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(Q_NULLPTR, "Unable to open file for read",
                                 file.errorString());
        return Q_NULLPTR;
    }
    return file.readAll();
}

bool writeFileToDisk(QString fname, QString ostring) {
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(Q_NULLPTR, "Unable to open file for write",
                                 file.errorString());
        return false;
    }
    QTextStream ostream(&file);
    ostream << ostring;
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Hide UI elements which should only be shown in particular circumstances
    ui->cancelButton->setVisible(false);
    ui->mediaBar->setVisible(false);

    ui->code->setStyleSheet("font: 12px monospace");

    ui->output->setRenderHint(QPainter::Antialiasing);

    // Flip output vertically to match orientation used by the rest of Contextfree
    ui->output->setTransform(ui->output->transform().scale(1, -1));

    scene = new QGraphicsScene(this);
    ui->output->setScene(scene);
    ui->framesBox->setValue(1);
    ui->framesBox->setRange(1, 1000000);

    // Set up timer for frame changing during playback
    QSettings s;
    fpsTimer.setInterval(1000/s.value("output_fps", 30).toDouble());

    currentFile = "";

    connect(&fpsTimer, SIGNAL(timeout()), this, SLOT(incFrame()));
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::confirmDangerAction() {

    if(!this->currentFile.isEmpty()) {
        QFile file(this->currentFile);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file for read"),
                                     file.errorString());
            return false; // Better safe than sorry
        }

        QString fileOnDisk = file.readAll();
        if (fileOnDisk == ui->code->document()->toPlainText())
            return true; // Safe to modify if it's the same
    } else if(ui->code->document()->toPlainText() == "") {
        return true; // Don't prompt the user if they haven't done anything to a new file
    }

    QMessageBox box;
    box.setText("You have unsaved changes which may be lost.");
    box.setInformativeText("Save your changes?");
    box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Save);
    int button = box.exec();
    switch(button) {
    case QMessageBox::Save:
        // save file and continue dangerous action
        this->saveFileAs();
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
        // Don't do it if you don't know what they said
        return false;
    }
}

void MainWindow::runCode() {

    if(!this->saveFile())
        return;

    QGraphicsScene *tempScene = new QGraphicsScene(this);
    this->scene = tempScene;
    if(r != NULL)
        delete r;

    ui->cancelButton->setVisible(true);
    ui->runButton->setDisabled(true);
    ui->mediaBar->setVisible(false);
    fpsTimer.stop();
    r = new AsyncRendQt(ui->output->width(), ui->output->height(), ui->framesBox->value(), this);
    connect(r, SIGNAL(done()), this, SLOT(doneRender()));
    connect(r, SIGNAL(aborted()), this, SLOT(abortRender()));
    connect(r, SIGNAL(updateRect()), this, SLOT(updateRect()));

    //qDebug() << ui->output->items() << endl;
}

void MainWindow::openFile() {
    qDebug() << "Open file";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("CFDG file (*.cfdg);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QDir::setCurrent(QFileInfo( QFile(fileName) ).dir().path());

        this->setWindowTitle(fileName.remove(0, fileName.lastIndexOf("/")+1) + " - ContextFree");
        this->currentFile = fileName;

        QString file = readFileFromDisk(fileName);

        if (!file.isNull()) {
            ui->code->document()->clearUndoRedoStacks();
            ui->code->document()->setPlainText(file);
        }
    }
}

bool MainWindow::saveFile() {
    if(this->currentFile.isEmpty())
        return this->saveFileAs();
    else
        return writeFileToDisk(this->currentFile, ui->code->document()->toPlainText());
}

bool MainWindow::saveFileAs() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("CFDG file (*.cfdg);;All Files (*)"));

    if (fileName.isNull()) // User selected "Cancel"
        return false;
    else {
        this->currentFile = fileName;
        QDir::setCurrent(QFileInfo( QFile(fileName) ).dir().path());
        this->setWindowTitle(fileName.remove(0, fileName.lastIndexOf("/")+1) + " - ContextFree");
        return writeFileToDisk(fileName, ui->code->document()->toPlainText());
    }
}

void MainWindow::newFile() {
    ui->code->document()->clearUndoRedoStacks();
    ui->code->document()->setPlainText("");
    this->currentFile = "";
    this->setWindowTitle("New Document - ContextFree");
}
// Can't be export, because that's a keyword
void MainWindow::exportFile() {
    int frames = ui->framesBox->value();

    if(!this->saveFile())
        return;

    // Only supports png/svg for now
    QFileDialog dialog(this);

#ifdef QUICKTIME
    dialog.setNameFilter(tr("PNG Image (*.png);;SVG Image (*.svg);;QuickTime file (*.mov)"));
#else /* QUICKTIME */
    dialog.setNameFilter(tr("PNG Image (*.png);;SVG Image (*.svg)"));
#endif
    dialog.setWindowTitle(tr("Export file"));

    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QString *filter = new QString("PNG Image (*.png)");

    connect(&dialog, &QFileDialog::filterSelected, [&filter] (const QString &newFilter) {
        delete filter;
        filter = new QString(newFilter);
        qDebug() << "Filter sel:" << newFilter.toStdString().c_str();
    });

    dialog.setFileMode(QFileDialog::AnyFile);

    if(!dialog.exec())
        return;

    string fname = dialog.selectedFiles()[0].toStdString();

    std::map<QString, exfmt::ExFmt> exporters;
    exporters.emplace(std::make_pair(tr("SVG Image (*.svg)"), exfmt::svg));
    exporters.emplace(std::make_pair(tr("PNG Image (*.png)"), exfmt::png));
#ifdef QUICKTIME
    exporters.emplace(std::make_pair(tr("QuickTime file (*.mov)"), exfmt::qtime));
#endif /* QUICKTIME */
    AsyncRendGeneric r(frames, 1920, 1080, this, this->currentFile.toStdString(), fname.c_str(), exporters[*filter]);

    delete filter;
}

void MainWindow::openFileAction() {
    if(!confirmDangerAction())
        return;
    this->openFile();
}

void MainWindow::saveFileAction() {
    this->saveFile();
}

void MainWindow::saveFileAsAction() {
    this->saveFileAs();
}

void MainWindow::newFileAction() {
    if(!confirmDangerAction())
        return;
    this->newFile();
}

void MainWindow::exportFileAction() {
    qDebug() << "Export clicked!";
    this->exportFile();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    confirmDangerAction() ? event->accept() : event->ignore();
}

void MainWindow::showPrefs() {
    qDebug() << "Showing preferences";
    SettingsDialog s;

    if(s.exec()) {
        QSettings s("contextfreeart.org", "ContextFree");
        fpsTimer.setInterval(1000.0 / s.value("output_fps").toInt());
    }
}

void MainWindow::doneRender() {
    qDebug() << "Done rendering";

    ui->cancelButton->setVisible(false);
    ui->runButton->setEnabled(true);
    if(r->getScenes().size() > 1) {
        ui->mediaBar->setVisible(true);
    }
    QGraphicsScene *temp = scene;
    r->frameIndex = 0;
    scene = r->getScenes()[0].get();
    ui->output->setScene(scene);
    ui->playhead->setMaximum(r->frameCount());
    delete temp;
}

void MainWindow::stop() {
    r->cleanup();
}

void MainWindow::abortRender() {
    qDebug() << "Aborted rendering";

    if(r != NULL) {
        delete r;
        r = NULL;
    }
    ui->cancelButton->setVisible(false);
    ui->runButton->setEnabled(true);
    ui->runButton->setText("Build");
}

void MainWindow::showmsg(const char* msg) {
    //ui->statusBar->showMessage(msg, 1000);
    delete msg;
}

void MainWindow::updateRect() {
    QRectF ibr = scene->itemsBoundingRect();
    ui->output->setSceneRect(ibr);
    scene->setSceneRect(ibr);
}

void MainWindow::startPlayback(bool shouldPlay) {
    if(shouldPlay)
        fpsTimer.start();
    else
        fpsTimer.stop();
}

void MainWindow::incFrame() {
    vector<unique_ptr<QGraphicsScene> > &scenes = r->getScenes();
    if(++(r->frameIndex) < scenes.size()) {
        scene = scenes[r->frameIndex].get();
        ui->output->setScene(scene);
        ui->playhead->setValue(r->frameIndex);
        qDebug() << "Show frame " << r->frameIndex << " of " << r->frameCount();
    } else
        fpsTimer.stop();
}

void MainWindow::setFrame(int frame) {
    vector<unique_ptr<QGraphicsScene> > &scenes = r->getScenes();
    if(frame < scenes.size()) {
        r->frameIndex = frame;
        scene = scenes[r->frameIndex].get();
        ui->output->setScene(scene);
    }
}
