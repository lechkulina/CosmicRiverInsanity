/*
 * ImageSubsystem.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <SDL_image.h>
#include <Core/ImageSubsystem.hpp>

Cosmic::Core::ImageSubsystem::ImageSubsystem() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem),
    initialized(false) {
    BOOST_LOG_FUNCTION();

    //initialize SDL image library with JPEG and PNG support
    BOOST_LOG(logger) << "Initializing SDL_image library.";
    const int requestedFlags = IMG_INIT_JPG|IMG_INIT_PNG;
    const int acquiredFlags = IMG_Init(requestedFlags);
    if ((acquiredFlags & requestedFlags) != requestedFlags) {
        BOOST_LOG_SEV(logger, Common::Severity::Critical)
            << "Failed to initialize SDL_image with JPEG and PNG support. " << IMG_GetError();
        IMG_Quit();
        return;
    }

    //retrieve version of SDL image library that we are currently linked against
    memcpy(&version, IMG_Linked_Version(), sizeof(SDL_version));
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "SDL_image " << int(version.major) << "." << int(version.minor) << "." << int(version.patch) << " initialized.";

    initialized = true;
}

Cosmic::Core::ImageSubsystem::~ImageSubsystem() {
    BOOST_LOG_FUNCTION();

    //check if we are initialized
    if (!isInitialized()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug) << "SDL_image library was not initialized.";
        return;
    }

    //clean up SDL_image library stuff
    BOOST_LOG(logger) << "Cleaning up SDL_image library.";
    IMG_Quit();
}

bool Cosmic::Core::ImageSubsystem::isInitialized() const {
    return initialized;
}
