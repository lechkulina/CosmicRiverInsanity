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
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class VideoSubsystem;
    typedef boost::shared_ptr<VideoSubsystem> VideoSubsystemSharedPtr;
    typedef boost::weak_ptr<VideoSubsystem> VideoSubsystemWeakPtr;

    class VideoSubsystem : public AbstractSubsystem {
        public:
            VideoSubsystem(bool disableScreenSaver, bool hideCursor);
            virtual ~VideoSubsystem();

            virtual bool isInitialized() const;

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (VideoSubsystemSharedPtr), static make, Keywords::Tags,
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
