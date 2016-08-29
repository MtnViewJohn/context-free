// version.h
// Context Free
// ---------------------
// Copyright (C) 2008 John Horigan
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

#ifndef INCLUDE_VERSION_H
#define INCLUDE_VERSION_H

const char* APP_NAME(const char* argv0);
const char* APP_VERSION();
int APP_BUILD();
const char* APP_OPTCHAR();
const char* APP_OPTLONG();
const char* APP_OPTSEP();
      char  APP_DIRCHAR();

#endif //INCLUDE_VERSION_H
