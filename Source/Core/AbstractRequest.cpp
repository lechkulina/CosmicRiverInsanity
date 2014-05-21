/*
 *  AbstractRequest.cpp
 *
 *  Created on: 20 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractRequest.hpp>

Cosmic::Core::AbstractRequest::AbstractRequest() :
    onResponseReady(responseReady),
    onResponseFailed(responseFailed) {
}

Cosmic::Core::AbstractRequest::~AbstractRequest() {
}
