#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "IExecutionEvent.h"
#include "ThreadPool.h"

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;
	
public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadStreamingAssets();
	void loadSingleStreamAsset(int index, IExecutionEvent* execEvent); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	int getStreamingAssetsCount() const;
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

private:
	TextureManager();
	~TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	const std::string STREAMING_PATH = "Media/Streaming/";
	int streamingAssetCount = 0;

	ThreadPool* threadPool;

	void countStreamingAssets();
};