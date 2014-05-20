/*
 *  VideoSubsystem.cpp
 *
 *  Created on: 30 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/VideoSubsystem.hpp>

Cosmic::Core::VideoSubsystem::VideoSubsystem(bool disableScreenSaver, bool hideCursor) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem),
    restoreScreenSaver(SDL_FALSE),
    restoreCursor(SDL_FALSE) {
    BOOST_LOG_FUNCTION();

    //initialize SDL core stuff together with the video subsystem
    BOOST_LOG(logger) << "Initializing SDL library.";
    if (SDL_Init(0) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL library. " << SDL_GetError();
        return;
    }

    //retrieve version of SDL that we are currently linked against
    memset(&version, 0, sizeof(SDL_version));
    SDL_GetVersion(&version);
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL " << int(version.major) << "." << int(version.minor) << "." << int(version.patch) << " initialized.";

    //initialize video subsystem
    BOOST_LOG(logger) << "Initializing video subsystem.";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL Video subsystem. " << SDL_GetError();
        SDL_Quit();
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Video subsystem initialized with " << SDL_GetCurrentVideoDriver() << " display driver.";

    //disable screen saver
    if (disableScreenSaver) {
        restoreScreenSaver = SDL_IsScreenSaverEnabled();
        SDL_DisableScreenSaver();
    }

    //hide cursor
    if (hideCursor) {
        restoreCursor = SDL_ShowCursor(SDL_QUERY) == 1 ? SDL_TRUE : SDL_FALSE;
        SDL_ShowCursor(SDL_DISABLE);
    }
}

Cosmic::Core::VideoSubsystem::~VideoSubsystem() {
    BOOST_LOG_FUNCTION();

    //check if we are initialized
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "Video subsystem was not initialized.";
        return;
    }

    //restore screen saver state
    if (restoreScreenSaver == SDL_TRUE) {
        SDL_EnableScreenSaver();
    }

    //restore cursor state
    if (restoreCursor == SDL_TRUE) {
        SDL_ShowCursor(SDL_ENABLE);
    }

    //clean up video subsystem
    BOOST_LOG(logger) << "Cleaning up video subsystem.";
    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    //clean up SDL library and any remaining subsystems
    BOOST_LOG(logger) << "Cleaning up SDL library.";
    SDL_Quit();
}

bool Cosmic::Core::VideoSubsystem::isInitialized() const {
    return SDL_WasInit(SDL_INIT_VIDEO) != 0;
}
