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
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class Music;
    typedef boost::shared_ptr<Music> MusicSharedPtr;
    typedef boost::weak_ptr<Music> MusicWeakPtr;

    class Music : public AbstractAsset {
        public:
            explicit Music(const std::string& name,
                            const boost::filesystem::path& path);
            virtual ~Music();

            virtual const std::string& getName() const;
            virtual const boost::filesystem::path& getPath() const;
            virtual bool isLoaded() const;

            void play(int loops = 0);

            operator Mix_Music*();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (MusicSharedPtr), static make, Keywords::Tags,
                (required
                    (name, (const std::string&))
                    (path, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<Music>(name, path);
            }

        private:
            Common::Logger logger;
            std::string name;
            boost::filesystem::path path;
            Mix_Music* music;
    };

}

}

#endif /* MUSIC_HPP_ */
