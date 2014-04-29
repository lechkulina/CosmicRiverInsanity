/*
 * Game.cpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <SDL.h>
#include <Core/Game.hpp>

Cosmic::Core::Game::Game() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = "Game"
    ),
    m_window(nullptr),
    m_renderer(nullptr),
    m_gameState(GameState::Startup) {
    BOOST_LOG_FUNCTION();
    subsystemsManager.initialize();

    //initialize SDL core stuff
    if (SDL_Init(0) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL library";
        return;
    }

    SDL_version version;
    SDL_GetVersion(&version);
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << " initialized";

    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_DisableScreenSaver();

    m_window = SDL_CreateWindow("Cosmic River Insanity",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                800, 600,
                                SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

Cosmic::Core::Game::~Game() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    subsystemsManager.uninitialize();
}

int Cosmic::Core::Game::execute() {
    BOOST_LOG_FUNCTION();
    m_gameState = GameState::Running;

    BOOST_LOG_SEV(logger, Common::Severity::Trace) << "Starting main loop";

    while(m_gameState != GameState::Shutdown) {
        SDL_Event event;
        if (SDL_PollEvent(&event) > 0) {
            handleEvent(event);
        } else {
            processFrame();
        }
    }

    return EXIT_SUCCESS;
}

void Cosmic::Core::Game::handleEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_QUIT: {
            m_gameState = GameState::Shutdown;
        } break;

        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_gameState = GameState::Shutdown;
            }
        } break;
    }
}

void Cosmic::Core::Game::processFrame() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    switch(m_gameState) {
        case GameState::Running: {

        } break;

        default: {
            //TODO
        }
    }

    SDL_RenderPresent(m_renderer);
}
