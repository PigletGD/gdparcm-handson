#include "StreamAssetLoader.h"
#include <vector>
#include "StringUtils.h"
#include "TextureManager.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* execEvent) {
	this->path = path;
	this->execEvent = execEvent;

	std::cout << "Desdfsjdflkjsdlfjsfdjksfjstroying stream asset loader." << std::endl;
}

StreamAssetLoader::~StreamAssetLoader() {
	std::cout << "Destroying stream asset loader." << std::endl;
}

void StreamAssetLoader::onStartTask() {
	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	//simulate loading of very large file
	IETThread::sleep(500);
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	// throw event
	this->execEvent->onFinishedExecution();

	//delete after done
	delete this;
}