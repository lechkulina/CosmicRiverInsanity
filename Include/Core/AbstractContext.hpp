/*
 * AbstractContext.hpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTCONTEXT_HPP_
#define ABSTRACTCONTEXT_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace Cosmic {

namespace Core {

    class AbstractContext;
    typedef boost::shared_ptr<AbstractContext> AbstractContextSharedPtr;
    typedef boost::weak_ptr<AbstractContext> AbstractContextWeakPtr;

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
