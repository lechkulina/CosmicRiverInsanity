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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractCache.hpp>

namespace Cosmic {

namespace Core {

    class StaticCache;
    typedef boost::shared_ptr<StaticCache> StaticCacheSharedPtr;
    typedef boost::weak_ptr<StaticCache> StaticCacheWeakPtr;

    class StaticCache : public AbstractCache {
        public:
            explicit StaticCache(bool ignoreInvalid = false,
                                    bool ignoreDuplicates = true);

            virtual bool isEmpty() const;
            virtual bool insert(AbstractAssetSharedPtr asset);
            virtual bool contains(const std::string& name) const;
            virtual AbstractAssetSharedPtr get(const std::string& name);

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (StaticCacheSharedPtr), static make, Keywords::Tags,
                (optional
                    (ignoreInvalid, (bool), false)
                    (ignoreDuplicates, (bool), true)
                )
            ) {
                return boost::make_shared<StaticCache>(ignoreInvalid, ignoreDuplicates);
            }

        private:
            typedef std::map<std::string, AbstractAssetSharedPtr> Assets;
            typedef Assets::iterator AssetsIterator;
            typedef Assets::const_iterator AssetsConstIterator;

            Common::Logger logger;
            Assets assets;
            bool ignoreInvalid;
            bool ignoreDuplicates;
    };

}

}

#endif /* STATICCACHE_HPP_ */
