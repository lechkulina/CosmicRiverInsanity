/*
 *  AbstractCache.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTCACHE_HPP_
#define ABSTRACTCACHE_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class AbstractCache;
    typedef boost::shared_ptr<AbstractCache> AbstractCacheSharedPtr;
    typedef boost::weak_ptr<AbstractCache> AbstractCacheWeakPtr;

    class AbstractCache {
        public:
            AbstractCache() = default;
            AbstractCache(const AbstractCache&) = delete;
            AbstractCache& operator=(const AbstractCache&) = delete;

            virtual ~AbstractCache();

            virtual bool isEmpty() const =0;
            virtual bool insert(AbstractAssetSharedPtr asset) =0;
            virtual bool contains(const std::string& name) const =0;
            virtual AbstractAssetSharedPtr get(const std::string& name) =0;

            template<class Asset>
            boost::shared_ptr<Asset> fetch(const std::string& name) {
                return boost::static_pointer_cast<Asset>(get(name));
            }
    };
}

}

#endif /* ABSTRACTCACHE_HPP_ */
