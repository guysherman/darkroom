#ifndef __SYSTEMINTERFACEGLFW_H__
#define __SYSTEMINTERFACEGLFW_H__
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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// C++ Standard Headers
#include <chrono>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>


// GTK Headers


// Our Headers



namespace darkroom
{

	class RocketGLFWSystemInterface : public Rocket::Core::SystemInterface
	{
	public:
		RocketGLFWSystemInterface();
		virtual ~RocketGLFWSystemInterface();
		Rocket::Core::Input::KeyIdentifier TranslateKey(int key);
		int GetKeyModifiers(GLFWwindow *window);
		float GetElapsedTime();
		bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

	private:
		std::chrono::high_resolution_clock::time_point startTime; 
	};
}

#endif // __SYSTEMINTERFACEGLFW_H__