#include "window.hpp"

#include <GLFW/glfw3.h>
#include <array>

namespace rpm {

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
    #include <windows.h>
    #include <dwmapi.h>
    #pragma comment(lib, "Dwmapi.lib")
    
typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

BOOL _is_windows_11_or_greater() {
    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    if (!hMod) return false;

    RtlGetVersionPtr RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
    if (!RtlGetVersion) return false;

    RTL_OSVERSIONINFOW osInfo = { 0 };
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);
    RtlGetVersion(&osInfo);

    return (osInfo.dwMajorVersion == 10 && osInfo.dwBuildNumber >= 22000);
}
#endif

void _enable_dark_title_bar(GLFWwindow* window) {
#ifdef _WIN32
    if (!_is_windows_11_or_greater()) return;

    HWND hwnd = glfwGetWin32Window(window);
    if (hwnd) {
        BOOL darkMode = TRUE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    }
#endif
}

#define EVENT_QUEUE_SIZE 128

struct Window {
    GLFWwindow* handle;
    bool running;
};

struct EventQueue {
    std::array<Event, EVENT_QUEUE_SIZE> events;
    size_t head = 0;
    size_t tail = 0;
    size_t size = 0;

    bool push(const Event& e) {
        if (size >= EVENT_QUEUE_SIZE) {
            return false;
        }
        events[tail] = e;
        tail = (tail + 1) % EVENT_QUEUE_SIZE;
        size++;
        return true;
    }

    bool pop(Event& e) {
        if (size == 0) return false;
        e = events[head];
        head = (head + 1) % EVENT_QUEUE_SIZE;
        size--;
        return true;
    }
};

static EventQueue g_EventQueue;

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Event key_event;
    key_event.type = EVENT_KEY;
    key_event.key_data = { key, scancode, action, mods };
    g_EventQueue.push(key_event);
}

void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Event mouse_event;
    mouse_event.type = EVENT_MOUSE_BUTTON;
    mouse_event.mouse_buton_data = { button, action, mods };
    g_EventQueue.push(mouse_event);
}

void _cursor_pos_callback(GLFWwindow* window, double x, double y) {
    static double last_x = x, last_y = y;
    Event cursor_event;
    cursor_event.type = EVENT_CURSOR;
    cursor_event.cursor_data = { x, y, x - last_x, y - last_y };
    last_x = x;
    last_y = y;
    g_EventQueue.push(cursor_event);
}

void _scroll_callback(GLFWwindow* window, double x, double y) {
    Event scroll_event;
    scroll_event.type = EVENT_SCROLL;
    scroll_event.scroll_data = { x, y };
    g_EventQueue.push(scroll_event);
}

void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    Event resize_event;
    resize_event.type = EVENT_RESIZE;
    resize_event.resize_data = { width, height };
    g_EventQueue.push(resize_event);
}

void _char_callback(GLFWwindow* window, uint32_t codepoint) {
    Event codepoint_event;
    codepoint_event.type = EVENT_CODEPOINT;
    codepoint_event.codepoint_data = { codepoint };
    g_EventQueue.push(codepoint_event);
}

Window* windowInitialize(int width, int height, const char* title, uint32_t flags) {
    if (!glfwInit()) {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, flags & WINDOWFLAG_RESIZABLE ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_MAXIMIZED, flags & WINDOWFLAG_MAXIMIZED ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, !(flags & WINDOWFLAG_UNDECORATED));
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, flags & WINDOWFLAG_TRANSPARENT ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window* window = new Window;
    window->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window->handle) {
        delete window;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window->handle);
    glfwSetKeyCallback(window->handle, _key_callback);
    glfwSetMouseButtonCallback(window->handle, _mouse_button_callback);
    glfwSetCursorPosCallback(window->handle, _cursor_pos_callback);
    glfwSetScrollCallback(window->handle, _scroll_callback);
    glfwSetFramebufferSizeCallback(window->handle, _framebuffer_size_callback);
    glfwSetCharCallback(window->handle, _char_callback);

    if (flags & WINDOWFLAG_CENTERED) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowPos(window->handle, (mode->width - width) / 2, (mode->height - height) / 2);
    }

    glfwSwapInterval(flags & WINDOWFLAG_VSYNC ? 1 : 0);
    _enable_dark_title_bar(window->handle);
    glfwShowWindow(window->handle);
    window->running = true;

    return window;
}

void windowDestroy(Window* window) {
    if (window) {
        glfwDestroyWindow(window->handle);
        delete window;
    }
}

void windowSwapBuffers(const Window* window) {
    if (window) {
        glfwSwapBuffers(window->handle);
    }
}

void windowPollEvents(Window* window) {
    if (!window) return;
    glfwPollEvents();

    if (glfwWindowShouldClose(window->handle) && window->running) {
        Event quit_event = { EVENT_QUIT };
        window->running = false;
        g_EventQueue.push(quit_event);
    }
}

bool windowGetEvent(Event& e) {
    return g_EventQueue.pop(e);
}

void windowSetTitle(const Window* window, const char* title) {
    if (window) {
        glfwSetWindowTitle(window->handle, title);
    }
}

void* windowGetNativeHandle(const Window* window) {
    return window ? (void*)window->handle : nullptr;
}

std::pair<int, int> windowGetResolution(const Window* window) {
    if (!window) return { 0, 0 };

    int width, height;
    glfwGetWindowSize(window->handle, &width, &height);
    return { width, height };
}

void windowSetIcon(const Window* window, const Image2D* image) {
    if(!window || !image) return;

    float width, height;
    imageGetSpecification(image, ImageSpec::WIDTH, width);
    imageGetSpecification(image, ImageSpec::HEIGHT, height);

    GLFWimage glfw_icon;
    glfw_icon.width = int(width);
    glfw_icon.height = int(height);
    glfw_icon.pixels = imageGetData(image);

    glfwSetWindowIcon(window->handle, 1, &glfw_icon);
}

float windowGetSeconds() {
    return static_cast<float>(glfwGetTime());
}

} // namespace rpm
