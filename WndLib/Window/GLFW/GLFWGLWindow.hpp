#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <WndLib/Window/WindowAbstract.hpp>
#include <WndLib/Window/OpenGLLoader.hpp>

#include "GLFWWindow.hpp"

namespace wnd {
	class GLFWGLWindow : public GLFWWindow
	{
	private:
		inline static bool opengl_initialized = false;

		int init_openGL()
		{
			glfwMakeContextCurrent(glfw_window);
			if (opengl_initialized) {
				return 1;
			}

			OpenGLLoader loader;
			int success = loader.load_opengl((GLADloadproc)glfwGetProcAddress);
			if (!success) {
				return success;
			}
			else {
				opengl_initialized = true;
			}

			glfwSwapInterval(1);

			return 1;
		}
	public:
		GLFWGLWindow() = delete;
		GLFWGLWindow(const char* title,
			int w = 1280,
			int h = 720,
			int x = 0,
			int y = 0)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

			glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
			glfwWindowHint(GLFW_DEPTH_BITS, 24);


			create_window(title, w, h, x, y);
			init_openGL();
		}

		GLFWGLWindow(const GLFWGLWindow& other) = delete;
		GLFWGLWindow& operator=(const GLFWGLWindow& other) = delete;
	};
}
