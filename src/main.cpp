#include "core/window.hpp"
#include "core/action_map.hpp"
#include "core/embedded_images.hpp"

#include <iostream>

int main() {
	rpm::Window* window = rpm::windowInitialize(
		512, 512, "Roopam",
		rpm::WINDOWFLAG_CENTERED | rpm::WINDOWFLAG_VSYNC
	);

	// Window icon setup
	{
		rpm::Image2D* icon = rpm::imageInitialize(rpm::EMBEDDED_ICON, 16, 16, 4);
		if (icon) {
			rpm::Image2D* icon2 = imageUpscale(icon, 3);
			rpm::imageFree(icon);
			if (icon2) {
				rpm::windowSetIcon(window, icon2);
				rpm::imageFree(icon2);
			}
		}
	}

	rpm::actionBindKey("UP", rpm::KEY_W);

	rpm::inputSetWindow(window);

	bool running = true;
	while (running) {
		rpm::Event e;
		rpm::windowPollEvents(window);
		while (rpm::windowGetEvent(e)) {
			if (e.type == rpm::EVENT_QUIT) {
				running = false;
			}
		}

		static int count = 0;
		if(rpm::actionJustPressed("UP")) printf("%d\n", ++count);

		rpm::actionMapUpdate();
		rpm::windowSwapBuffers(window);
	}

	rpm::windowDestroy(window);
}
