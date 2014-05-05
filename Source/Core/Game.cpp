/*
 * Game.cpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <SDL.h>
#include <cstdlib>
#include <boost/make_shared.hpp>
#include <Core/Game.hpp>
#include <Core/LoggingSubsystem.hpp>
#include <Core/VideoSubsystem.hpp>
#include <Core/ImageSubsystem.hpp>
#include <Core/AudioSubsystem.hpp>

Cosmic::Core::Game::Game() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Game),
    gameState(GameState::Startup) {
    BOOST_LOG_FUNCTION();

    //initialize all required subsystems
    composedSubsystem.compose(boost::make_shared<LoggingSubsystem>());
    composedSubsystem.compose(boost::make_shared<VideoSubsystem>());
    composedSubsystem.compose(boost::make_shared<ImageSubsystem>());
    composedSubsystem.compose(boost::make_shared<AudioSubsystem>());
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

    texture = boost::make_shared<Texture>(videoContext, "./playerShip1_green.png");
    spacecraft = boost::make_shared<Cosmic::Game::Spacecraft>(texture);
}

Cosmic::Core::Game::~Game() {
}

bool Cosmic::Core::Game::isInitialized() const {
    return composedSubsystem.isInitialized() && videoContext->isReady();
}

int Cosmic::Core::Game::execute() {
    BOOST_LOG_FUNCTION();

    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Game is not initialized.";
        return EXIT_FAILURE;
    }

    BOOST_LOG(logger) << "Start main loop";
    gameState = GameState::Running;

    const float fps = 60.0f;
    const float deltaTime = (1 / fps) * 1000;
    const float maxAccumulatedTime = 50.0f;
    float accumulatedTime = 0.0f;
    float startTime = SDL_GetTicks();

    while(gameState != GameState::Shutdown) {
        SDL_Event event;
        if (SDL_PollEvent(&event) > 0) {
            handleEvent(event);
        } else {
            //avoid spiral of death
            const float currentTime = SDL_GetTicks();
            accumulatedTime += currentTime - startTime;
            if (accumulatedTime > maxAccumulatedTime) {
                accumulatedTime = maxAccumulatedTime;
            }
            startTime = currentTime;

            while(accumulatedTime > deltaTime) {
                updateFrame(deltaTime);
                accumulatedTime -= deltaTime;
            }

            renderFrame();
            resetFrame();
        }
    }

    BOOST_LOG(logger) << "Stop main loop";
    return EXIT_SUCCESS;
}

void Cosmic::Core::Game::handleEvent(const SDL_Event& event) {
    const float mag = 0.02;
    switch(event.type) {
        case SDL_QUIT: {
            gameState = GameState::Shutdown;
        } break;

        case SDL_KEYDOWN: {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    gameState = GameState::Shutdown;
                } break;
                case SDLK_RIGHT: {
                    spacecraft->setLeftEngineThrust(0.0);
                    spacecraft->setRightEngineThrust(-mag);
                } break;
                case SDLK_LEFT: {
                    spacecraft->setLeftEngineThrust(-mag);
                    spacecraft->setRightEngineThrust(0.0);
                } break;
                case SDLK_UP: {
                    spacecraft->setLeftEngineThrust(mag);
                    spacecraft->setRightEngineThrust(mag);
                } break;
                case SDLK_DOWN: {
                    spacecraft->setLeftEngineThrust(-mag);
                    spacecraft->setRightEngineThrust(-mag);
                } break;
                case SDLK_SPACE: {
                    spacecraft->setLeftEngineThrust(0.0f);
                    spacecraft->setRightEngineThrust(0.0f);
                } break;
            }
        } break;
    }
}

void Cosmic::Core::Game::updateFrame(float deltaTime) {
    spacecraft->update(deltaTime);
}

void Cosmic::Core::Game::renderFrame() {
    videoContext->setDrawColor();
    videoContext->clear();

    switch(gameState) {
        case GameState::Running: {
            spacecraft->render(videoContext);
        } break;

        default: {
            //TODO
        }
    }

    videoContext->present();
}

void Cosmic::Core::Game::resetFrame() {
    spacecraft->reset();
}
