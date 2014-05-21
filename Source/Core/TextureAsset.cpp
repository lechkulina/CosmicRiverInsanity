/*
 * TextureAsset.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/TextureAsset.hpp>

Cosmic::Core::TextureAsset::TextureAsset(boost::shared_ptr<VideoContext> videoContext,
                                        const boost::filesystem::path& assetPath) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    texture(nullptr),
    width(0),
    height(0) {
    BOOST_LOG_FUNCTION();

    //load and decode image file
    BOOST_LOG(logger) << "Loading texture " << assetPath.string();
    SDL_Surface* const surface = IMG_Load(assetPath.string().c_str());
    if (!surface) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to load image " << assetPath.string() << " for texture. " << IMG_GetError();
        return;
    }

    //create texture from the given surface
    texture = SDL_CreateTextureFromSurface(*videoContext, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to create texture from surface " << assetPath.string() << ". " << IMG_GetError();
        return;
    }

    //query texture dimensions
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to query texture " << assetPath.string() << " dimensions. " << SDL_GetError();
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Texture " << assetPath.string() << " loaded.";
}

Cosmic::Core::TextureAsset::~TextureAsset() {
    BOOST_LOG_FUNCTION();

    if (!isLoaded()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "Texture is not loaded.";
        return;
    }

    SDL_DestroyTexture(texture);
}

bool Cosmic::Core::TextureAsset::isLoaded() const {
    return texture != nullptr;
}

int Cosmic::Core::TextureAsset::getWidth() const {
    return width;
}

int Cosmic::Core::TextureAsset::getHeight() const {
    return height;
}

void Cosmic::Core::TextureAsset::copy(boost::shared_ptr<VideoContext> videoContext, int x, int y) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopy(*videoContext, texture, nullptr, &destination) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy texture. " << SDL_GetError();
    }
}

void Cosmic::Core::TextureAsset::copyRotated(boost::shared_ptr<VideoContext> videoContext, int x, int y, double angle) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopyEx(*videoContext, texture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy and rotate texture. " << SDL_GetError();
    }
}

Cosmic::Core::TextureAsset::operator SDL_Texture*() {
    return texture;
}
