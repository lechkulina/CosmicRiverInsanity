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
            virtual ~AbstractSubsystem() {}

            virtual void initialize() =0;
            virtual void uninitialize() =0;

            virtual bool isInitialized() const =0;
    };

}

}

#endif /* ABSTRACTSUBSYSTEM_HPP_ */
