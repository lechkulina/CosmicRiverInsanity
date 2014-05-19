/*
 *  TextureFileRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef TEXTUREFILEREQUEST_HPP_
#define TEXTUREFILEREQUEST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <Core/AbstractRequest.hpp>
#include <Core/VideoContext.hpp>

namespace Cosmic {

namespace Core {

    //! Executes a request to load texture from a local file system.
    class TextureFileRequest : public AbstractRequest {
        public:
            TextureFileRequest(boost::shared_ptr<VideoContext> videoContext,
                               const std::string& assetName,
                               const boost::filesystem::path& assetPath);

            virtual void execute();

        private:
            boost::shared_ptr<VideoContext> videoContext;
            boost::filesystem::path assetPath;
    };

}

}

#endif /* TEXTUREFILEREQUEST_HPP_ */
