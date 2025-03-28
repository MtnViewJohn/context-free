#pragma once

#include "RenderParams.h"
#include "EditorParams.h"

class Settings : public RenderParameters, public EditorParams
{
public:
    Settings();
    static void Load();
    static void Save(bool justme = false);
    static void Modify(int& param, int v);
    static void Modify(bool& param, bool v);

    enum class LaunchActions { NoDocument, NewDocument, Welcome };

    static LaunchActions AtLaunch;
    static bool RenderOnOpen;
    static int EditorWidth;
    static int WindowWidth;
    static int WindowHeight;
};

