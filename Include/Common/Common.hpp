/*
 * Common.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <boost/utility.hpp>
#include <boost/signals2.hpp>

#define COSMIC_UNUSED(x) (void)x

namespace Cosmic {

namespace Common {

    template<class S>
    class SignalAdapter {
        public:
            typedef S Signal;
            typedef typename Signal::slot_type Slot;
            typedef boost::signals2::connection Connection;

            explicit SignalAdapter(Signal& signal);

            Connection connect(const Slot& slot);
            void disconnect(const Slot& slot);

        private:
            Signal& signal;
    };

    template<class S>
    SignalAdapter<S>::SignalAdapter(Signal& signal) :
        signal(signal) {}

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

#endif /* COMMON_HPP_ */
