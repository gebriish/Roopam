#include "input.hpp"
#include <GLFW/glfw3.h>

namespace rpm {

static struct {
  void* window_handle = nullptr;
} g_InputState;

void inputSetWindow(const Window* window) {
  g_InputState.window_handle = windowGetNativeHandle(window);
}

bool inputIsKeyPressed(int key) {
  GLFWwindow* ptr = (GLFWwindow*) g_InputState.window_handle;
  
  if(ptr)
    return glfwGetKey(ptr, key) == GLFW_PRESS;

  return false;
}

bool inputIsMousePressed(int button) {
  GLFWwindow* ptr = (GLFWwindow*) g_InputState.window_handle;
  if(ptr)  
    return glfwGetMouseButton(ptr, button) == GLFW_PRESS;

  return false;
}

void inputGetCursorPosition(float& x_axis, float& y_axis) {
  double x, y;
  GLFWwindow* ptr = (GLFWwindow*) g_InputState.window_handle;
	if(!ptr) return;
		
	glfwGetCursorPos(ptr, &x, &y);
	x_axis = float(x);
	y_axis = float(y);
	return;
}


bool inputGamepadConntected(int gamepad) {
  return glfwJoystickPresent(gamepad);
}

bool inputGamepadButtonPressed(int gamepad, int button) {
  if (!glfwJoystickPresent(gamepad)) return false;

  GLFWgamepadstate state;
  if (glfwGetGamepadState(gamepad, &state)) {
    return state.buttons[button] == GLFW_PRESS;
  }
  return false;
}

float inputGamepadAxis(int gamepad, int axis) {
  if (!glfwJoystickPresent(gamepad)) return 0.0f;

  GLFWgamepadstate state;
  if (glfwGetGamepadState(gamepad, &state)) {
    return state.axes[axis];
  }
  return 0.0f;
}

} // namespace rpm
