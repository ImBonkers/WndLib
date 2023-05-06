#pragma once

#include "../WindowAbstract.hpp"
#include "SDL2Window.hpp"
#include "SDL2GLWindow.hpp"

namespace wnd {
	class SDL2Factory : public WindowFactory
	{
	public:
		Window* create_window(const char* title, int width, int height, int x, int y) {
			return new SDL2Window(title, width, height);
		}
		Window* create_gl_window(const char* title, int width, int height, int x, int y) {
			return new SDL2GLWindow(title, width, height);
		}
		Window* create_vulkan_window(const char* title, int width, int height, int x, int y) {
			return nullptr;
		}
		Window* create_d3d_window(const char* title, int width, int height, int x, int y) {
			return nullptr;
		}
	};
}