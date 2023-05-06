#pragma once

#include <iostream>

#include "Window/WindowAbstract.hpp"

// SDL2
#ifdef SDL_h_
#include "Window/SDL2/SDL2Factory.hpp"
#endif

#ifdef _glfw3_h_
#include "Window/GLFW/GLFWFactory.hpp"
#endif

#ifdef _WX_WX_H_
#include "Window/WX/WXFactory.hpp"
#endif

#ifdef _WX_WX_H_
#include "Window/WX/WXFactory.hpp"
#endif

namespace wnd {
	class WindowCreator {
	private:
		WindowFactory* factory;
		WindowType w_type;
		GfxAPI g_api;

	public:
		WindowCreator(WindowType type, GfxAPI api)
		:	w_type(type), g_api(api)
		{
			factory = nullptr;
			switch (type) {
			case wnd::WindowType::SDL:
			{
#ifdef SDL_h_
				factory = new SDL2Factory();
#else
				std::cout << "SDL2 is not properly included." << std::endl;
#endif
			}; break;
			case wnd::WindowType::GLFW:
			{
#ifdef _glfw3_h_
				factory = new GLFWFactory();
#else
				std::cout << "GLFW is not properly included." << std::endl;
#endif
			}; break;
			case wnd::WindowType::WX:
			{
#ifdef _WX_WX_H_
				factory = new WXFactory();
#else
				std::cout << "WXWidgets is not properly included." << std::endl;
#endif
			}; break;
			case wnd::WindowType::QT:
			{
				factory = nullptr;
			}; break;
			default:
			{
				factory = nullptr;
			}; break;
			}
		}

		Window* create_window(const char* title = "Window", int width = 1280, int height = 720, int x = 0, int y = 0) {
			
			Window* window;
			switch (g_api) {
			case wnd::GfxAPI::NONE:
			{
				window = factory->create_window(title, width, height, x, y);
			}break;
			case wnd::GfxAPI::OPENGL:
				window = factory->create_gl_window(title, width, height, x, y); break;
			case wnd::GfxAPI::VULKAN:
				window = factory->create_vulkan_window(title, width, height, x, y); break;
			case wnd::GfxAPI::D3D:
				window = factory->create_d3d_window(title, width, height, x, y); break;
			default:
				window = nullptr; break;
			}

			return window;
		}
	};
}