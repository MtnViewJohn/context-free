#include "qtsystem.h"
#include <cstdarg>
#include <QMessageBox>

QtSystem::QtSystem() {
}

void QtSystem::message(const char *fmt, ...) {
    va_list args;
    char *msg = new char[100];
    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    QMessageBox::information(nullptr, "Message", msg);
}

void QtSystem::syntaxError(const CfdgError &err) {
}
