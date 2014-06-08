/*
 *  AudioSubsystem.hpp
 *
 *  Created on: 5 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef AUDIOSUBSYSTEM_HPP_
#define AUDIOSUBSYSTEM_HPP_

#include <SDL.h>
#include <SDL_mixer.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class AudioSubsystem;
    typedef boost::shared_ptr<AudioSubsystem> AudioSubsystemSharedPtr;
    typedef boost::weak_ptr<AudioSubsystem> AudioSubsystemWeakPtr;

    class AudioSubsystem : public AbstractSubsystem {
        public:
            AudioSubsystem(Sint32 frequency, Uint16 format, Sint32 channels, Sint32 chunkSize);
            virtual ~AudioSubsystem();

            virtual bool isInitialized() const;

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (AudioSubsystemSharedPtr), static make, Keywords::Tags,
                (optional
                    (frequency, (Sint32), MIX_DEFAULT_FREQUENCY)
                    (format, (Uint16), MIX_DEFAULT_FORMAT)
                    (channels, (Sint32), 2)
                    (chunkSize, (Sint32), 4096)
                )
            ) {
                return boost::make_shared<AudioSubsystem>(frequency, format, channels, chunkSize);
            }

        private:
            Common::Logger logger;
            SDL_version version;
            Sint32 frequency;
            Uint16 format;
            Sint32 channels;
    };

}

}

#endif /* AUDIOSUBSYSTEM_HPP_ */
