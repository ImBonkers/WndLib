#pragma once

#include "../WindowAbstract.hpp"
#include "GLFWWindow.hpp"
#include "GLFWGLWindow.hpp"

namespace wnd {
	class GLFWFactory : public WindowFactory
	{
	public:
		Window* create_window(const char* title, int width, int height, int x, int y) {
			return new GLFWWindow(title, width, height);
		}
		Window* create_gl_window(const char* title, int width, int height, int x, int y) {
			return new GLFWGLWindow(title, width, height);
		}
		Window* create_vulkan_window(const char* title, int width, int height, int x, int y) {
			return nullptr;
		}
		Window* create_d3d_window(const char* title, int width, int height, int x, int y) {
			return nullptr;
		}
	};
}