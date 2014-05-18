/*
 *  AbstractRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTREQUEST_HPP_
#define ABSTRACTREQUEST_HPP_

namespace Cosmic {

namespace Core {

    class AbstractRequest {
        public:
            virtual ~AbstractRequest() {}
            virtual void execute() const =0;
    };

}

}

#endif /* ABSTRACTREQUEST_HPP_ */
