/*
 *  LoggingSubsystem.hpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef LOGGINGSUBSYSTEM_HPP_
#define LOGGINGSUBSYSTEM_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class LoggingSubsystem;
    typedef boost::shared_ptr<LoggingSubsystem> LoggingSubsystemSharedPtr;
    typedef boost::weak_ptr<LoggingSubsystem> LoggingSubsystemWeakPtr;

    class LoggingSubsystem : public AbstractSubsystem {
        public:
            LoggingSubsystem(const std::string& path, int rotationSize);
            virtual ~LoggingSubsystem();

            virtual bool isInitialized() const;

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (LoggingSubsystemSharedPtr), static make, Keywords::Tags,
                (required
                    (path, (std::string))
                )
                (optional
                    (rotationSize, (int), 5 * 1024 * 1024)
                )
            ) {
                return boost::make_shared<LoggingSubsystem>(path, rotationSize);
            }
        private:
            typedef boost::log::core Core;
            typedef boost::log::sinks::text_file_backend TextFileBackend;
            typedef boost::log::sinks::synchronous_sink<TextFileBackend> SynchronousSink;

            boost::shared_ptr<SynchronousSink> sink;
    };

}

}

#endif /* LOGGINGSUBSYSTEM_HPP_ */
