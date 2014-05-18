/*
 * AbstractAsset.cpp
 *
 * Created on: 18 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractAsset.hpp>

Cosmic::Core::AbstractAsset::AbstractAsset() :
    onLoad(onLoadSignal),
    onUnload(onUnloadSignal) {

}

Cosmic::Core::AbstractAsset::~AbstractAsset() {

}

