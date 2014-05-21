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
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Core/AbstractAsset.hpp>
#include <Core/AbstractRequest.hpp>
#include <Core/VideoContext.hpp>

namespace Cosmic {

namespace Core {

    //! Executes a request to load texture from a local file system.
    class TextureRequest : public AbstractRequest {
        public:
            TextureRequest(boost::shared_ptr<VideoContext> videoContext, const std::string& assetName,
                                   const boost::filesystem::path& assetPath);

            virtual const std::string& getAssetName() const;
            virtual const boost::filesystem::path& getAssetPath() const;
            virtual void execute();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (boost::shared_ptr<TextureRequest>), static make, Keywords::Tags,
                (required
                    (videoContext, (boost::shared_ptr<VideoContext>))
                    (assetName, (const std::string&))
                    (assetPath, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<TextureRequest>(videoContext, assetName, assetPath);
            }

        private:
            boost::shared_ptr<VideoContext> videoContext;
            std::string assetName;
            boost::filesystem::path assetPath;
    };

}

}

#endif /* TEXTUREREQUEST_HPP_ */
