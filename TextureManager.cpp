#include "TextureManager.h"

void TextureManager::SaveTextures(const std::map<std::string, sf::Texture>& textures, const std::string& filename)
{
    std::ofstream file(filename);
    boost::archive::text_oarchive archive(file);

    // Serialize the number of textures and fonts
    size_t numTextures = textures.size();
    archive << numTextures;

    // Serialize each texture
    for (const auto& pair : textures) {
        const std::string& id = pair.first;
        const sf::Texture& texture = pair.second;

        archive << id << texture.getSize().x << texture.getSize().y; // Serialize texture ID and size

        // Serialize pixel data
        sf::Image image = texture.copyToImage();
        for (unsigned int y = 0; y < texture.getSize().y; ++y) {
            for (unsigned int x = 0; x < texture.getSize().x; ++x) {
                archive << image.getPixel(x, y).toInteger();
            }
        }
    }
}

bool TextureManager::LoadTextures(const std::string& filename)
{
	std::map<std::string, sf::Texture> textures;
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    boost::archive::text_iarchive archive(file);

    // Deserialize the number of textures and fonts
    size_t numTextures;
    archive >> numTextures;

    // Deserialize each texture
    for (size_t i = 0; i < numTextures; ++i) {
        std::string id;
        unsigned int width, height;
        archive >> id >> width >> height; // Deserialize texture ID and size

        sf::Image image;
        image.create(width, height);
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                sf::Uint32 pixelValue;
                archive >> pixelValue;
                image.setPixel(x, y, sf::Color(pixelValue));
            }
        }

        auto textureShPtr = std::make_shared<sf::Texture>();
        textureShPtr->loadFromImage(image);
        texturesMap[id] = textureShPtr;
    }

	return true;
}

std::shared_ptr<sf::Texture> TextureManager::AcquireTexture(const std::string& name)
{
    return texturesMap[name];
}
