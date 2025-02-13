#pragma once
#include <memory>

class Renderer;

void setupTimer(std::shared_ptr<Renderer>& renderer);
void cleanupTimer();
