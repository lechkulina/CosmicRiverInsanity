/*
 * Texture.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <boost/filesystem.hpp>
#include <Common/Logging.hpp>
#include <Core/VideoContext.hpp>

namespace Cosmic {

namespace Core {

    class Texture {
        public:
            Texture(boost::shared_ptr<VideoContext> videoContext, const boost::filesystem::path& path);
            virtual ~Texture();

            virtual bool isLoaded() const;

            virtual void copy(boost::shared_ptr<VideoContext> videoContext, int x, int y);
            virtual void copyRotated(boost::shared_ptr<VideoContext> videoContext, int x, int y, double angle);

            operator SDL_Texture*();

        private:
            Common::Logger logger;
            SDL_Texture* texture;
            int width;
            int height;
    };

}

}

#endif /* TEXTURE_HPP_ */
