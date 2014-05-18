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
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <Common/Logging.hpp>
#include <Core/VideoContext.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class Texture : public AbstractAsset {
        public:
            Texture(boost::shared_ptr<VideoContext> videoContext,
                    const boost::filesystem::path& path);
            virtual ~Texture();

            virtual bool isLoaded() const;

            int getWidth() const;
            int getHeight() const;

            void copy(boost::shared_ptr<VideoContext> videoContext, int x, int y);
            void copyRotated(boost::shared_ptr<VideoContext> videoContext, int x, int y, double angle);

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
