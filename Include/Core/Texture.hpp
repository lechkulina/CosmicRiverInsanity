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
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/VideoContext.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class Texture;
    typedef boost::shared_ptr<Texture> TextureSharedPtr;
    typedef boost::weak_ptr<Texture> TextureWeakPr;

    class Texture : public AbstractAsset {
        public:
            Texture(VideoContextSharedPtr videoContext, const std::string& name,
                        const boost::filesystem::path& path);
            virtual ~Texture();

            virtual const std::string& getName() const;
            virtual const boost::filesystem::path& getPath() const;
            virtual bool isLoaded() const;

            int getWidth() const;
            int getHeight() const;

            void copy(VideoContextSharedPtr videoContext, int x, int y);
            void copyRotated(VideoContextSharedPtr videoContext, int x, int y, double angle);

            operator SDL_Texture*();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (TextureSharedPtr), static make, Keywords::Tags,
                (required
                    (videoContext, (VideoContextSharedPtr))
                    (name, (const std::string&))
                    (path, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<Texture>(videoContext, name, path);
            }

        private:
            Common::Logger logger;
            std::string name;
            boost::filesystem::path path;
            SDL_Texture* texture;
            int width;
            int height;
    };

}

}

#endif /* TEXTURE_HPP_ */
