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
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    namespace Keywords {

        BOOST_PARAMETER_NAME((disableScreenSaver, Tags) disableScreenSaver)
        BOOST_PARAMETER_NAME((hideCursor, Tags) hideCursor)

    }

    class VideoSubsystem : public AbstractSubsystem {
        public:
            VideoSubsystem(bool disableScreenSaver, bool hideCursor);
            virtual ~VideoSubsystem();

            virtual bool isInitialized() const;

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (boost::shared_ptr<VideoSubsystem>), static make, Keywords::Tags,
                (optional
                    (disableScreenSaver, (bool), true)
                    (hideCursor, (bool), true)
                )
            ) {
                return boost::make_shared<VideoSubsystem>(disableScreenSaver, hideCursor);
            }

        private:
            Common::Logger logger;
            SDL_version version;
            SDL_bool restoreScreenSaver;
            SDL_bool restoreCursor;
    };

}

}

#endif /* VIDEOSUBSYSTEM_HPP_ */
