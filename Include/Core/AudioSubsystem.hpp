/*
 *  AudioSubsystem.hpp
 *
 *  Created on: 5 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef AUDIOSUBSYSTEM_HPP_
#define AUDIOSUBSYSTEM_HPP_

#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class AudioSubsystem : public AbstractSubsystem {
        public:
            AudioSubsystem();
            virtual ~AudioSubsystem();

            virtual bool isInitialized() const;

        private:
            Common::Logger logger;
            SDL_version version;
            int frequency;
            Uint16 format;
            int channels;
            bool initialized;
    };

}

}

#endif /* AUDIOSUBSYSTEM_HPP_ */
