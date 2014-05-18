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
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/tuple/tuple.hpp>
#include <Common/Common.hpp>
#include <Common/Logging.hpp>
#include <Core/VideoContext.hpp>
#include <Core/Texture.hpp>

namespace Cosmic {

namespace Core {

    class TexturesCache {
        public:
            TexturesCache();

            void pushRequest(const std::string& name, const boost::filesystem::path& path);
            bool hasPendingRequests() const;
            void load(boost::shared_ptr<VideoContext> videoContext);

            bool contains(const std::string& name) const;
            boost::shared_ptr<Texture> fetch(const std::string& name);

        private:
            typedef boost::tuple<std::string, boost::filesystem::path> PendingRequest;
            typedef std::list<PendingRequest> PendingRequests;
            typedef std::map<std::string, boost::shared_ptr<Texture> > Textures;

            Common::Logger logger;
            PendingRequests pendingRequests;
            Textures textures;
    };

}

}

#endif /* TEXTURESCACHE_HPP_ */
