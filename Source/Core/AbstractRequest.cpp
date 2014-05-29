/*
 *  AbstractRequest.cpp
 *
 *  Created on: 20 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractRequest.hpp>

Cosmic::Core::AbstractRequest::~AbstractRequest() {
}

boost::signals2::connection
Cosmic::Core::AbstractRequest::connectToFinished(const FinishedSlot& finishedSlot) {
    return finishedSignal.connect(finishedSlot);
}

void Cosmic::Core::AbstractRequest::disconnectFromFinished(const FinishedSlot& finishedSlot) {
    //finishedSignal.disconnect(finishedSlot);
}
