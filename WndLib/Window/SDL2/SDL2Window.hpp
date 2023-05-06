#pragma once

#include <iostream>

#include <sdl/SDL.h>

#include <WndLib/Window/WindowAbstract.hpp>
#include <WndLib/Window/SDL2/Translator/SDL2EventTranslator.hpp>

namespace wnd {
	class SDL2Window : public Window
	{
	private:
		inline static bool sdl_initialized = false;

		SDL_Window* sdl_window = nullptr;

		event::Observer<event::WindowEvent>* close_event_observer;
		event::Observer<event::WindowQuitEvent>* quit_event_observer;

		bool open = false;

		int init_SDL()
		{
			int status = SDL_Init(SDL_INIT_EVERYTHING);
			if (status < 0) {
				return status;
			}
			if (!sdl_initialized) {
				sdl_initialized = true;
				std::cout << "SDL successfully initialized." << std::endl;
			}
			open = true;
			return 1;
		}

		void destroy_window()
		{
			if (open) {
				open = false;

				SDL_DestroyWindow(sdl_window);

				delete close_event_observer;
				delete quit_event_observer;

				std::cout << "SDL window destroyed." << std::endl;
			}
		}
	public:
		SDL2Window()
		{
			init_SDL();
		}
		SDL2Window(
			const char* title,
			int w = 1280,
			int h = 720,
			int x = SDL_WINDOWPOS_CENTERED,
			int y = SDL_WINDOWPOS_CENTERED,
			Uint32 flags = 0)
		{
			init_SDL();
			create_window(title, x, y, w, h, flags);
		}

		SDL2Window(const SDL2Window&) = delete;
		~SDL2Window()
		{
			destroy_window();
		}

		SDL2Window& operator=(const SDL2Window& other) = delete;
	
		void create_window(const char* title, int w, int h, int x, int y, Uint32 flags)
		{
			sdl_window = SDL_CreateWindow(
				title,
				x, y,
				w, h,
				flags);

			if (!sdl_window) {
				std::cout << "SDL window failed to be created [error: " << SDL_GetError() << "]" << std::endl;
			}
			else {
				std::cout << "SDL window successfully created." << std::endl;
			}

			event::WindowEventManager& manager = event::WindowEventManager::get_instance();

			close_event_observer = manager.window_event.create_observer([&](const event::WindowEvent e) {
				if (e.type == event::WindowEventType::CLOSE) {
					if (e.window_ptr == this) {
						destroy_window();
					}
				}
			});

			quit_event_observer = manager.window_quit_event.create_observer([&](const event::WindowQuitEvent e) {
				SDL_Quit();
			});

		}
		void create_window(const char* title, int w, int h, int x, int y)
		{
			create_window(title, w, h, x, y, 0);
		}
		void poll_events()
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				SDL_GetWindowID(sdl_window);
				if (e.type == SDL_QUIT) {
					destroy_window();
				}
				SDL2EventTranslator::get_instance().translate(this, e);
			}
		}
		void swap()
		{
			SDL_GL_SwapWindow(sdl_window);
		}

		void enable_setting(Setting setting) {

		}

		int get_width()
		{
			int w;
			int h;
			SDL_GetWindowSize(sdl_window, &w, &h);
			return w;
		}
		int get_height()
		{
			int w;
			int h;
			SDL_GetWindowSize(sdl_window, &w, &h);
			return h;
		}

		std::string get_title()
		{
			return SDL_GetWindowTitle(sdl_window);
		}
		void set_title(std::string title)
		{
			SDL_SetWindowTitle(sdl_window, title.c_str());
		}

		Uint32 get_flags()
		{
			return SDL_GetWindowFlags(sdl_window);
		}

		void* get_window_ptr()
		{
			return sdl_window;
		}

		bool is_open()
		{
			return open;
		}
	};
}