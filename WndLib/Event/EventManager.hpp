#pragma once

#include "Observer.hpp"
#include "EventTypes.hpp"

namespace event {
	class WindowEventManager
	{
	private:
		WindowEventManager() {};
	public:
		Subject<WindowQuitEvent> window_quit_event;
		Subject<WindowEvent> window_event;
		Subject<KeyboardEvent> keyboard_event;
		Subject<TextInputEvent> text_event;
		Subject<MouseMoveEvent> mouse_move_event;
		Subject<MouseButtonEvent> mouse_button_event;
		Subject<MouseWheelEvent> mouse_wheel_event;
		Subject<JoyAxisEvent> joy_axis_event;
		Subject<JoyBallEvent> joy_ball_event;
		Subject<JoyHatEvent> joy_hat_event;
		Subject<JoyButtonEvent> joy_butten_event;
		Subject<JoyDeviceEvent> joy_device_event;
		Subject<ControllerAxisEvent> controller_axis_event;
		Subject<ControllerButtonEvent> controller_button_event;
		Subject<ControllerDeviceEvent> controller_device_event;
		Subject<AudioDeviceEvent> audio_device_event;

		WindowEventManager(const WindowEventManager&) = delete;
		void operator=(const WindowEventManager&) = delete;

		static WindowEventManager& get_instance()
		{
			static WindowEventManager instance;
			return instance;
		}
	};
}