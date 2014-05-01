/*
 * VideoContext.cpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/VideoContext.hpp>

Cosmic::Core::VideoContext::VideoContext() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Context),
    window(nullptr),
    renderer(nullptr) {
    BOOST_LOG_FUNCTION();

    //create window for our insane game !
    BOOST_LOG(logger) << "Creating window.";
    if ((window = SDL_CreateWindow("Cosmic River Insanity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    800, 600, SDL_WINDOW_HIDDEN)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create window. " << SDL_GetError();
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Window with ID " << SDL_GetWindowID(window) << " created.";

    //create renderer
    BOOST_LOG(logger) << "Creating renderer.";
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to create renderer. " << SDL_GetError();
        SDL_DestroyWindow(window);
        window = nullptr;
        return;
    }

    //retrieve renderer information
    memset(&rendererInfo, 0, sizeof(SDL_RendererInfo));
    if (SDL_GetRendererInfo(renderer, &rendererInfo) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to retrieve renderer information" << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = nullptr;
        window = nullptr;
        return;
    }
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Renderer " << rendererInfo.name << " created.";

    //everything is OK now, show and rise our brand new window
    SDL_ShowWindow(window);
    SDL_RaiseWindow(window);
}

Cosmic::Core::VideoContext::~VideoContext() {
    BOOST_LOG_FUNCTION();

    //check if we are in a ready state
    if (!isReady()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "Video context is not ready.";
        return;
    }

    //destroy renderer
    BOOST_LOG(logger) << "Destroying renderer " << rendererInfo.name << ".";
    SDL_DestroyRenderer(renderer);

    //destroy window
    BOOST_LOG(logger) << "Destroying window with ID " << SDL_GetWindowID(window) << ".";
    SDL_DestroyWindow(window);
}

bool Cosmic::Core::VideoContext::isReady() const {
    return window != nullptr && renderer != nullptr;
}

void Cosmic::Core::VideoContext::setDrawColor(const Common::Color& color /*= Common::Color::Black*/) {
    BOOST_LOG_FUNCTION();

    if (SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to set draw color. " << SDL_GetError();
    }
}

void Cosmic::Core::VideoContext::clear() {
    BOOST_LOG_FUNCTION();

    if (SDL_RenderClear(renderer) != 0) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to clear the rendering target. " << SDL_GetError();
    }
}

void Cosmic::Core::VideoContext::present() {
    SDL_RenderPresent(renderer);
}
