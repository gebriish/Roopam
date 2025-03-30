#pragma once
#include "draw_list.hpp"

namespace Rpm {

void renderInit();
void renderCleanup();

void renderSetViewport(int width, int height);
void renderClearViewport(float color[4]);

void renderDrawAll();
void renderFlushData();

DrawList& renderMainDrawList();

}
