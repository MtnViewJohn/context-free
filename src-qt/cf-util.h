#ifndef CFUTIL_H
#define CFUTIL_H

#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static MainWindow w;

inline void gerr(const QString &errmsg, MainWindow *w = nullptr, const bool &shouldTerminate = false) {
    QMessageBox box;
    box.setStandardButtons(QMessageBox::Ok);
    if (shouldTerminate){
        box.setText("Fatal error (your current document will be saved to cfdg.err.XX)");
        box.setInformativeText(errmsg);
        box.setIcon(QMessageBox::Critical);
        box.exec();
        cerr << "Saving document..." << endl;
        int name_suf = 0;
        while(true) {
            if (FILE *file = fopen(("cfdg.err." + to_string(name_suf)).c_str(), "r")) {
                fclose(file);
                name_suf++;
            } else {
                fclose(file);
                break;
            }
        }
        ofstream bak ("cfdg.err." + to_string(name_suf));
        if(bak.is_open()) {
            bak << w->ui->code->toPlainText().toStdString();
            bak.close();
            cerr << "Successfully wrote backup file" << endl;
        } else {
            cerr << "CRITICAL: Couldn't open backup file; hope you saved recently" << endl;
        }
        exit(-1);
    } else {
        box.setText("Error (it's ok, we'll keep running)");
        box.setInformativeText(errmsg);
        box.setIcon(QMessageBox::Warning);
    }
}


#endif // CFUTIL_H
