/*
 *  TextureRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef TEXTUREREQUEST_HPP_
#define TEXTUREREQUEST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractAsset.hpp>
#include <Core/AbstractRequest.hpp>
#include <Core/VideoContext.hpp>

namespace Cosmic {

namespace Core {

    class TextureRequest;
    typedef boost::shared_ptr<TextureRequest> TextureRequestSharedPtr;
    typedef boost::weak_ptr<TextureRequest> TextureRequestWeakPtr;

    //! Executes a request to load texture from a local file system.
    class TextureRequest : public AbstractRequest {
        public:
            TextureRequest(VideoContextSharedPtr videoContext, const std::string& name,
                               const boost::filesystem::path& path);

            virtual const std::string& getName() const;
            virtual const boost::filesystem::path& getPath() const;
            virtual void execute();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (TextureRequestSharedPtr), static make, Keywords::Tags,
                (required
                    (videoContext, (VideoContextSharedPtr))
                    (name, (const std::string&))
                    (path, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<TextureRequest>(videoContext, name, path);
            }

        private:
            VideoContextSharedPtr videoContext;
            std::string name;
            boost::filesystem::path path;
    };

}

}

#endif /* TEXTUREREQUEST_HPP_ */
