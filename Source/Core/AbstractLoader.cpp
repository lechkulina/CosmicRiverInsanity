/*
 *  AbstractLoader.cpp
 *
 *  Created on: 20 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractLoader.hpp>

Cosmic::Core::AbstractLoader::AbstractLoader() :
    onAssetReady(assetReady),
    onProgressChanged(progressChanged) {
}

Cosmic::Core::AbstractLoader::~AbstractLoader() {
}
