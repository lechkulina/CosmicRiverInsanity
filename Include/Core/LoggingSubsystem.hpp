/*
 *  LoggingSubsystem.hpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef LOGGINGSUBSYSTEM_HPP_
#define LOGGINGSUBSYSTEM_HPP_

#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class LoggingSubsystem : public AbstractSubsystem {
        public:
            LoggingSubsystem();
            virtual ~LoggingSubsystem();

            virtual void initialize();
            virtual void uninitialize();

            virtual bool isInitialized() const;

        private:
            bool initialized;
    };

}

}

#endif /* LOGGINGSUBSYSTEM_HPP_ */
