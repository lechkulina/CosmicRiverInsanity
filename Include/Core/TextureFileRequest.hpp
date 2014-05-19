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
#include <boost/filesystem.hpp>
#include <Core/AbstractRequest.hpp>
#include <Core/TexturesCache.hpp>
#include <Core/VideoContext.hpp>

namespace Cosmic {

namespace Core {

    class TextureRequest : public AbstractRequest {
        public:
            TextureRequest(TexturesCache& texturesCache, boost::shared_ptr<VideoContext> videoContext,
                           const std::string& name, const boost::filesystem::path& path);
            virtual void execute() const;

        private:
            TexturesCache& texturesCache;
            boost::shared_ptr<VideoContext> videoContext;
            std::string name;
            boost::filesystem::path path;
    };

}

}

#endif /* TEXTUREREQUEST_HPP_ */
