#pragma once

#include <string>

#include "Scancodes.hpp"

namespace event {
	enum class WindowEventType{
		NONE,
		QUIT,
		SHOWN,
		HIDDEN,
		EXPOSED,
		MOVED,
		RESIZED,
		SIZE_CHANGED,
		MINIMIZED,
		MAXIMIZED,
		RESTORED,
		ENTER,
		LEAVE,
		FOCUS_GAINED,
		FOCUS_LOST,
		CLOSE,
		TAKE_FOCUS
	};

	enum class DeviceState {
		CONNECTED, DISCONNECTED, REMAPPED
	};


	struct WindowQuitEvent {

	};

	struct WindowEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int x;
		int y;
		WindowEventType type;
	};

	struct KeyboardEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int mod;
		key::Scancode scancode;
		key::InputState state;
	};

	struct TextInputEvent {
		void* window_ptr;
		unsigned long long timestamp;
		std::string text;
	};

	struct MouseMoveEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int x;
		int y;
		int dx;
		int dy;
	};

	struct MouseButtonEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int button;
		int x;
		int y;
		int clicks;
		key::InputState state;
	};

	struct MouseWheelEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int x;
		int y;
		float xprecise;
		float yprecise;
	};

	struct JoyAxisEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int axis;
		int value;
	};

	struct JoyBallEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int ball;
		int xrel;
		int yrel;
	};

	struct JoyHatEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int hat;
		int value;
	};

	struct JoyButtonEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int button;
		key::InputState state;
	};

	struct JoyDeviceEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		DeviceState state;
	};

	struct ControllerAxisEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int axis;
		int value;
	};

	struct ControllerButtonEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		int button;
		key::InputState state;
	};

	struct ControllerDeviceEvent {
		void* window_ptr;
		unsigned long long timestamp;
		int id;
		DeviceState state;
	};

	struct AudioDeviceEvent {
		void* window_ptr;
		unsigned long long timestamp;
		bool isoutput;
		DeviceState state;
	};
}