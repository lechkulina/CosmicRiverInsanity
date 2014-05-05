/*
 *  Music.cpp
 *
 *  Created on: 6 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/Music.hpp>

Cosmic::Core::Music::Music(const boost::filesystem::path& path) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    music(nullptr) {
    BOOST_LOG_FUNCTION();

    //load music from file
    BOOST_LOG(logger) << "Loading music " << path.string();
    if ((music = Mix_LoadMUS(path.string().c_str())) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to load music " << path.string() << ". " << Mix_GetError();
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Music " << path.string() << " loaded.";
}

Cosmic::Core::Music::~Music() {
    BOOST_LOG_FUNCTION();

    if (!isLoaded()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "Music is not loaded.";
        return;
    }

    //explicitly halt music before freeing it - we do not want to block here
    Mix_HaltMusic();
    Mix_FreeMusic(music);
}

bool Cosmic::Core::Music::isLoaded() const {
    return music != nullptr;
}

void Cosmic::Core::Music::play(int loops /*= 0*/) {
    BOOST_LOG_FUNCTION();

    if (Mix_PlayMusic(music, loops) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to play music. " << Mix_GetError();
    }
}

Cosmic::Core::Music::operator Mix_Music*() {
    return music;
}
