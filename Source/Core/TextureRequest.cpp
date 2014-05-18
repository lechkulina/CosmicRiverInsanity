/*
 *  TextureRequest.cpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/TextureRequest.hpp>

Cosmic::Core::TextureRequest::TextureRequest(TexturesCache& texturesCache, boost::shared_ptr<VideoContext> videoContext,
                                             const std::string& name, const boost::filesystem::path& path) :
    texturesCache(texturesCache),
    videoContext(videoContext),
    name(name),
    path(path) {
}

void Cosmic::Core::TextureRequest::execute() const {
    boost::shared_ptr<Texture> texture =  boost::make_shared<Texture>(videoContext, path);
    if (texture->isLoaded()) {
        texturesCache.insert(name, texture);
    }
}

