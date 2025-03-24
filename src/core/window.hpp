#pragma once
#include <cstdint>
#include <utility>
#include "image.hpp"

namespace Rpm {

struct Window;

enum EventType : uint16_t {
	EVENT_QUIT, 
	EVENT_RESIZE,
	EVENT_KEY,
	EVENT_CURSOR,
	EVENT_MOUSE_BUTTON,
	EVENT_CODEPOINT,
	EVENT_SCROLL,
	EVENT_WINDOW_MOVE,
};

enum WindowFlags : uint8_t {
	WINDOWFLAG_NONE         = 0,
	WINDOWFLAG_MAXIMIZED    = 1 << 0,
	WINDOWFLAG_RESIZABLE    = 1 << 1,
	WINDOWFLAG_VSYNC        = 1 << 2,
	WINDOWFLAG_UNDECORATED  = 1 << 3,
	WINDOWFLAG_CENTERED     = 1 << 4,
	WINDOWFLAG_TRANSPARENT  = 1 << 5,
	WINDOWFLAG_FULLSCREEN   = 1 << 6,
};

struct Event {
	EventType type;
	union {
		struct { int width, height; } resize_data;
		struct { int key, scancode, action, mods; } key_data;
		struct { double x, y, delta_x, delta_y; } cursor_data;
		struct { int button, action, mods; } mouse_buton_data;
		struct { uint32_t codepoint; } codepoint_data;
		struct { double x, y; } scroll_data;
		struct { int x, y; } window_move_data;
	};
};

Window* windowInitialize(int width, int height, const char* title, uint32_t flags);
void windowDestroy(Window* window);

void windowSwapBuffers(const Window* window);
void windowPollEvents(Window* window);

bool windowGetEvent(Event& e);
void* windowGetNativeHandle(const Window* window); 
std::pair<int,int> windowGetResolution(const Window* window);
std::pair<int, int> windowGetPosition(const Window* window);

void windowSetTitle(const Window* window, const char* title);
void windowSetIcon(const Window* window, const Image2D* image);

void windowSetMode(const Window* window, WindowFlags flags);
void windowSetPosition(const Window* window, int xPos, int yPos);

float windowGetSeconds();

} // NAMESPACE RPM
