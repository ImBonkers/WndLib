#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <WndLib/Window/WindowAbstract.hpp>
#include <WndLib/Window/GLFW/Translator/GLFWEventTranslator.hpp>

namespace wnd {
	class GLFWWindow : public Window
	{
	protected:
		inline static bool glfw_initialized = false;
		std::string window_title = "";
		unsigned int window_flags = 0;

		GLFWwindow* glfw_window = nullptr;

		event::Observer<event::WindowEvent>* close_event_observer;
		event::Observer<event::WindowQuitEvent>* quit_event_observer;

		bool open = false;

		int init_GLFW()
		{

			int status = glfwInit();
			if (status== GLFW_FALSE) {
				return status;
			}
			if (!glfw_initialized) {
				glfw_initialized = true;
				std::cout << "GLFW successfully initialized." << std::endl;
			}
			open = true;
			return 1;
		}

		void destroy_window()
		{
			if (open) {
				open = false;

				glfwDestroyWindow(glfw_window);

				delete close_event_observer;
				delete quit_event_observer;

				std::cout << "GLFW window destroyed." << std::endl;
			}
		}
	public:
		GLFWWindow()
		{
			init_GLFW();
		}
		GLFWWindow(
			const char* title,
			int w = 1280,
			int h = 720,
			int x = 0,
			int y = 0,
			unsigned int flags = 0)
		{
			init_GLFW();
			create_window(title, x, y, w, h, flags);
			window_flags = flags;
		}

		GLFWWindow(const GLFWWindow&) = delete;
		~GLFWWindow()
		{
			destroy_window();
		}

		GLFWWindow& operator=(const GLFWWindow& other) = delete;
	
		void create_window(const char* title, int w, int h, int x, int y, unsigned int flags)
		{
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

			glfw_window = glfwCreateWindow(w, h, title, 0, 0);

			if (!glfw_window) {
				std::cout << "GLFW window failed to be created [error: " << glfwGetError(0) << "]" << std::endl;
				destroy_window();
			}
			else {
				std::cout << "GLFW window successfully created." << std::endl;
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
				glfwTerminate();
			});
		}
		void create_window(const char* title, int w, int h, int x, int y)
		{
			create_window(title, w, h, x, y, 0);
		}
		void poll_events()
		{
			GLFWEventTranslator::get_instance().translate(this, glfw_window);
			glfwPollEvents();
		}
		void swap()
		{
			glfwSwapBuffers(glfw_window);
		}

		void enable_setting(Setting setting) {

		}

		int get_width()
		{
			int w;
			int h;
			glfwGetWindowSize(glfw_window, &w, &h);
			return w;
		}
		int get_height()
		{
			int w;
			int h;
			glfwGetWindowSize(glfw_window, &w, &h);
			return h;
		}

		std::string get_title()
		{
			return window_title;
		}
		void set_title(std::string title)
		{
			window_title = title;
			glfwSetWindowTitle(glfw_window, title.c_str());
		}

		unsigned int get_flags()
		{
			return window_flags;
		}

		void* get_window_ptr()
		{
			return glfw_window;
		}

		bool is_open()
		{
			return open;
		}
	};
}