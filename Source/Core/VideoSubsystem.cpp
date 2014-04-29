/*
 *  VideoSubsystem.cpp
 *
 *  Created on: 30 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/VideoSubsystem.hpp>

Cosmic::Core::VideoSubsystem::VideoSubsystem() :
    window(nullptr),
    renderer(nullptr) {
}

Cosmic::Core::VideoSubsystem::~VideoSubsystem() {

}

void Cosmic::Core::VideoSubsystem::initialize(){
    BOOST_LOG_FUNCTION();
    if (isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Video subsystem has already been initialized";
        return;
    }

    //initialize SDL core stuff with the video subsystem
    BOOST_LOG_SEV(logger, Common::Severity::Trace)
        << "Initializing video subsystem and SDL library";
    if (SDL_Init(0) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL library. " << SDL_GetError();
        return;
    }
    SDL_version version;
    SDL_GetVersion(&version);
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << " initialized";

    //initialize video subsystem and disable screen saver
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL Video subsystem. " << SDL_GetError();
        return;
    }
    SDL_DisableScreenSaver();

    //create window for our insane game !
    if ((window = SDL_CreateWindow("Cosmic River Insanity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    800, 600, SDL_WINDOW_SHOWN)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create window. " << SDL_GetError();
        return;
    }

    //create renderer
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create renderer. " << SDL_GetError();
        return;
    }
}

void Cosmic::Core::VideoSubsystem::uninitialize() {
    BOOST_LOG_FUNCTION();
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Video subsystem has already been uninitialized";
        return;
    }

    BOOST_LOG_SEV(logger, Common::Severity::Trace)
        << "Uninitializing video subsystem and SDL library";
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

bool Cosmic::Core::VideoSubsystem::isInitialized() const {
    return SDL_WasInit(SDL_INIT_VIDEO) != 0;
}
