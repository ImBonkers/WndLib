#pragma once

#include <glfw/glfw3.h>

#include <unordered_map>
#include <functional>

#include <WndLib/Window.hpp>
#include <WndLib/Window/GLFW/GLFWWindow.hpp>
#include <WndLib/Event/EventManager.hpp>

#include "GLFWScancodeTranslator.hpp"

class GLFWEventTranslator: public EventTranslator
{
private:
	inline static int mouse_pos_x = 0;
	inline static int mouse_pos_y = 0;

	static unsigned long long generate_timestamp() { return 0; }

	static key::InputState get_state(int action) {
		key::InputState state;
		switch (action) {
		case GLFW_PRESS: {
			state = key::InputState::DOWN;
		}break;
		case GLFW_REPEAT: {
			state = key::InputState::REPEAT;
		}break;
		case GLFW_RELEASE: {
			state = key::InputState::UP;
		}break;
		default: {
			state = key::InputState::UNKNOWN;
		}break;
		}
		return state;
	}

	static void window_size_callback(GLFWwindow* window, int width, int height) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		manager.window_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			width,
			height,
			event::WindowEventType::SIZE_CHANGED,
		});
	}

	static void window_position_callback(GLFWwindow* window, int x, int y) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		manager.window_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			x,
			y,
			event::WindowEventType::MOVED,
		});
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();
		
		key::InputState state = get_state(action);

		manager.keyboard_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			mods,
			GLFWScancodeTranslator::get_instance().translate(key),
			state,
		});
	}


	// Deal with text construction at some point...
	static void character_callback(GLFWwindow* window, unsigned int codepoint) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();
		
		manager.text_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			std::string(),
		});
	}

	static void mouse_move_callback(GLFWwindow* window, double x, double y) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		int x_rel = mouse_pos_x - (int)x;
		int y_rel = mouse_pos_y - (int)y;

		mouse_pos_x = (int)x;
		mouse_pos_y = (int)y;

		manager.mouse_move_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			0,
			(int)x,
			(int)y,
			x_rel,
			y_rel,
		});
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		key::InputState state = get_state(action);

		manager.mouse_button_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			0, // id
			button,
			mouse_pos_x,
			mouse_pos_y,
			1,
			state,
		});
	}

	static void scroll_callback(GLFWwindow* window, double x, double y) {
		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		manager.mouse_wheel_event.update({
			glfwGetWindowUserPointer(window),
			generate_timestamp(),
			0, // id
			(int)x,
			(int)y,
			(float)x,
			(float)y
		});
	}

	GLFWEventTranslator() {}

public:
	GLFWEventTranslator(const GLFWEventTranslator&) = delete;
	void operator=(const GLFWEventTranslator&) = delete;

	static GLFWEventTranslator& get_instance()
	{
		static GLFWEventTranslator instance;
		return instance;
	}

	void translate(wnd::Window* window_ptr, GLFWwindow* glfw_window)
	{
		glfwSetWindowUserPointer(glfw_window, window_ptr);
		glfwSetWindowSizeCallback(glfw_window, &GLFWEventTranslator::window_size_callback);
		glfwSetWindowPosCallback(glfw_window, &GLFWEventTranslator::window_position_callback);
		glfwSetKeyCallback(glfw_window, &GLFWEventTranslator::key_callback);
		glfwSetCharCallback(glfw_window, &GLFWEventTranslator::character_callback);
		glfwSetCursorPosCallback(glfw_window, &GLFWEventTranslator::mouse_move_callback);
		glfwSetMouseButtonCallback(glfw_window, &GLFWEventTranslator::mouse_button_callback);
		glfwSetScrollCallback(glfw_window, &GLFWEventTranslator::scroll_callback);
	}
};