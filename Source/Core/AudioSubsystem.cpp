/*
 *  AudioSubsystem.cpp
 *
 *  Created on: 5 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/AudioSubsystem.hpp>

Cosmic::Core::AudioSubsystem::AudioSubsystem(Sint32 frequency, Uint16 format, Sint32 channels, Sint32 chunkSize) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem),
    frequency(0),
    format(0),
    channels(0) {
    BOOST_LOG_FUNCTION();

    //initialize audio SDL's audio subsystem - this is required by the Mix_OpenAudio
    BOOST_LOG(logger) << "Initializing audio subsystem.";
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL audio subsystem. " << SDL_GetError();
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Audio subsystem initialized with " << SDL_GetCurrentAudioDriver() << " audio driver.";

    //initialize SDL mixer library with OGG/Vorbis support
    BOOST_LOG(logger) << "Initializing SDL_mixer library with OGG/Vorbis support.";
    const int requestedFlags = MIX_INIT_OGG;
    const int acquiredFlags = Mix_Init(requestedFlags);
    if ((acquiredFlags & requestedFlags) != requestedFlags) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL_mixer with OGG/Vorbis support. " << Mix_GetError();
        Mix_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return;
    }

    //retrieve version of SDL mixer library that we are currently linked against
    memcpy(&version, Mix_Linked_Version(), sizeof(SDL_version));
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL_mixer " << int(version.major) << "." << int(version.minor) << "." << int(version.patch) << " with OGG/Vorbis support initialized.";

    //open audio device
    BOOST_LOG(logger) << "Opening audio device.";
    if (Mix_OpenAudio(frequency, format, channels, chunkSize) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to open audio device. " << Mix_GetError();
        Mix_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
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
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Audio device with frequency " << this->frequency << ", format " << this->format
        << " and number of channels " << this->channels << " opened.";
}

Cosmic::Core::AudioSubsystem::~AudioSubsystem() {
    BOOST_LOG_FUNCTION();

    //check if we are initialized
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "SDL_mixer library was not initialized.";
        return;
    }

    //close audio device
    BOOST_LOG(logger) << "Closing audio device.";
    Mix_CloseAudio();

    //clean up SDL_mixer library stuff
    BOOST_LOG(logger) << "Cleaning up SDL_mixer library.";
    Mix_Quit();

    //cleanup audio subsystem - this is not required but it won't harm
    BOOST_LOG(logger) << "Cleaning up audio subsystem.";
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool Cosmic::Core::AudioSubsystem::isInitialized() const {
    return SDL_WasInit(SDL_INIT_AUDIO) != 0;
}
