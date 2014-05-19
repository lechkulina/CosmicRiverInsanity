/*
 *  AbstractRequest.cpp
 *
 *  Created on: 20 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractRequest.hpp>

Cosmic::Core::AbstractRequest::AbstractRequest(const std::string& assetName) :
    onResponseReady(responseReady),
    onResponseFailed(responseFailed),
    assetName(assetName) {
}

Cosmic::Core::AbstractRequest::~AbstractRequest() {
}

const std::string& Cosmic::Core::AbstractRequest::getAssetName() const {
    return assetName;
}
