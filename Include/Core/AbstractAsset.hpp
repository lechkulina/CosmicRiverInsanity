/*
 * AbstractAsset.hpp
 *
 * Created on: 17 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTASSET_HPP_
#define ABSTRACTASSET_HPP_

namespace Cosmic {

namespace Core {

    class AbstractAsset {
        public:
            AbstractAsset() = default;
            AbstractAsset(const AbstractAsset&) = delete;
            AbstractAsset& operator=(const AbstractAsset&) = delete;

            virtual ~AbstractAsset() {};
            virtual bool isLoaded() const =0;
    };

}

}

#endif /* ABSTRACTASSET_HPP_ */
