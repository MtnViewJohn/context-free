#ifndef QTSYSTEM_H
#define QTSYSTEM_H
#include <cfdg.h>
#include <string>
#include <iostream>

class QtSystem : public PosixSystem
{
    public:
        void message(const char* fmt) override;
        void syntaxError(const CfdgError &err) override;
        bool error(bool errorOccurred) override;
        void catastrophicError(const char *what) override;
};

#endif // QTSYSTEM_H
