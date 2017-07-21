#ifndef QTSYSTEM_H
#define QTSYSTEM_H
#include <posixSystem.h>
class QtSystem: public PosixSystem {
    public:
        QtSystem();
        void message(const char* fmt, ...) override;
        void syntaxError(const CfdgError &err) override;
        void catastrophicError(const char* what) override;
};

#endif // QTSYSTEM_H
