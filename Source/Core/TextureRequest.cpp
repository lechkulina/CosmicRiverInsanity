/*
 *  TextureRequest.cpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/TextureRequest.hpp>
#include <Core/TextureAsset.hpp>

Cosmic::Core::TextureRequest::TextureRequest(boost::shared_ptr<VideoContext> videoContext, const std::string& assetName,
                                                 const boost::filesystem::path& assetPath) :
    videoContext(videoContext),
    assetName(assetName),
    assetPath(assetPath) {
}

const std::string& Cosmic::Core::TextureRequest::getAssetName() const {
    return assetName;
}

const boost::filesystem::path& Cosmic::Core::TextureRequest::getAssetPath() const {
    return assetPath;
}

void Cosmic::Core::TextureRequest::execute() {
    boost::shared_ptr<TextureAsset> textureAsset =  TextureAsset::make(videoContext, assetPath);
    if (textureAsset->isLoaded()) {
        responseReady(*this, textureAsset);
    } else {
        responseFailed(*this);
    }
}
