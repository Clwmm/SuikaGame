#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <memory>
#include <map>

#include "SFML/Graphics.hpp"
#include "Settings.h"

class TextureManager
{
public:
	static void SaveTextures(const std::map<std::string, sf::Texture>& textures, const std::string& filename);
	static bool LoadTextures(const std::string& filename);
	static sf::Texture AcquireTexture(const std::string& name);
private:
	static std::map<std::string, sf::Texture> texturesMap;
};

