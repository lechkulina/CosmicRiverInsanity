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

            virtual bool isInitialized() const;

        private:
            Common::Logger logger;
            SDL_version version;
            SDL_bool restoreScreenSaver;
    };

}

}

#endif /* VIDEOSUBSYSTEM_HPP_ */
