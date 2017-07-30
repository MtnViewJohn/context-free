#include "qtsystem.h"
#include <cstdarg>
#include <string>
#include <fstream>
#include <QThread>
#include <QMessageBox>
#include <QStatusBar>

QtSystem::QtSystem(QStatusBar *sb): sb(sb) {
}


void QtSystem::message(const char *fmt, ...) {
    va_list args;
    char *msg = new char[500];
    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    emit showmsg(msg);
}

void QtSystem::syntaxError(const CfdgError &err) {
    QMessageBox::warning(nullptr, "Syntax Error", (std::string(err.what()) + " at " + std::to_string(err.where.begin.line) + ":" + std::to_string(err.where.begin.column)).c_str());
}

void QtSystem::catastrophicError(const char *what) {
    QMessageBox::critical(nullptr, "Catastrophic Error", what);
}

std::istream *QtSystem::openFileForRead(const std::string &path) {
    return new std::ifstream(path);
}
