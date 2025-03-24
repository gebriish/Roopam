#include "action_map.hpp"

#include <unordered_map>
#include <vector>
#include <cstdio>

namespace Rpm {

//======================================================================//
// Global ActionMap state
//======================================================================//
static struct {
	std::unordered_map<uint32_t, std::vector<ActionBinding>> bindings;
	std::unordered_map<uint32_t, Action> action_states;
} g_ActionMap;

//======================================================================//
// local helper function
//======================================================================//
static float _get_input_value(const ActionBinding& bind) {
	switch(bind.type) {
		case ActionType::KEYBOARD :
			return inputIsKeyPressed(bind.key) ? 1.0f : 0.0f;

		case ActionType::MOUSE_BUTTON :
			return inputIsMousePressed(bind.key) ? 1.0f : 0.0f;

		case ActionType::MOUSE_AXIS : {
			float xpos, ypos;
			inputGetCursorPosition(xpos, ypos);
			return (bind.key == 0) ? float(xpos) : float(ypos);
		}

		case ActionType::GAMEPAD_BUTTON : {
			return inputGamepadButtonPressed(bind.gamepad, bind.key) ? 1.0 : 0.0;
		}

		case ActionType::GAMEPAD_AXIS : {
			return inputGamepadAxis(bind.gamepad, bind.key);
		}

	}

	return 0.0f;
}

//======================================================================//
// Global state update (per 'frame') 
//======================================================================//
void actionMapUpdate() {
	for (auto& [action, binds] : g_ActionMap.bindings) {
		Action& state = g_ActionMap.action_states[action];
		state.bitset = state.bitset << 1;

		float value = 0.0f;
		int count = 0;

		for (const auto& bind : binds) {

			float value_reading = _get_input_value(bind);

			if (std::abs(value_reading) > bind.dead_zone) {
				value = value + value_reading * bind.scale;
				count++;
			}
		}

		if(count > 0) {
			state.bitset |= 1;
			value /= count;
			state.value = value;
		}
		else {
			state.value = 0.0f;
		}

	}
}

//======================================================================//
// Binding functions
//======================================================================//
void actionBindKey(uint32_t name, int key, float scale) {
	ActionBinding bind;
	bind.key = key;
	bind.type = ActionType::KEYBOARD;
	bind.scale = scale;

	g_ActionMap.bindings[name].push_back(bind);
}

void actionBindMouseButton(uint32_t name, int button, float scale) {
	ActionBinding bind;
	bind.type = ActionType::MOUSE_BUTTON;
	bind.key = button;
	bind.scale = scale;

	g_ActionMap.bindings[name].push_back(bind);
}


void actionBindMouseAxis(uint32_t name, bool x_axis, 
						 float dead_zone, float scale) {
	ActionBinding bind;
	bind.key = x_axis ? 0 : 1;
	bind.type = ActionType::MOUSE_AXIS;
	bind.scale = scale;
	bind.dead_zone = dead_zone;

	g_ActionMap.bindings[name].push_back(bind);
}


void actionBindGamepadButton(uint32_t name, int button, int gamepad, float scale) {
	ActionBinding bind;
	bind.type = ActionType::GAMEPAD_BUTTON;
	bind.key = button;
	bind.gamepad = gamepad;
	bind.scale = scale;

	g_ActionMap.bindings[name].push_back(bind);
}

void actionBindGamepadAxis(uint32_t name, int axis, int gamepad,
						   float dead_zone, float scale) {
	ActionBinding bind;
	bind.type = ActionType::GAMEPAD_AXIS;
	bind.key = axis;
	bind.scale = scale;
	bind.dead_zone = dead_zone;

	g_ActionMap.bindings[name].push_back(bind);
}

//======================================================================//
// Action polling  
//======================================================================//
bool actionPressed(uint32_t name) {
	auto it = g_ActionMap.action_states.find(name);
	if(it != g_ActionMap.action_states.end()) {
		const Action& action = it->second;
		return action.bitset & 1;
	}

	return false;
}

bool actionJustPressed(uint32_t name) {
	auto it = g_ActionMap.action_states.find(name);
	if (it != g_ActionMap.action_states.end()) {
		const Action& action = it->second;
		return (action.bitset & 0b11) == 0b01;
	}
	return false;
}

bool actionJustReleased(uint32_t name) {
	auto it = g_ActionMap.action_states.find(name);
	if (it != g_ActionMap.action_states.end()) {
		const Action& action = it->second;
		return (action.bitset & 0b11) == 0b10;
	}
	return false;
}

float actionGetValue(uint32_t name) {
	auto it = g_ActionMap.action_states.find(name);
	return (it != g_ActionMap.action_states.end()) ? it->second.value : 0.0f;
}

} // NAMESPACE RPM
