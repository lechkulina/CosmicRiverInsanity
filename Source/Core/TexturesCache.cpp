/*
 * TexturesCache.cpp
 *
 * Created on: 18 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Core/TexturesCache.hpp>
#include <Core/TextureRequest.hpp>

Cosmic::Core::TexturesCache::TexturesCache::TexturesCache(boost::shared_ptr<AbstractLoader> loader) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    loader(loader) {

}

bool Cosmic::Core::TexturesCache::request(boost::shared_ptr<VideoContext> videoContext, const std::string& name,
                                            const boost::filesystem::path& path) {
    BOOST_LOG_FUNCTION();
    loader->request(TextureRequest(*this, videoContext, name, path));
    return true;
}

bool Cosmic::Core::TexturesCache::insert(const std::string& name, boost::shared_ptr<Texture> texture) {
    BOOST_LOG_FUNCTION();

    //warn about and reject duplicates
    BOOST_LOG(logger) << "Inserting texture " << name << " into cache.";
    if (textures.find(name) != textures.end()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Texture " << name << " has already been inserted.";
        return false;
    }

    textures.insert(std::make_pair(name, texture));
    return true;
}
