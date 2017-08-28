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
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <tga.h>

// GTK Headers


// Our Headers
#include "TgaImage.h"
#include "File.h"


namespace darkroom
{
	TgaImage::TgaImage(std::string filename) : image(nullptr)
	{
		memset(&data, '\0', sizeof(TGAData));
		auto fileData = File::ReadAllBytes(filename);
		FILE *fd = fmemopen(&fileData[0], fileData.size(), "rb");
		image = TGAOpenFd(fd);

		data.flags = TGA_IMAGE_DATA | TGA_IMAGE_INFO | TGA_RGB;
		int result = TGAReadImage(image, &data);
		if (TGA_OK != result)
		{
			TGAClose(image);
			image = nullptr;
		}

		
	}

	TgaImage::TgaImage(std::vector<unsigned char> fileData) : image(nullptr)
	{
		memset(&data, '\0', sizeof(TGAData));
		FILE *fd = fmemopen(&fileData[0], fileData.size(), "rb");
		image = TGAOpenFd(fd);

		data.flags = TGA_IMAGE_DATA | TGA_IMAGE_INFO | TGA_RGB;
		int result = TGAReadImage(image, &data);
		if (TGA_OK != result)
		{
			TGAClose(image);
			image = nullptr;
		}
	}

	TgaImage::~TgaImage()
	{
		if (image)
		{
			TGAClose(image);
		}
	}

	const unsigned char *TgaImage::GetData() const
	{
		if (image && image->hdr.depth == 32 && image->hdr.alpha == 8) 
		{
			return data.img_data;
		}
		
		return nullptr;
	}

	
	int TgaImage::GetWidth() const
	{
		if (image && image->hdr.depth == 32 && image->hdr.alpha == 8) 
		{
			return image->hdr.width;
		}

		return 0;
	}

	int TgaImage::GetHeight() const
	{
		if (image && image->hdr.depth == 32 && image->hdr.alpha == 8) 
		{
			return image->hdr.height;
		}

		return 0;
	}

	unsigned char TgaImage::GetVerticalOrientation() const
	{
		
		return image->hdr.vert;

	}
}
