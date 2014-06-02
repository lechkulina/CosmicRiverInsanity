/*
 *  MusicRequest.cpp
 *
 *  Created on: 3 cze 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/MusicRequest.hpp>
#include <Core/Music.hpp>

Cosmic::Core::MusicRequest::MusicRequest(const std::string& name,
                                           const boost::filesystem::path& path) :
    name(name),
    path(path) {
}

bool Cosmic::Core::MusicRequest::isValid() const {
    return !name.empty() && !path.empty() && boost::filesystem::exists(path);
}

const std::string& Cosmic::Core::MusicRequest::getName() const {
    return name;
}

const boost::filesystem::path& Cosmic::Core::MusicRequest::getPath() const {
    return path;
}

void Cosmic::Core::MusicRequest::execute() {
    finishedSignal(Music::make(name, path));
}


