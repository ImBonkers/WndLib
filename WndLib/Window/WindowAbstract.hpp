#pragma once

#include "../Event/EventTranslator.hpp"

namespace wnd {
	enum class WindowType {
		SDL,
		GLFW,
		WX,
		QT
	};

	enum class GfxAPI {
		NONE,
		OPENGL,
		VULKAN,
		D3D
	};

	enum class Setting {
		NONE,
	};

	class Window
	{
	public:
		virtual void create_window(const char* title, int w, int h, int x, int y) = 0;
		virtual void poll_events() = 0;
		virtual void swap() = 0;

		virtual void enable_setting(Setting setting) = 0;

		virtual int get_width() = 0;
		virtual int get_height() = 0;

		virtual void* get_window_ptr() = 0;

		virtual bool is_open() = 0;
	};

	class WindowFactory
	{
	public:
		virtual Window* create_window(const char* title, int width, int height, int x, int y) = 0;
		virtual Window* create_gl_window(const char* title, int width, int height, int x, int y) = 0;
		virtual Window* create_vulkan_window(const char* title, int width, int height, int x, int y) = 0;
		virtual Window* create_d3d_window(const char* title, int width, int height, int x, int y) = 0;
	};
}