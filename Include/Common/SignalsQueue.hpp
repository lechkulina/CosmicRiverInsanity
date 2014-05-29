/*
 *  SignalsQueue.hpp
 *
 *  Created on: 26 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef SIGNALSQUEUE_HPP_
#define SIGNALSQUEUE_HPP_

#include <list>
#include <boost/thread.hpp>
#include <boost/function.hpp>

namespace Cosmic {

namespace Common {

    class SignalsQueue {
        public:
            typedef boost::function<void ()> Callback;

            void dispatch(const Callback& callback);
            bool poll();

        private:
            typedef std::list<Callback> Callbacks;

            Callbacks callbacks;
            boost::mutex mutex;
    };

}

}

#endif /* SIGNALSQUEUE_HPP_ */
