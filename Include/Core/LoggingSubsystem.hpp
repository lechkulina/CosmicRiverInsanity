/*
 *  LoggingSubsystem.hpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef LOGGINGSUBSYSTEM_HPP_
#define LOGGINGSUBSYSTEM_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class LoggingSubsystem : public AbstractSubsystem {
        public:
            LoggingSubsystem();
            virtual ~LoggingSubsystem();

            virtual bool isInitialized() const;

        private:
            typedef boost::log::core Core;
            typedef boost::log::sinks::text_file_backend TextFileBackend;
            typedef boost::log::sinks::synchronous_sink<TextFileBackend> SynchronousSink;

            boost::shared_ptr<Core> core;
            boost::shared_ptr<SynchronousSink> sink;
    };

}

}

#endif /* LOGGINGSUBSYSTEM_HPP_ */
