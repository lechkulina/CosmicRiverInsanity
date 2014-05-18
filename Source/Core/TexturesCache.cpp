/*
 * TexturesCache.cpp
 *
 * Created on: 18 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <algorithm>
#include <Core/TexturesCache.hpp>

Cosmic::Core::TexturesCache::TexturesCache::TexturesCache() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources) {

}

void Cosmic::Core::TexturesCache::pushRequest(const std::string& name, const boost::filesystem::path& path) {
    BOOST_LOG_FUNCTION();

    PendingRequest request = boost::make_tuple(name, path);
    if (std::find(pendingRequests.begin(), pendingRequests.end(), request) != pendingRequests.end()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Texture " << name << " has already been added to the pending queue.";
    }
}

void Cosmic::Core::TexturesCache::load(boost::shared_ptr<VideoContext> videoContext) {

}

bool Cosmic::Core::TexturesCache::contains(const std::string& name) const {
    return textures.find(name) != textures.end();
}

boost::shared_ptr<Cosmic::Core::Texture>
Cosmic::Core::TexturesCache::fetch(const std::string& name) {
    auto texture = textures.find(name);
    if (texture != textures.end()) {
        texture->second;
    }
    return boost::shared_ptr<Texture>();
}

