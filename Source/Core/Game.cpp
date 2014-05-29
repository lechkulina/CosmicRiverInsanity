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
#include <boost/bind.hpp>
#include <Core/Game.hpp>

Cosmic::Core::Game::Game() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Game),
    gameState(GameState::Startup) {
    BOOST_LOG_FUNCTION();

    //create and initialize logging subsystem
    loggingSubsystem = LoggingSubsystem::make(
        Keywords::fileName = "game%3N.log",
        Keywords::rotationSize = 20 * 1024 * 1024
    );
    if (!loggingSubsystem->isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize logging subsystem.";
        return;
    }

    //create and initialize video subsystem
    videoSubsystem = VideoSubsystem::make(
        Keywords::hideCursor = false
    );
    if (!videoSubsystem->isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize video subsystem.";
        return;
    }

    //create and initialize image subsystem
    imageSubsystem = ImageSubsystem::make();
    if (!imageSubsystem->isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize image subsystem.";
        return;
    }

    //create and initialize audio subsystem
    audioSubsystem = AudioSubsystem::make(
        Keywords::frequency = MIX_DEFAULT_FREQUENCY
    );
    if (!audioSubsystem->isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize audio subsystem.";
        return;
    }

    //create and initialize video context
    videoContext = VideoContext::make(
        Keywords::windowTitle = "Cosmic River Insanity"
    );
    if (!videoContext->isReady()) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create video context.";
        return;
    }

    //create loader and cache
    asyncLoader = boost::make_shared<AsyncLoader>(signalsQueue);
    asyncLoader->start();
    asyncLoader->connectToFinished(boost::bind(&Game::finished, this, _1));

    //texturesCache = boost::make_shared<TexturesCache>(asyncLoader);

    asyncLoader->pushRequest(TextureRequest::make(videoContext, "player-ship", "./playerShip1_green.png"));
    asyncLoader->pushRequest(TextureRequest::make(videoContext, "player-ship2", "./playerShip2_red.png"));
    asyncLoader->pushRequest(TextureRequest::make(videoContext, "player-ship3", "./playerShip3_red.png"));
    asyncLoader->pushRequest(TextureRequest::make(videoContext, "ufo-green", "./ufoGreen.png"));

    //texturesCache->request(videoContext, "player-ship", "./playerShip1_green.png");


    texture = boost::make_shared<Texture>(videoContext, "PLAYER-SHIP", "./playerShip1_green.png");
    music = boost::make_shared<Music>("./ObservingTheStar.ogg");
    spacecraft = boost::make_shared<Cosmic::Game::Spacecraft>(texture);
}


void Cosmic::Core::Game::finished(AbstractAssetSharedPtr asset) {
    BOOST_LOG_FUNCTION();
    BOOST_LOG(logger) << "FINISHED name=" << asset->getName() << " path=" << asset->getPath() << " isLoaded=" << asset->isLoaded();
}

Cosmic::Core::Game::~Game() {
}

bool Cosmic::Core::Game::isInitialized() const {
    return videoContext->isReady();
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

    music->play();

    const float fps = 60.0f;
    const float deltaTime = (1 / fps) * 1000;
    const float maxAccumulatedTime = 50.0f;
    float accumulatedTime = 0.0f;
    float startTime = SDL_GetTicks();

    while(gameState != GameState::Shutdown) {
        SDL_Event event;
        if (SDL_PollEvent(&event) > 0) {
            handleEvent(event);
            continue;
        }

        if (signalsQueue.poll()) {
            continue;
        }

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
