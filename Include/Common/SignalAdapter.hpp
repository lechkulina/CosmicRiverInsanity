/*
 *  SignalAdapter.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef SIGNALADAPTER_HPP_
#define SIGNALADAPTER_HPP_

#include <boost/signals2.hpp>

namespace Cosmic {

namespace Common {

    template<class S>
    class SignalAdapter {
        public:
            typedef S Signal;
            typedef typename Signal::slot_type Slot;
            typedef boost::signals2::connection Connection;

            explicit SignalAdapter(Signal& signal);
            SignalAdapter(const SignalAdapter&) = delete;
            SignalAdapter& operator=(const SignalAdapter&) = delete;

            Connection connect(const Slot& slot);
            void disconnect(const Slot& slot);

        private:
            Signal& signal;
    };

    template<class S>
    SignalAdapter<S>::SignalAdapter(Signal& signal) :
        signal(signal) {
    }

    template<class S>
    inline typename SignalAdapter<S>::Connection
    SignalAdapter<S>::connect(const typename SignalAdapter<S>::Slot& slot) {
        return signal.connect(slot);
    }

    template<class S>
    inline void SignalAdapter<S>::disconnect(const Slot& slot) {
        signal.disconnect(slot);
    }
}

}

#endif /* SIGNALADAPTER_HPP_ */
