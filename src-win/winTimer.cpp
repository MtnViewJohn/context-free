// winTimer.cpp
// Context Free
// ---------------------
// Copyright (C) 2008-2014 John Horigan
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#define _WIN32_WINNT 0x0500
#define NOMINMAX 1
#include <Windows.h>
#include "cfdg.h"
#include <memory>

static std::weak_ptr<Renderer> gRenderer;

VOID CALLBACK 
statusTimer(PVOID, BOOLEAN)
{
    if (auto runningRenderer = gRenderer.lock())
        runningRenderer->requestUpdate = true;
}

HANDLE timerQueueTimer = NULL;

void
setupTimer(std::shared_ptr<Renderer>& renderer)
{
    gRenderer = renderer;
    if (renderer) {
        CreateTimerQueueTimer(&timerQueueTimer, NULL, statusTimer, 
            nullptr, 250, 250, WT_EXECUTEINTIMERTHREAD);
    }
}

void
cleanupTimer()
{
    if (timerQueueTimer) {
        DeleteTimerQueueTimer(NULL, timerQueueTimer, INVALID_HANDLE_VALUE);
    }
}
