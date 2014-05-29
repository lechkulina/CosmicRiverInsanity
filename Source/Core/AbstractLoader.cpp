/*
 *  AbstractLoader.cpp
 *
 *  Created on: 20 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AbstractLoader.hpp>

Cosmic::Core::AbstractLoader::~AbstractLoader() {
}

boost::signals2::connection
Cosmic::Core::AbstractLoader::connectToFinished(const FinishedSlot& finishedSlot) {
    return finishedSignal.connect(finishedSlot);
}

void Cosmic::Core::AbstractLoader::disconnectFromFinished(const FinishedSlot& finishedSlot) {
    //finishedSignal.disconnect(finishedSlot);
}

boost::signals2::connection
Cosmic::Core::AbstractLoader::connectToProgressChanged(const ProgressChangedSlot& progressChangedSlot) {
    return progressChangedSignal.connect(progressChangedSlot);
}

void Cosmic::Core::AbstractLoader::disconnectFromProgressChanged(const ProgressChangedSlot& progressChangedSlot) {
    //progressChangedSignal.disconnect(progressChangedSlot);
}
