#pragma once
#include <memory>

class Renderer;

class WinTimer
{

private:
    HANDLE m_timerHandle = NULL;
    std::weak_ptr<Renderer> gRenderer;

    static void CALLBACK TimerProc(void* InstancePointer, BOOLEAN TimerOrWaitFired);
    void timerProc(BOOLEAN TimerOrWaitFired);

public:

    WinTimer();
    ~WinTimer();

    void Stop();
    void Start(std::shared_ptr<Renderer>& renderer);

};
