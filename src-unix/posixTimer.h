#pragma once
#include <memory>

class Renderer;

class PosixTimer
{
public:
    PosixTimer();
    ~PosixTimer();

    void Stop();
    void Start(std::shared_ptr<Renderer>& renderer);

    static std::weak_ptr<Renderer> gRenderer;
};
