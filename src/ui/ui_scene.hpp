#pragma once
#include <core/vmath.hpp>
#include <vector>


namespace Rpm {

struct UINode;
struct UIScene;

using LayoutCallback = void(*)(UINode& node, UIScene& scene);

struct UITransform {
	vec2 position{0.0f};
	vec2 scale{1.0f};
};

struct UINode {
	int parentIndex = -1;
	std::vector<int> children;
	UITransform localTransform;
	UITransform globalTransform;
	bool isDirty = true;
	vec2 size;
};

struct UIDrawCommand {
	vec2 position;
	vec2 size;
	vec2 scale;
};

class UIScene {
public:
	int createNode(int parent = -1);
	void markDirty(int id);
	void updateTransforms(int id=0, UITransform parentTransform = {});
	void collectDrawCommands(std::vector<UIDrawCommand>& outCommands, int id = 0);

	inline const std::vector<UINode>& getNodes() const { return mNodes; }
private:
	std::vector<UINode> mNodes;
};

};
