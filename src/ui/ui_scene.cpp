#include "ui_scene.hpp"

namespace Rpm {

int UIScene::createNode(int parent) {
	int id = (int)mNodes.size();
	mNodes.push_back({});
	mNodes[id].parentIndex = parent;
	if (parent != -1) mNodes[parent].children.push_back(id);
	return id;
}

void UIScene::markDirty(int id) {
	mNodes[id].isDirty = true;
	for (auto child : mNodes[id].children)
		markDirty(child);
}

void UIScene::updateTransforms(int id, UITransform parentTransform) {
	UINode& node = mNodes[id];
	if (node.isDirty) {
		node.globalTransform.position = parentTransform.position + node.localTransform.position * parentTransform.scale;
		node.globalTransform.scale = parentTransform.scale * node.localTransform.scale;
		node.isDirty = false;
	}
	for (auto child : node.children) {
		updateTransforms(child, node.globalTransform);
	}
}

void UIScene::collectDrawCommands(std::vector<UIDrawCommand>& outCommands, int id) {
	const UINode& node = mNodes[id];
	outCommands.push_back({
		node.globalTransform.position,
		node.size,
		node.globalTransform.scale,
	});

	for (auto child : node.children) {
		collectDrawCommands(outCommands, child);
	}
}

}
