#pragma once

#include <glad/glad.h>
#include <sdl/SDL.h>

#include <WndLib/Window/WindowAbstract.hpp>
#include <WndLib/Window/OpenGLLoader.hpp>

#include "SDL2Window.hpp"

namespace wnd {
	class SDL2GLWindow : public SDL2Window
	{
	private:
		inline static bool opengl_initialized = false;
		SDL_GLContext context;

		int init_openGL()
		{
			if (opengl_initialized) {
				return 1;
			}

			OpenGLLoader loader;
			int success = loader.load_opengl(SDL_GL_GetProcAddress);
			if (!success) {
				return success;
			}
			else {
				opengl_initialized = true;
			}

			SDL_GL_SetSwapInterval(1);

			return 1;
		}
		void create_context()
		{
			context = SDL_GL_CreateContext((SDL_Window*)get_window_ptr());
		}
	public:
		SDL2GLWindow() = delete;
		SDL2GLWindow(const char* title,
			int w = 1280,
			int h = 720,
			int x = SDL_WINDOWPOS_CENTERED,
			int y = SDL_WINDOWPOS_CENTERED)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			create_window(title, w, h, x, y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

			create_context();
			init_openGL();
		}

		SDL2GLWindow(const SDL2GLWindow& other) = delete;
		SDL2GLWindow& operator=(const SDL2GLWindow& other) = delete;
	};
}
