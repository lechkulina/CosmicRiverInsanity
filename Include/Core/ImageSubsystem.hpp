/*
 * ImageSubsystem.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef IMAGESUBSYSTEM_HPP_
#define IMAGESUBSYSTEM_HPP_

#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class ImageSubsystem : public AbstractSubsystem {
        public:
            ImageSubsystem();
            virtual ~ImageSubsystem();

            virtual bool isInitialized() const;

        private:
            Common::Logger logger;
            SDL_version version;
            bool initialized;
    };

}

}

#endif /* IMAGESUBSYSTEM_HPP_ */
