/*
 * Game.cpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

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

    //initialize all required subsystems
    composedSubsystem.compose(boost::make_shared<LoggingSubsystem>());
    composedSubsystem.compose(boost::make_shared<VideoSubsystem>());
    if (!composedSubsystem.isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize required subsystems.";
        return;
    }

    //create video context
    videoContext = boost::make_shared<VideoContext>();
    if (!videoContext->isReady()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create video context.";
        return;
    }
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
    videoContext->setDrawColor();
    videoContext->clear();

    switch(gameState) {
        case GameState::Running: {

        } break;

        default: {
            //TODO
        }
    }

    videoContext->present();
}
