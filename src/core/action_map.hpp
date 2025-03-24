#pragma once
#include <cstdint>
#include "input.hpp" // not needed, but included for ease of use

namespace Rpm {

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

void actionBindKey(uint32_t name, int key, float scale = 1.0f);
void actionBindMouseButton(uint32_t name, int button, float scale = 1.0f);
void actionBindMouseAxis(uint32_t name, bool x_axis, float dead_zone = 0.1f, float scale = 1.0f);
void actionBindGamepadButton(uint32_t name, int button, int gamepad = 0, float scale = 1.0f);
void actionBindGamepadAxis(uint32_t name, int axis, int gamepad = 0, float dead_zone = 0.0f, float scale = 1.0f);

bool actionPressed(uint32_t name);
bool actionJustPressed(uint32_t name);
bool actionJustReleased(uint32_t name);
float actionGetValue(uint32_t name);

void actionMapUpdate();

} // NAMESPACE RPM
