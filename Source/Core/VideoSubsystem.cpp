/*
 *  VideoSubsystem.cpp
 *
 *  Created on: 30 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/VideoSubsystem.hpp>

Cosmic::Core::VideoSubsystem::VideoSubsystem() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem
    ),
    restoreScreenSaver(SDL_FALSE),
    window(nullptr),
    renderer(nullptr) {
}

Cosmic::Core::VideoSubsystem::~VideoSubsystem() {

}

void Cosmic::Core::VideoSubsystem::initialize(){
    BOOST_LOG_FUNCTION();
    if (isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Video subsystem has already been initialized.";
        return;
    }

    //initialize SDL core stuff with the video subsystem
    BOOST_LOG_SEV(logger, Common::Severity::Trace)
        << "Initializing SDL library and video subsystem.";
    if (SDL_Init(0) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL library. " << SDL_GetError();
        return;
    }
    SDL_version version;
    SDL_GetVersion(&version);
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL " << int(version.major) << "." << int(version.minor) << "." << int(version.patch) << " initialized";

    //initialize video subsystem
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL Video subsystem. " << SDL_GetError();
        SDL_Quit();
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Video subsystem initialized with " << SDL_GetCurrentVideoDriver() << " display driver.";

    //create and rise window for our insane game !
    if ((window = SDL_CreateWindow("Cosmic River Insanity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    800, 600, SDL_WINDOW_SHOWN)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create window. " << SDL_GetError();
        SDL_Quit();
        return;
    }
    SDL_RaiseWindow(window);
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Window with ID " << SDL_GetWindowID(window) << " created.";

    //create renderer
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create renderer. " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    //disable screen saver and hide cursor
    restoreScreenSaver = SDL_IsScreenSaverEnabled();
    SDL_DisableScreenSaver();
    SDL_ShowCursor(SDL_DISABLE);
}

void Cosmic::Core::VideoSubsystem::uninitialize() {
    BOOST_LOG_FUNCTION();
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Video subsystem has already been uninitialized";
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Trace)
        << "Uninitializing video subsystem and SDL library.";

    //restore screen saver state
    if (restoreScreenSaver == SDL_TRUE) {
        SDL_DisableScreenSaver();
        restoreScreenSaver = SDL_FALSE;
    }

    //destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    //destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    //this will uninitialize all currently initialized SDL subsystems !
    SDL_Quit();
}

bool Cosmic::Core::VideoSubsystem::isInitialized() const {
    return SDL_WasInit(SDL_INIT_VIDEO) != 0;
}
