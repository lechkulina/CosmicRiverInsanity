/*
 *  StaticCache.cpp
 *
 *  Created on: 1 cze 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/StaticCache.hpp>

Cosmic::Core::StaticCache::StaticCache() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources) {
}

bool Cosmic::Core::StaticCache::isEmpty() const {
    return assets.empty();
}

bool Cosmic::Core::StaticCache::insert(AbstractAssetSharedPtr asset) {
    BOOST_LOG_FUNCTION();

    if (!asset) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Empty asset was passed to the cache - ignoring it.";
        return false;
    }

    //we have to ensure that only valid assets are stored in cache
    const std::string& name = asset->getName();
    if (!asset->isLoaded()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Asset " << name << " is not loaded - ignoring it.";
        return false;
    }

    //reject duplicates
    BOOST_LOG(logger) << "Inserting asset " << name << " into cache.";
    if (assets.find(name) != assets.end()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Asset " << name << " has already been inserted - ignoring it.";
        return false;
    }

    assets.insert(std::make_pair(name, asset));
    return true;
}

bool Cosmic::Core::StaticCache::contains(const std::string& name) const {
    return assets.find(name) != assets.end();
}

Cosmic::Core::AbstractAssetSharedPtr
Cosmic::Core::StaticCache::get(const std::string& name) {
    AssetsIterator asset = assets.find(name);
    if (asset != assets.end()) {
        *asset;
    }
    return AbstractAssetSharedPtr();
}
