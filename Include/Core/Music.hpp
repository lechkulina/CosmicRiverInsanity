/*
 *  Music.hpp
 *
 *  Created on: 6 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <SDL.h>
#include <SDL_mixer.h>
#include <boost/filesystem.hpp>
#include <Common/Logging.hpp>

namespace Cosmic {

namespace Core {

    class Music {
        public:
            explicit Music(const boost::filesystem::path& path);
            virtual ~Music();

            virtual bool isLoaded() const;

            void play(int loops = 0);

            operator Mix_Music*();

        private:
            Common::Logger logger;
            Mix_Music* music;
    };

}

}

#endif /* MUSIC_HPP_ */
