/*
 *  AbstractSubsystem.hpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTSUBSYSTEM_HPP_
#define ABSTRACTSUBSYSTEM_HPP_

namespace Cosmic {

namespace Core {

    class AbstractSubsystem {
        public:
            AbstractSubsystem() = default;
            AbstractSubsystem(const AbstractSubsystem&) = delete;
            AbstractSubsystem& operator=(const AbstractSubsystem&) = delete;

            virtual ~AbstractSubsystem() {}

            virtual bool isInitialized() const =0;
    };

}

}

#endif /* ABSTRACTSUBSYSTEM_HPP_ */
