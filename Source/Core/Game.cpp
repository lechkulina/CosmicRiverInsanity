/*
 * Game.cpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <SDL.h>
#include <Core/Game.hpp>
#include <Core/LoggingSubsystem.hpp>
#include <Core/VideoSubsystem.hpp>

Cosmic::Core::Game::Game() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Game),
    gameState(GameState::Startup) {
    BOOST_LOG_FUNCTION();

    //create and initialize all required subsystems
    composedSubsystem.compose(boost::make_shared<LoggingSubsystem>());
    composedSubsystem.compose(boost::make_shared<VideoSubsystem>());
}

Cosmic::Core::Game::~Game() {
}

int Cosmic::Core::Game::execute() {
    BOOST_LOG_FUNCTION();
    gameState = GameState::Running;

    BOOST_LOG_SEV(logger, Common::Severity::Trace) << "Starting main loop";

    while(gameState != GameState::Shutdown) {
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
            gameState = GameState::Shutdown;
        } break;

        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                gameState = GameState::Shutdown;
            }
        } break;
    }
}

void Cosmic::Core::Game::processFrame() {
    //SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    //SDL_RenderClear(m_renderer);

    switch(gameState) {
        case GameState::Running: {

        } break;

        default: {
            //TODO
        }
    }

    //SDL_RenderPresent(m_renderer);
}
