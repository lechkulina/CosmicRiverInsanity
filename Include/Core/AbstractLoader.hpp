/*
 *  AbstractLoader.hpp
 *
 *  Created on: 19 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTLOADER_HPP_
#define ABSTRACTLOADER_HPP_

#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class AbstractLoader {
        public:
            AbstractLoader() = default;
            AbstractLoader(const AbstractLoader&) = delete;
            AbstractLoader& operator=(const AbstractLoader&) = delete;

            virtual ~AbstractLoader() {}
            virtual bool request(const AbstractRequest& request) =0;
    };

}

}

#endif /* ABSTRACTLOADER_HPP_ */
