/*
 * TexturesCache.hpp
 *
 * Created on: 10 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef TEXTURESCACHE_HPP_
#define TEXTURESCACHE_HPP_

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractLoader.hpp>
#include <Core/AbstractCache.hpp>
#include <Core/VideoContext.hpp>
#include <Core/TextureAsset.hpp>

namespace Cosmic {

namespace Core {

    class TexturesCache : public AbstractCache {
        /*public:
            explicit TexturesCache(boost::shared_ptr<AbstractLoader> loader);

            bool request(boost::shared_ptr<VideoContext> videoContext, const std::string& name,
                            const boost::filesystem::path& path);
            bool insert(const std::string& name, boost::shared_ptr<Texture> texture);

        private:
            typedef std::map<std::string, boost::shared_ptr<Texture> > Textures;

            Common::Logger logger;
            boost::shared_ptr<AbstractLoader> loader;
            Textures textures;*/
    };

}

}

#endif /* TEXTURESCACHE_HPP_ */
