/*
 * TextureAsset.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef TEXTUREASSET_HPP_
#define TEXTUREASSET_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Core/VideoContext.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class TextureAsset : public AbstractAsset {
        public:
            TextureAsset(boost::shared_ptr<VideoContext> videoContext, const boost::filesystem::path& assetPath);
            virtual ~TextureAsset();

            virtual bool isLoaded() const;

            int getWidth() const;
            int getHeight() const;

            void copy(boost::shared_ptr<VideoContext> videoContext, int x, int y);
            void copyRotated(boost::shared_ptr<VideoContext> videoContext, int x, int y, double angle);

            operator SDL_Texture*();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (boost::shared_ptr<TextureAsset>), static make, Keywords::Tags,
                (required
                    (videoContext, (boost::shared_ptr<VideoContext>))
                    (assetPath, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<TextureAsset>(videoContext, assetPath);
            }

        private:
            Common::Logger logger;
            SDL_Texture* texture;
            int width;
            int height;
    };

}

}

#endif /* TEXTUREASSET_HPP_ */
