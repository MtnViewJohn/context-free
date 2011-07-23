*** Context Free
*** version 2.2

    by Chris Coyne, John Horigan and Mark Lentczner

    Context Free Copyright 2005-2008 Mark Lentczner and John Horigan
    CFDG Copyright 2005 Chris Coyne
	Anti-Grain Geometry library Copyright 2002-2005 Maxim Shemanarev

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
DISTRIBUTION & LICENSE

Context Free is released under the GNU license.  

Context Free is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
GENERAL NOTES


~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
FILE TREE

./              - top level: this file, license, Makefile,
                  Xcode project and Windows CLI solution
./input/        - sample input files
./src-agg/      - a subset of the Anti_Grain Geometry sources
./src-common/   - the CFDG engine
./src-net/	- Windows .Net specific sources
./src-osx/      - Mac specific sources
./src-unix/     - Unix/Posix specific sources 
./src-win/      - Windows specific sources
./src-win/derived   - pre-built output from flex and yacc for folks that
                      don't have those tools available

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
MACINTOSH BUILD NOTES

Requires Xcode 1.5 & Mac OS X 10.3 (Panther).
Developed with XCode 3.0 and Mac OS X 10.5 (Leopard), has not been tested with older versions of XCode or Mac OS X.

The Xcode project file is in the top directory:
    ./Context Free.xcodeproj


~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
WINDOWS GUI BUILD NOTES

Requires Visual Studio 2005 or later.

The VS2005 solution file is at ./src-net/ContextFreeNet.sln


~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
WINDOWS CLI (command line) BUILD NOTES

Requires Visual Studio 2005 or Visual C++ 2005 Express edition,  or later.

The CLI solution file is at ./ContextFreeCLI.sln

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
BSD/LINUX/UNIX/POSIX BUILD NOTES

You'll need a c++ compiler, flex (not lex), bison (newer yacc works too)
and the libpng Library. Most of this should be installed or easily
available on any modern operating system distribution.  If you need it,
libpng can be found here:
    http://libpng.org/pub/png/libpng.html    

From the top level, you should just run:
    $ make

You'll see a warning about "mktemp" and "mkstemp" during the link step.
This can be ignored for now.

To run the program, try something like:
    $ ./cfdg -s 500 input/mtree.cfdg mtree.png

Run it with -? to get a usage summary:
    $ ./cfdg -?


