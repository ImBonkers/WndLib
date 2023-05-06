#pragma once

#include <sdl/SDL.h>

#include <unordered_map>
#include <functional>

#include <WndLib/Event/EventManager.hpp>

class SDL2EventTranslator : public EventTranslator
{
private:
	std::unordered_map<int, SDL_GameController*> controllers;
	std::unordered_map<int, SDL_Joystick*> joysticks;
	std::unordered_map<Uint32, event::WindowEventType> window_events;
	std::unordered_map<Uint32, std::function<void(wnd::Window*, const SDL_Event& e)>> translators;

private:
	SDL2EventTranslator()
	{
		window_events = {
			{ SDL_QUIT, event::WindowEventType::QUIT },
			{ SDL_WINDOWEVENT_NONE, event::WindowEventType::NONE },
			{ SDL_WINDOWEVENT_SHOWN, event::WindowEventType::SHOWN },
			{ SDL_WINDOWEVENT_HIDDEN, event::WindowEventType::HIDDEN },
			{ SDL_WINDOWEVENT_EXPOSED, event::WindowEventType::EXPOSED },
			{ SDL_WINDOWEVENT_MOVED, event::WindowEventType::MOVED },
			{ SDL_WINDOWEVENT_RESIZED, event::WindowEventType::RESIZED },
			{ SDL_WINDOWEVENT_SIZE_CHANGED, event::WindowEventType::SIZE_CHANGED },
			{ SDL_WINDOWEVENT_MINIMIZED, event::WindowEventType::MINIMIZED },
			{ SDL_WINDOWEVENT_MAXIMIZED, event::WindowEventType::MAXIMIZED },
			{ SDL_WINDOWEVENT_RESTORED, event::WindowEventType::RESTORED },
			{ SDL_WINDOWEVENT_ENTER, event::WindowEventType::ENTER },
			{ SDL_WINDOWEVENT_LEAVE, event::WindowEventType::LEAVE },
			{ SDL_WINDOWEVENT_FOCUS_GAINED, event::WindowEventType::FOCUS_GAINED },
			{ SDL_WINDOWEVENT_FOCUS_LOST, event::WindowEventType::FOCUS_LOST },
			{ SDL_WINDOWEVENT_CLOSE, event::WindowEventType::CLOSE },
			{ SDL_WINDOWEVENT_TAKE_FOCUS, event::WindowEventType::TAKE_FOCUS }
		};

		event::WindowEventManager& manager = event::WindowEventManager::get_instance();

		translators[SDL_QUIT] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.window_quit_event.update({});
		};
		translators[SDL_WINDOWEVENT] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.window_event.update({
				window_ptr,
				e.window.timestamp,
				e.window.data1,
				e.window.data2,
				window_events[e.window.event]
				});
		};
		translators[SDL_KEYUP] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			// SDL2 scancodes and modifiers are directly compatible with the project.
			manager.keyboard_event.update({
				window_ptr,
				e.key.timestamp,
				e.key.keysym.mod,
				(key::Scancode)(int)e.key.keysym.scancode,
				key::InputState::UP
				});
		};
		translators[SDL_KEYDOWN] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			// SDL2 scancodes and modifiers are directly compatible with the project.
			key::InputState state = key::InputState::DOWN;
			if (e.key.repeat) {
				state = key::InputState::REPEAT;
			}

			manager.keyboard_event.update({
				window_ptr,
				e.key.timestamp,
				e.key.keysym.mod,
				(key::Scancode)(int)e.key.keysym.scancode,
				state
				});
		};
		translators[SDL_TEXTINPUT] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.text_event.update({
				window_ptr,
				e.text.timestamp,
				std::string(e.text.text)
				});
		};
		translators[SDL_MOUSEMOTION] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.mouse_move_event.update({
				window_ptr,
				e.motion.timestamp,
				(int)e.motion.which,
				e.motion.x,
				e.motion.y,
				e.motion.xrel,
				e.motion.yrel,
				});
		};
		translators[SDL_MOUSEBUTTONDOWN] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.mouse_button_event.update({
				window_ptr,
				e.button.timestamp,
				(int)e.button.which,
				e.button.button,
				e.button.x,
				e.button.y,
				e.button.clicks,
				key::InputState::DOWN
				});
		};
		translators[SDL_MOUSEBUTTONUP] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.mouse_button_event.update({
				window_ptr,
				e.button.timestamp,
				(int)e.button.which,
				e.button.button,
				e.button.x,
				e.button.y,
				e.button.clicks,
				key::InputState::UP
				});
		};
		translators[SDL_MOUSEWHEEL] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.mouse_wheel_event.update({
				window_ptr,
				e.wheel.timestamp,
				(int)e.wheel.which,
				e.wheel.x,
				e.wheel.y,
				e.wheel.preciseX,
				e.wheel.preciseY
				});
		};
		translators[SDL_JOYAXISMOTION] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.joy_axis_event.update({
				window_ptr,
				e.jaxis.timestamp,
				(int)e.jaxis.which,
				e.jaxis.axis,
				e.jaxis.value
				});
		};
		translators[SDL_JOYBALLMOTION] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.joy_ball_event.update({
				window_ptr,
				e.jball.timestamp,
				e.jball.which,
				e.jball.ball,
				e.jball.xrel,
				e.jball.yrel
				});
		};
		translators[SDL_JOYHATMOTION] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.joy_hat_event.update({
				window_ptr,
				e.jhat.timestamp,
				e.jhat.which,
				e.jhat.hat,
				e.jhat.value
				});
		};
		translators[SDL_JOYBUTTONDOWN] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.joy_butten_event.update({
				window_ptr,
				e.jbutton.timestamp,
				e.jbutton.which,
				e.jbutton.button,
				key::InputState::DOWN
				});
		};
		translators[SDL_JOYBUTTONUP] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.joy_butten_event.update({
				window_ptr,
				e.jbutton.timestamp,
				e.jbutton.which,
				e.jbutton.button,
				key::InputState::UP
				});
		};
		translators[SDL_JOYDEVICEADDED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			joysticks[e.jdevice.which] = SDL_JoystickOpen(e.jdevice.which);
			manager.joy_device_event.update({
				window_ptr,
				e.jdevice.timestamp,
				e.jdevice.which,
				event::DeviceState::CONNECTED
				});
		};
		translators[SDL_JOYDEVICEREMOVED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			SDL_JoystickClose(joysticks[e.jdevice.which]);
			manager.joy_device_event.update({
				window_ptr,
				e.jdevice.timestamp,
				e.jdevice.which,
				event::DeviceState::DISCONNECTED
				});
		};
		translators[SDL_CONTROLLERAXISMOTION] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.controller_axis_event.update({
				window_ptr,
				e.caxis.timestamp,
				e.caxis.which,
				e.caxis.axis,
				e.caxis.value,
				});
		};
		translators[SDL_CONTROLLERBUTTONDOWN] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.controller_button_event.update({
				window_ptr,
				e.cbutton.timestamp,
				e.cbutton.which,
				e.cbutton.button,
				key::InputState::DOWN
				});
		};
		translators[SDL_CONTROLLERBUTTONUP] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.controller_button_event.update({
				window_ptr,
				e.cbutton.timestamp,
				e.cbutton.which,
				e.cbutton.button,
				key::InputState::UP
				});
		};
		translators[SDL_CONTROLLERDEVICEADDED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			controllers[e.cdevice.which] = SDL_GameControllerOpen(e.cdevice.which);
			manager.controller_device_event.update({
				window_ptr,
				e.cdevice.timestamp,
				e.cdevice.which,
				event::DeviceState::CONNECTED
				});
		};
		translators[SDL_CONTROLLERDEVICEREMOVED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			SDL_GameControllerClose(controllers[e.cdevice.which]);
			manager.controller_device_event.update({
				window_ptr,
				e.cdevice.timestamp,
				e.cdevice.which,
				event::DeviceState::DISCONNECTED
				});
		};
		translators[SDL_CONTROLLERDEVICEREMAPPED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.controller_device_event.update({
				window_ptr,
				e.cdevice.timestamp,
				e.cdevice.which,
				event::DeviceState::REMAPPED
				});
		};
		translators[SDL_AUDIODEVICEADDED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.audio_device_event.update({
				window_ptr,
				e.adevice.timestamp,
				!(e.adevice.iscapture),
				event::DeviceState::CONNECTED
				});
		};
		translators[SDL_AUDIODEVICEREMOVED] = [&](wnd::Window* window_ptr, const SDL_Event& e) {
			manager.audio_device_event.update({
				window_ptr,
				e.adevice.timestamp,
				!(e.adevice.iscapture),
				event::DeviceState::DISCONNECTED
				});
		};
	}

public:
	SDL2EventTranslator(const SDL2EventTranslator&) = delete;
	void operator=(const SDL2EventTranslator&) = delete;

	static SDL2EventTranslator& get_instance()
	{
		static SDL2EventTranslator instance;
		return instance;
	}

	void translate(wnd::Window* window_ptr, const SDL_Event& e)
	{
		auto it = translators.find(e.type);
		if (it != translators.end()) {
			translators[e.type](window_ptr, e);
		}
	}
};