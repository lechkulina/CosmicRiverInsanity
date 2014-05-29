/*
 * Texture.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/Texture.hpp>

Cosmic::Core::Texture::Texture(VideoContextSharedPtr videoContext, const std::string& name,
                                const boost::filesystem::path& path) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    name(name),
    path(path),
    texture(nullptr),
    width(0),
    height(0) {
    BOOST_LOG_FUNCTION();

    //load and decode image file
    BOOST_LOG(logger) << "Loading texture " << name << " from " << path.string();
    SDL_Surface* const surface = IMG_Load(path.string().c_str());
    if (!surface) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to load texture " << name << " from " << path.string() << ". " << IMG_GetError();
        return;
    }

    //create texture from the given surface
    texture = SDL_CreateTextureFromSurface(*videoContext, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to create texture " << name << " from surface " << path.string() << ". " << IMG_GetError();
        return;
    }

    //query texture dimensions
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to query texture " << name << " for dimensions. " << SDL_GetError();
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Texture " << name << " from " << path.string() << " is loaded.";
}

Cosmic::Core::Texture::~Texture() {
    BOOST_LOG_FUNCTION();

    if (!isLoaded()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Texture " << name << " is not loaded.";
        return;
    }

    SDL_DestroyTexture(texture);
}

const std::string& Cosmic::Core::Texture::getName() const {
    return name;
}

const boost::filesystem::path& Cosmic::Core::Texture::getPath() const {
    return path;
}

bool Cosmic::Core::Texture::isLoaded() const {
    return texture != nullptr;
}

int Cosmic::Core::Texture::getWidth() const {
    return width;
}

int Cosmic::Core::Texture::getHeight() const {
    return height;
}

void Cosmic::Core::Texture::copy(VideoContextSharedPtr videoContext, int x, int y) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopy(*videoContext, texture, nullptr, &destination) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy texture " << name << ". " << SDL_GetError();
    }
}

void Cosmic::Core::Texture::copyRotated(VideoContextSharedPtr videoContext, int x, int y, double angle) {
    BOOST_LOG_FUNCTION();

    const SDL_Rect destination = {x, y, width, height};
    if (SDL_RenderCopyEx(*videoContext, texture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to copy and rotate texture " << name << ". " << SDL_GetError();
    }
}

Cosmic::Core::Texture::operator SDL_Texture*() {
    return texture;
}
