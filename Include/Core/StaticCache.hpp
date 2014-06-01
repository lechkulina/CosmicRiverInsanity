/*
 *  StaticCache.hpp
 *
 *  Created on: 1 cze 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef STATICCACHE_HPP_
#define STATICCACHE_HPP_

#include <map>
#include <Common/Logging.hpp>
#include <Core/AbstractCache.hpp>

namespace Cosmic {

namespace Core {

    class StaticCache;
    typedef boost::shared_ptr<StaticCache> StaticCacheSharedPtr;
    typedef boost::weak_ptr<StaticCache> StaticCacheWeakPtr;

    class StaticCache : public AbstractCache {
        public:
            StaticCache();

            virtual bool isEmpty() const;
            virtual bool insert(AbstractAssetSharedPtr asset);
            virtual bool contains(const std::string& name) const;
            virtual AbstractAssetSharedPtr get(const std::string& name);

        private:
            typedef std::map<std::string, AbstractAssetSharedPtr> Assets;
            typedef Assets::iterator AssetsIterator;
            typedef Assets::const_iterator AssetsConstIterator;

            Common::Logger logger;
            Assets assets;
    };

}

}

#endif /* STATICCACHE_HPP_ */
