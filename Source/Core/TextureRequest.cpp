/*
 *  TextureRequest.cpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/TextureRequest.hpp>
#include <Core/Texture.hpp>

Cosmic::Core::TextureRequest::TextureRequest(VideoContextSharedPtr videoContext, const std::string& name,
                                                 const boost::filesystem::path& path) :
    videoContext(videoContext),
    name(name),
    path(path) {
}

bool Cosmic::Core::TextureRequest::isValid() const {
    return !name.empty() && !path.empty() && boost::filesystem::exists(path);
}

const std::string& Cosmic::Core::TextureRequest::getName() const {
    return name;
}

const boost::filesystem::path& Cosmic::Core::TextureRequest::getPath() const {
    return path;
}

void Cosmic::Core::TextureRequest::execute() {
    finishedSignal(Texture::make(videoContext, name, path));
}
