#pragma once
#include <string>
#include <cstdint>
#include "input.hpp"

namespace rpm {

struct Action {
	float value = 0.0f;
	uint8_t bitset = 0;
};

enum class ActionType : uint8_t {
	KEYBOARD,
	MOUSE_BUTTON,
	MOUSE_AXIS,
	GAMEPAD_BUTTON,
	GAMEPAD_AXIS
};

struct ActionBinding {
	float dead_zone = 0.1f;
	float scale = 1.0f;
	int key;
	int gamepad;
	ActionType type;
};

void actionBindKey(const std::string& name, int key, float scale = 1.0f);
void actionBindMouseButton(const std::string& name, int button, float scale = 1.0f);
void actionBindMouseAxis(const std::string& name, bool x_axis, float dead_zone = 0.1f, float scale = 1.0f);
void actionBindGamepadButton(const std::string& name, int button, int gamepad = 0, float scale = 1.0f);
void actionBindGamepadAxis(const std::string& name, int axis, int gamepad = 0, float dead_zone = 0.0f, float scale = 1.0f);

bool actionPressed(const std::string& name);
bool actionJustPressed(const std::string& name);
bool actionJustReleased(const std::string& name);
float actionGetValue(const std::string& name);

void actionMapUpdate();

} // namespace rpm
