/*
 * AbstractAsset.hpp
 *
 * Created on: 17 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTASSET_HPP_
#define ABSTRACTASSET_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/filesystem.hpp>

namespace Cosmic {

namespace Core {

    class AbstractAsset;
    typedef boost::shared_ptr<AbstractAsset> AbstractAssetSharedPtr;
    typedef boost::weak_ptr<AbstractAsset> AbstractAssetWeakPr;

    class AbstractAsset {
        public:
            AbstractAsset() = default;
            AbstractAsset(const AbstractAsset&) = delete;
            AbstractAsset& operator=(const AbstractAsset&) = delete;

            virtual ~AbstractAsset();

            virtual const std::string& getName() const =0;
            virtual const boost::filesystem::path& getPath() const =0;
            virtual bool isLoaded() const =0;
    };

}

}

#endif /* ABSTRACTASSET_HPP_ */
