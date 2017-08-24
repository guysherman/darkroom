#ifndef __PNGUTILS_H__
#define __PNGUTILS_H__
/*
	Darkroom is an open-source photography tool.
	Copyright (C) 2017  Guy Sherman

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	Contact the author via https://github.com/guysherman
*/


// C++ Standard Headers


// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers



// This function actually writes out the PNG image file. The string 'title' is
// also written into the image file
int writeImage(const char* filename, int width, int height, const unsigned char *buffer, const char* title);


#endif // __PNGUTILS_H__