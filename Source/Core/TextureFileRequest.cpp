/*
 *  TextureFileRequest.cpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/TextureFileRequest.hpp>
#include <Core/Texture.hpp>

Cosmic::Core::TextureFileRequest::TextureFileRequest(boost::shared_ptr<VideoContext> videoContext,
                                                     const std::string& assetName,
                                                     const boost::filesystem::path& assetPath) :
    AbstractRequest(assetName),
    videoContext(videoContext),
    assetPath(assetPath) {
}

void Cosmic::Core::TextureFileRequest::execute() {
    boost::shared_ptr<Texture> texture =  boost::make_shared<Texture>(videoContext, assetPath);
    if (texture->isLoaded()) {
        responseReady(*this, texture);
    } else {
        responseFailed(*this);
    }
}
