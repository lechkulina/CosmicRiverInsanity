/*
 * Texture.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/Texture.hpp>

Cosmic::Core::Texture::Texture(boost::shared_ptr<VideoContext> videoContext, const boost::filesystem::path& path) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    texture(nullptr),
    width(0),
    height(0) {
    BOOST_LOG_FUNCTION();

    //load and decode image file
    BOOST_LOG(logger) << "Loading texture " << path.string();
    SDL_Surface* const surface = IMG_Load(path.string().c_str());
    if (!surface) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to load image " << path.string() << " for texture. " << IMG_GetError();
        return;
    }

    //create texture from the given surface
    texture = SDL_CreateTextureFromSurface(*videoContext, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to create texture from surface " << path.string() << ". " << IMG_GetError();
        return;
    }

    //query texture dimensions
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to query texture " << path.string() << " dimensions. " << SDL_GetError();
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Texture " << path.string() << " loaded.";
}

Cosmic::Core::Texture::~Texture() {
    BOOST_LOG_FUNCTION();

    if (!isLoaded()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "Texture is not loaded.";
        return;
    }

    SDL_DestroyTexture(texture);
}

bool Cosmic::Core::Texture::isLoaded() const {
    return texture != nullptr;
}

void Cosmic::Core::Texture::copy(boost::shared_ptr<VideoContext> videoContext, int x, int y) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopy(*videoContext, texture, nullptr, &destination) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy texture. " << SDL_GetError();
    }
}

void Cosmic::Core::Texture::copyRotated(boost::shared_ptr<VideoContext> videoContext,int x, int y, double angle) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopyEx(*videoContext, texture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy and rotate texture. " << SDL_GetError();
    }
}

Cosmic::Core::Texture::operator SDL_Texture*() {
    return texture;
}
