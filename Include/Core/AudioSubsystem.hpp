/*
 *  AudioSubsystem.hpp
 *
 *  Created on: 5 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef AUDIOSUBSYSTEM_HPP_
#define AUDIOSUBSYSTEM_HPP_

#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    namespace Keywords {

        BOOST_PARAMETER_NAME((frequency, Tags) frequency)
        BOOST_PARAMETER_NAME((format, Tags) format)
        BOOST_PARAMETER_NAME((channels, Tags) channels)
        BOOST_PARAMETER_NAME((chunkSize, Tags) chunkSize)

    }

    namespace Private {

        class AudioSubsystem : public AbstractSubsystem {
            public:
                AudioSubsystem(int frequency, Uint16 format, int channels, int chunkSize);
                virtual ~AudioSubsystem();

                virtual bool isInitialized() const;

            protected:
                template<class ArgumentsPack>
                explicit AudioSubsystem(const ArgumentsPack& arguments) :
                    AudioSubsystem(
                        arguments[Keywords::frequency | MIX_DEFAULT_FREQUENCY],
                        arguments[Keywords::format | MIX_DEFAULT_FORMAT],
                        arguments[Keywords::channels | 2],
                        arguments[Keywords::chunkSize | 4096]
                    ) {
                }

            private:
                Common::Logger logger;
                SDL_version version;
                int frequency;
                Uint16 format;
                int channels;
        };

    }

    class AudioSubsystem : public Private::AudioSubsystem {
        public:
            BOOST_PARAMETER_CONSTRUCTOR(
                AudioSubsystem, (Private::AudioSubsystem), Keywords::Tags,
                (optional
                    (frequency, (int))
                    (format, (Uint16))
                    (channels, (int))
                    (chunkSize, (int))
                )
            )
    };

}

}

#endif /* AUDIOSUBSYSTEM_HPP_ */
