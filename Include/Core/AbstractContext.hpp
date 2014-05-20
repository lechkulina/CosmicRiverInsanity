/*
 * AbstractContext.hpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTCONTEXT_HPP_
#define ABSTRACTCONTEXT_HPP_

namespace Cosmic {

namespace Core {

    class AbstractContext {
        public:
            AbstractContext() = default;
            AbstractContext(const AbstractContext&) = delete;
            AbstractContext& operator=(const AbstractContext&) = delete;

            virtual ~AbstractContext() {}

            virtual bool isReady() const =0;
    };

}

}

#endif /* ABSTRACTCONTEXT_HPP_ */
