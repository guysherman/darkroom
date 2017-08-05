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
#include <Rocket/Core/Core.h>

// GTK Headers


// Our Headers
#include "SystemInterfaceGLFW.h"


namespace darkroom
{
	
	RocketGLFWSystemInterface::RocketGLFWSystemInterface()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	RocketGLFWSystemInterface::~RocketGLFWSystemInterface()
	{

	}

	Rocket::Core::Input::KeyIdentifier RocketGLFWSystemInterface::TranslateKey(int key)
	{
		switch(key)
		{
		case GLFW_KEY_A:
			return Rocket::Core::Input::KI_A;
			break;
		case GLFW_KEY_B:
			return Rocket::Core::Input::KI_B;
			break;
		case GLFW_KEY_C:
			return Rocket::Core::Input::KI_C;
			break;
		case GLFW_KEY_D:
			return Rocket::Core::Input::KI_D;
			break;
		case GLFW_KEY_E:
			return Rocket::Core::Input::KI_E;
			break;
		case GLFW_KEY_F:
			return Rocket::Core::Input::KI_F;
			break;
		case GLFW_KEY_G:
			return Rocket::Core::Input::KI_G;
			break;
		case GLFW_KEY_H:
			return Rocket::Core::Input::KI_H;
			break;
		case GLFW_KEY_I:
			return Rocket::Core::Input::KI_I;
			break;
		case GLFW_KEY_J:
			return Rocket::Core::Input::KI_J;
			break;
		case GLFW_KEY_K:
			return Rocket::Core::Input::KI_K;
			break;
		case GLFW_KEY_L:
			return Rocket::Core::Input::KI_L;
			break;
		case GLFW_KEY_M:
			return Rocket::Core::Input::KI_M;
			break;
		case GLFW_KEY_N:
			return Rocket::Core::Input::KI_N;
			break;
		case GLFW_KEY_O:
			return Rocket::Core::Input::KI_O;
			break;
		case GLFW_KEY_P:
			return Rocket::Core::Input::KI_P;
			break;
		case GLFW_KEY_Q:
			return Rocket::Core::Input::KI_Q;
			break;
		case GLFW_KEY_R:
			return Rocket::Core::Input::KI_R;
			break;
		case GLFW_KEY_S:
			return Rocket::Core::Input::KI_S;
			break;
		case GLFW_KEY_T:
			return Rocket::Core::Input::KI_T;
			break;
		case GLFW_KEY_U:
			return Rocket::Core::Input::KI_U;
			break;
		case GLFW_KEY_V:
			return Rocket::Core::Input::KI_V;
			break;
		case GLFW_KEY_W:
			return Rocket::Core::Input::KI_W;
			break;
		case GLFW_KEY_X:
			return Rocket::Core::Input::KI_X;
			break;
		case GLFW_KEY_Y:
			return Rocket::Core::Input::KI_Y;
			break;
		case GLFW_KEY_Z:
			return Rocket::Core::Input::KI_Z;
			break;
		case GLFW_KEY_0:
			return Rocket::Core::Input::KI_0;
			break;
		case GLFW_KEY_1:
			return Rocket::Core::Input::KI_1;
			break;
		case GLFW_KEY_2:
			return Rocket::Core::Input::KI_2;
			break;
		case GLFW_KEY_3:
			return Rocket::Core::Input::KI_3;
			break;
		case GLFW_KEY_4:
			return Rocket::Core::Input::KI_4;
			break;
		case GLFW_KEY_5:
			return Rocket::Core::Input::KI_5;
			break;
		case GLFW_KEY_6:
			return Rocket::Core::Input::KI_6;
			break;
		case GLFW_KEY_7:
			return Rocket::Core::Input::KI_7;
			break;
		case GLFW_KEY_8:
			return Rocket::Core::Input::KI_8;
			break;
		case GLFW_KEY_9:
			return Rocket::Core::Input::KI_9;
			break;
		case GLFW_KEY_KP_0:
			return Rocket::Core::Input::KI_NUMPAD0;
			break;
		case GLFW_KEY_KP_1:
			return Rocket::Core::Input::KI_NUMPAD1;
			break;
		case GLFW_KEY_KP_2:
			return Rocket::Core::Input::KI_NUMPAD2;
			break;
		case GLFW_KEY_KP_3:
			return Rocket::Core::Input::KI_NUMPAD3;
			break;
		case GLFW_KEY_KP_4:
			return Rocket::Core::Input::KI_NUMPAD4;
			break;
		case GLFW_KEY_KP_5:
			return Rocket::Core::Input::KI_NUMPAD5;
			break;
		case GLFW_KEY_KP_6:
			return Rocket::Core::Input::KI_NUMPAD6;
			break;
		case GLFW_KEY_KP_7:
			return Rocket::Core::Input::KI_NUMPAD7;
			break;
		case GLFW_KEY_KP_8:
			return Rocket::Core::Input::KI_NUMPAD8;
			break;
		case GLFW_KEY_KP_9:
			return Rocket::Core::Input::KI_NUMPAD9;
			break;
		case GLFW_KEY_LEFT:
			return Rocket::Core::Input::KI_LEFT;
			break;
		case GLFW_KEY_RIGHT:
			return Rocket::Core::Input::KI_RIGHT;
			break;
		case GLFW_KEY_UP:
			return Rocket::Core::Input::KI_UP;
			break;
		case GLFW_KEY_DOWN:
			return Rocket::Core::Input::KI_DOWN;
			break;
		case GLFW_KEY_KP_ADD:
			return Rocket::Core::Input::KI_ADD;
			break;
		case GLFW_KEY_BACKSPACE:
			return Rocket::Core::Input::KI_BACK;
			break;
		case GLFW_KEY_DELETE:
			return Rocket::Core::Input::KI_DELETE;
			break;
		case GLFW_KEY_KP_DIVIDE:
			return Rocket::Core::Input::KI_DIVIDE;
			break;
		case GLFW_KEY_END:
			return Rocket::Core::Input::KI_END;
			break;
		case GLFW_KEY_ESCAPE:
			return Rocket::Core::Input::KI_ESCAPE;
			break;
		case GLFW_KEY_F1:
			return Rocket::Core::Input::KI_F1;
			break;
		case GLFW_KEY_F2:
			return Rocket::Core::Input::KI_F2;
			break;
		case GLFW_KEY_F3:
			return Rocket::Core::Input::KI_F3;
			break;
		case GLFW_KEY_F4:
			return Rocket::Core::Input::KI_F4;
			break;
		case GLFW_KEY_F5:
			return Rocket::Core::Input::KI_F5;
			break;
		case GLFW_KEY_F6:
			return Rocket::Core::Input::KI_F6;
			break;
		case GLFW_KEY_F7:
			return Rocket::Core::Input::KI_F7;
			break;
		case GLFW_KEY_F8:
			return Rocket::Core::Input::KI_F8;
			break;
		case GLFW_KEY_F9:
			return Rocket::Core::Input::KI_F9;
			break;
		case GLFW_KEY_F10:
			return Rocket::Core::Input::KI_F10;
			break;
		case GLFW_KEY_F11:
			return Rocket::Core::Input::KI_F11;
			break;
		case GLFW_KEY_F12:
			return Rocket::Core::Input::KI_F12;
			break;
		case GLFW_KEY_F13:
			return Rocket::Core::Input::KI_F13;
			break;
		case GLFW_KEY_F14:
			return Rocket::Core::Input::KI_F14;
			break;
		case GLFW_KEY_F15:
			return Rocket::Core::Input::KI_F15;
			break;
		case GLFW_KEY_HOME:
			return Rocket::Core::Input::KI_HOME;
			break;
		case GLFW_KEY_INSERT:
			return Rocket::Core::Input::KI_INSERT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			return Rocket::Core::Input::KI_LCONTROL;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			return Rocket::Core::Input::KI_LSHIFT;
			break;
		case GLFW_KEY_KP_MULTIPLY:
			return Rocket::Core::Input::KI_MULTIPLY;
			break;
		case GLFW_KEY_PAUSE:
			return Rocket::Core::Input::KI_PAUSE;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			return Rocket::Core::Input::KI_RCONTROL;
			break;
		case GLFW_KEY_ENTER:
			return Rocket::Core::Input::KI_RETURN;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			return Rocket::Core::Input::KI_RSHIFT;
			break;
		case GLFW_KEY_SPACE:
			return Rocket::Core::Input::KI_SPACE;
			break;
		case GLFW_KEY_MINUS:
			return Rocket::Core::Input::KI_SUBTRACT;
			break;
		case GLFW_KEY_TAB:
			return Rocket::Core::Input::KI_TAB;
			break;
		};

		return Rocket::Core::Input::KI_UNKNOWN;
	}

	int RocketGLFWSystemInterface::GetKeyModifiers(GLFWwindow *window)
	{
		int mods = 0;
		int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_SHIFT;
		}

		state = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_SHIFT;
		}

		state = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_CTRL;
		}

		state = glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_CTRL;
		}

		state = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_ALT;
		}

		state = glfwGetKey(window, GLFW_KEY_RIGHT_ALT);
		if (state == GLFW_PRESS)
		{
			mods |= Rocket::Core::Input::KM_ALT;
		}

		return mods;
	}

	float RocketGLFWSystemInterface::GetElapsedTime()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - startTime);
		return time_span.count();
	}

	bool RocketGLFWSystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
	{
		std::string Type;

		switch(type)
		{
		case Rocket::Core::Log::LT_ALWAYS:
			Type = "[Always]";
			break;
		case Rocket::Core::Log::LT_ERROR:
			Type = "[Error]";
			break;
		case Rocket::Core::Log::LT_ASSERT:
			Type = "[Assert]";
			break;
		case Rocket::Core::Log::LT_WARNING:
			Type = "[Warning]";
			break;
		case Rocket::Core::Log::LT_INFO:
			Type = "[Info]";
			break;
		case Rocket::Core::Log::LT_DEBUG:
			Type = "[Debug]";
			break;
		default:
			Type = "[Other]";
			break;

		};

		printf("%s - %s\n", Type.c_str(), message.CString());

		return true;

	}
}
