#pragma once

#include <unordered_map>

#include <WndLib/Event/Scancodes.hpp>

class GLFWScancodeTranslator {
private:
	std::unordered_map<int, key::Scancode> translator;
private:
	GLFWScancodeTranslator() {
		translator = {
			{GLFW_KEY_SPACE, key::Scancode::SPACE},
			{GLFW_KEY_APOSTROPHE, key::Scancode::APOSTROPHE},
			{GLFW_KEY_COMMA, key::Scancode::COMMA},
			{GLFW_KEY_MINUS, key::Scancode::MINUS},
			{GLFW_KEY_PERIOD, key::Scancode::PERIOD},
			{GLFW_KEY_SLASH, key::Scancode::SLASH},
			{GLFW_KEY_0, key::Scancode::NUM0},
			{GLFW_KEY_1, key::Scancode::NUM1},
			{GLFW_KEY_2, key::Scancode::NUM2},
			{GLFW_KEY_3, key::Scancode::NUM3},
			{GLFW_KEY_4, key::Scancode::NUM4},
			{GLFW_KEY_5, key::Scancode::NUM5},
			{GLFW_KEY_6, key::Scancode::NUM6},
			{GLFW_KEY_7, key::Scancode::NUM7},
			{GLFW_KEY_8, key::Scancode::NUM8},
			{GLFW_KEY_9, key::Scancode::NUM9},
			{GLFW_KEY_SEMICOLON, key::Scancode::SEMICOLON},
			{GLFW_KEY_EQUAL, key::Scancode::EQUALS},
			{GLFW_KEY_A, key::Scancode::A},
			{GLFW_KEY_B, key::Scancode::B},
			{GLFW_KEY_C, key::Scancode::C},
			{GLFW_KEY_D, key::Scancode::D},
			{GLFW_KEY_E, key::Scancode::E},
			{GLFW_KEY_F, key::Scancode::F},
			{GLFW_KEY_G, key::Scancode::G},
			{GLFW_KEY_H, key::Scancode::H},
			{GLFW_KEY_I, key::Scancode::I},
			{GLFW_KEY_J, key::Scancode::J},
			{GLFW_KEY_K, key::Scancode::K},
			{GLFW_KEY_L, key::Scancode::L},
			{GLFW_KEY_M, key::Scancode::M},
			{GLFW_KEY_N, key::Scancode::N},
			{GLFW_KEY_O, key::Scancode::O},
			{GLFW_KEY_P, key::Scancode::P},
			{GLFW_KEY_Q, key::Scancode::Q},
			{GLFW_KEY_R, key::Scancode::R},
			{GLFW_KEY_S, key::Scancode::S},
			{GLFW_KEY_T, key::Scancode::T},
			{GLFW_KEY_U, key::Scancode::U},
			{GLFW_KEY_V, key::Scancode::V},
			{GLFW_KEY_W, key::Scancode::W},
			{GLFW_KEY_X, key::Scancode::X},
			{GLFW_KEY_Y, key::Scancode::Y},
			{GLFW_KEY_Z, key::Scancode::Z},
			{GLFW_KEY_LEFT_BRACKET, key::Scancode::LEFTBRACKET},
			{GLFW_KEY_BACKSLASH, key::Scancode::BACKSLASH},
			{GLFW_KEY_RIGHT_BRACKET, key::Scancode::RIGHTBRACKET},
			{GLFW_KEY_GRAVE_ACCENT, key::Scancode::GRAVE},
			{GLFW_KEY_ESCAPE, key::Scancode::ESCAPE},
			{GLFW_KEY_ENTER, key::Scancode::RETURN},
			{GLFW_KEY_TAB, key::Scancode::TAB},
			{GLFW_KEY_BACKSPACE, key::Scancode::BACKSPACE},
			{GLFW_KEY_INSERT, key::Scancode::INSERT},
			{GLFW_KEY_DELETE, key::Scancode::DELETE},
			{GLFW_KEY_RIGHT, key::Scancode::RIGHT},
			{GLFW_KEY_LEFT, key::Scancode::LEFT},
			{GLFW_KEY_DOWN, key::Scancode::DOWN},
			{GLFW_KEY_UP, key::Scancode::UP},
			{GLFW_KEY_PAGE_UP, key::Scancode::PAGEUP},
			{GLFW_KEY_PAGE_DOWN, key::Scancode::PAGEDOWN},
			{GLFW_KEY_HOME, key::Scancode::HOME},
			{GLFW_KEY_END, key::Scancode::END},
			{GLFW_KEY_CAPS_LOCK, key::Scancode::CAPSLOCK},
			{GLFW_KEY_SCROLL_LOCK, key::Scancode::SCROLLLOCK},
			{GLFW_KEY_NUM_LOCK, key::Scancode::NUMLOCKCLEAR},
			{GLFW_KEY_PRINT_SCREEN, key::Scancode::PRINTSCREEN},
			{GLFW_KEY_PAUSE, key::Scancode::PAUSE},
			{GLFW_KEY_F1, key::Scancode::F1},
			{GLFW_KEY_F2, key::Scancode::F2},
			{GLFW_KEY_F3, key::Scancode::F3},
			{GLFW_KEY_F4, key::Scancode::F4},
			{GLFW_KEY_F5, key::Scancode::F5},
			{GLFW_KEY_F6, key::Scancode::F6},
			{GLFW_KEY_F7, key::Scancode::F7},
			{GLFW_KEY_F8, key::Scancode::F8},
			{GLFW_KEY_F9, key::Scancode::F9},
			{GLFW_KEY_F10, key::Scancode::F10},
			{GLFW_KEY_F11, key::Scancode::F11},
			{GLFW_KEY_F12, key::Scancode::F12},
			{GLFW_KEY_F13, key::Scancode::F13},
			{GLFW_KEY_F14, key::Scancode::F14},
			{GLFW_KEY_F15, key::Scancode::F15},
			{GLFW_KEY_F16, key::Scancode::F16},
			{GLFW_KEY_F17, key::Scancode::F17},
			{GLFW_KEY_F18, key::Scancode::F18},
			{GLFW_KEY_F19, key::Scancode::F19},
			{GLFW_KEY_F20, key::Scancode::F20},
			{GLFW_KEY_F21, key::Scancode::F21},
			{GLFW_KEY_F22, key::Scancode::F22},
			{GLFW_KEY_F23, key::Scancode::F23},
			{GLFW_KEY_F24, key::Scancode::F24},
			{GLFW_KEY_KP_0, key::Scancode::KP_0},
			{GLFW_KEY_KP_1, key::Scancode::KP_1},
			{GLFW_KEY_KP_2, key::Scancode::KP_2},
			{GLFW_KEY_KP_3, key::Scancode::KP_3},
			{GLFW_KEY_KP_4, key::Scancode::KP_4},
			{GLFW_KEY_KP_5, key::Scancode::KP_5},
			{GLFW_KEY_KP_6, key::Scancode::KP_6},
			{GLFW_KEY_KP_7, key::Scancode::KP_7},
			{GLFW_KEY_KP_8, key::Scancode::KP_8},
			{GLFW_KEY_KP_9, key::Scancode::KP_9},
			{GLFW_KEY_KP_DECIMAL, key::Scancode::KP_DECIMAL},
			{GLFW_KEY_KP_DIVIDE, key::Scancode::KP_DIVIDE},
			{GLFW_KEY_KP_MULTIPLY, key::Scancode::KP_MULTIPLY},
			{GLFW_KEY_KP_SUBTRACT, key::Scancode::KP_MEMSUBTRACT},
			{GLFW_KEY_KP_ADD, key::Scancode::KP_MEMADD},
			{GLFW_KEY_KP_ENTER, key::Scancode::KP_ENTER},
			{GLFW_KEY_KP_EQUAL, key::Scancode::KP_EQUALS},
			{GLFW_KEY_LEFT_SHIFT, key::Scancode::LSHIFT},
			{GLFW_KEY_LEFT_CONTROL, key::Scancode::LCTRL},
			{GLFW_KEY_LEFT_ALT, key::Scancode::LALT},
			{GLFW_KEY_RIGHT_SHIFT, key::Scancode::RSHIFT},
			{GLFW_KEY_RIGHT_CONTROL, key::Scancode::RCTRL},
			{GLFW_KEY_RIGHT_ALT, key::Scancode::RALT},
			{GLFW_KEY_MENU, key::Scancode::MENU},
		};
	}
public:	
	GLFWScancodeTranslator(const GLFWScancodeTranslator&) = delete;
	void operator=(const GLFWScancodeTranslator&) = delete;

	static GLFWScancodeTranslator& get_instance()
	{
		static GLFWScancodeTranslator instance;
		return instance;
	}

	key::Scancode translate(int code) {
		auto it = translator.find(code);
		if (it != translator.end())
			return it->second;
		return key::Scancode::UNKNOWN;
	}
};