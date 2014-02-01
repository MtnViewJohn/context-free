// posixTimer.cpp
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

#include "cfdg.h"
#include <sys/time.h>
#include <signal.h>
#include <memory>

static std::weak_ptr<Renderer> gRenderer;

void
statusTimer(int signal)
{
  if (auto runningRenderer = gRenderer.lock())
      runningRenderer->requestUpdate = true;
}

void
setupTimer(std::shared_ptr<Renderer>& renderer)
{
    gRenderer = renderer;

    struct sigaction doit;
    doit.sa_handler = statusTimer;
    sigemptyset(&doit.sa_mask);
    doit.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &doit, 0);

    itimerval period;
    period.it_interval.tv_sec = 0;
    period.it_interval.tv_usec = 250000;  // 1/4 second
    period.it_value = period.it_interval;
    setitimer(ITIMER_REAL, &period, 0);
}

void
cleanupTimer()
{
    itimerval period;
    period.it_interval.tv_sec = 0;
    period.it_interval.tv_usec = 0;
    period.it_value = period.it_interval;
    setitimer(ITIMER_REAL, &period, 0);
}



