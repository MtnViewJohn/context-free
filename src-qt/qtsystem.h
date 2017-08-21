#ifndef QTSYSTEM_H
#define QTSYSTEM_H
#include <posixSystem.h>
#include <fstream>
#include <string>
#include <QStatusBar>
class QtSystem: public QObject, public PosixSystem {
        Q_OBJECT

    public:
        QtSystem();
        void message(const char* fmt, ...) override;
        void syntaxError(const CfdgError &err) override;
        void catastrophicError(const char* what) override;
        std::istream *openFileForRead(const std::string &path) override;
        void orphan() override {}
    signals:
        void showmsg(const char *msg);
};

#endif // QTSYSTEM_H
