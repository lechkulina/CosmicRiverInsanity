/*
 *  AudioSubsystem.cpp
 *
 *  Created on: 5 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <SDL.h>
#include <SDL_mixer.h>
#include <Core/AudioSubsystem.hpp>

Cosmic::Core::Private::AudioSubsystem::AudioSubsystem(int frequency, Uint16 format, int channels, int chunkSize) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem),
    frequency(0),
    format(0),
    channels(0),
    initialized(false) {
    BOOST_LOG_FUNCTION();

    //initialize SDL mixer library with OGG/Vorbis support
    BOOST_LOG(logger) << "Initializing SDL_mixer library with OGG/Vorbis support.";
    const int requestedFlags = MIX_INIT_OGG;
    const int acquiredFlags = Mix_Init(requestedFlags);
    if ((acquiredFlags & requestedFlags) != requestedFlags) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL_mixer with OGG/Vorbis support. " << Mix_GetError();
        Mix_Quit();
        return;
    }

    //retrieve version of SDL mixer library that we are currently linked against
    memcpy(&version, Mix_Linked_Version(), sizeof(SDL_version));
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL_mixer " << int(version.major) << "." << int(version.minor) << "." << int(version.patch) << " initialized with OGG/Vorbis support.";

    //open audio device
    BOOST_LOG(logger) << "Opening audio device.";
    if (Mix_OpenAudio(frequency, format, channels, chunkSize) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to open audio device. " << Mix_GetError();
        Mix_Quit();
        return;
    }

    //get the chunk decoders info
    const int chunkDecoders = Mix_GetNumChunkDecoders();
    BOOST_LOG(logger) << "There are " << chunkDecoders << " chunk decoders available.";
    for (int i=0; i < chunkDecoders; ++i) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Found " << Mix_GetChunkDecoder(i) << " chunk decoder.";
    }

    //get music decoders info
    const int musicDecoders = Mix_GetNumMusicDecoders();
    BOOST_LOG(logger) << "There are " << musicDecoders << " music decoders available.";
    for (int i=0; i < musicDecoders; ++i) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Found " << Mix_GetMusicDecoder(i) << " music decoder.";
    }

    //query the actual format that is in use by the opened audio device
    if (Mix_QuerySpec(&this->frequency, &this->format, &this->channels) == 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to query audio format that is in use by the current audio device. " << Mix_GetError();
        Mix_CloseAudio();
        Mix_Quit();
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Audio device with frequency " << this->frequency << ", format " << this->format
        << " and number of channels " << this->channels << " opened.";

    initialized = true;
}

Cosmic::Core::Private::AudioSubsystem::~AudioSubsystem() {
    BOOST_LOG_FUNCTION();

    //check if we are initialized
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "SDL_mixer library was not initialized.";
        return;
    }

    //close audio device
    BOOST_LOG(logger) << "Closing audio device.";
    Mix_CloseAudio();

    //clean up SDL_mixer library stuff
    BOOST_LOG(logger) << "Cleaning up SDL_mixer library.";
    Mix_Quit();
}

bool Cosmic::Core::Private::AudioSubsystem::isInitialized() const {
    return initialized;
}
