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

typedef boost::log::sinks::text_file_backend TextFileBackend;
typedef boost::log::sinks::synchronous_sink<TextFileBackend> SynchronousTextFileSink;

Cosmic::Core::Game::Game() :
    m_window(nullptr),
    m_renderer(nullptr),
    m_gameState(GameState::Startup) {

    //add global and thread specific attributes
    boost::shared_ptr<boost::log::core> core = boost::log::core::get();
    core->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());

    //create log sink before we start logging
    boost::shared_ptr<TextFileBackend> backend = boost::make_shared<TextFileBackend>(
        boost::log::keywords::file_name = "game.log",
        boost::log::keywords::rotation_size = 5 * 1024 * 1024
    );
    backend->auto_flush(true);

    boost::shared_ptr<SynchronousTextFileSink> sink = boost::make_shared<SynchronousTextFileSink>(backend);
    sink->set_formatter(
        boost::log::expressions::stream
            << "<" << boost::log::trivial::severity << "> "
            << boost::log::expressions::smessage
    );
    core->add_sink(sink);

    //initialize SDL core stuff
    if (SDL_Init(0) != 0) {
        BOOST_LOG_SEV(logger, SeverityLevel::Fatal) << "Failed to initialize SDL library";
        return;
    }

    SDL_version version;
    SDL_GetVersion(&version);
    BOOST_LOG_SEV(logger, SeverityLevel::Debug)
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
}

int Cosmic::Core::Game::execute() {
    m_gameState = GameState::Running;

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
