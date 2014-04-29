/*
 *  VideoSubsystem.hpp
 *
 *  Created on: 30 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef VIDEOSUBSYSTEM_HPP_
#define VIDEOSUBSYSTEM_HPP_

#include <SDL.h>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class VideoSubsystem : public AbstractSubsystem {
        public:
            VideoSubsystem();
            virtual ~VideoSubsystem();

            virtual void initialize();
            virtual void uninitialize();

            virtual bool isInitialized() const;

        private:
            boost::log::sources::severity_channel_logger<Common::Severity, std::string> logger;
            SDL_Window* window;
            SDL_Renderer* renderer;
    };

}

}

#endif /* VIDEOSUBSYSTEM_HPP_ */
