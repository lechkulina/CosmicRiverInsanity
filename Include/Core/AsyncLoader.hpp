/*
 *  AsyncLoader.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ASYNCLOADER_HPP_
#define ASYNCLOADER_HPP_

#include <Core/AbstractLoader.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class AsyncLoader : public AbstractLoader {
        public:
            virtual bool request(const AbstractRequest& request) {
                request.execute();
                return true;
            }
    };

}

}

#endif /* ASYNCLOADER_HPP_ */
