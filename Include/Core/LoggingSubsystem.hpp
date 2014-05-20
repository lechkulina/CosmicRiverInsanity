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
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    namespace Keywords {

        BOOST_PARAMETER_NAME((fileName, Tags) fileName)
        BOOST_PARAMETER_NAME((rotationSize, Tags) rotationSize)

    }

    class LoggingSubsystem : public AbstractSubsystem {
        public:
            LoggingSubsystem(const std::string& fileName, int rotationSize);
            virtual ~LoggingSubsystem();

            virtual bool isInitialized() const;

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (boost::shared_ptr<LoggingSubsystem>), static make, Keywords::Tags,
                (required
                    (fileName, (std::string))
                )
                (optional
                    (rotationSize, (int), 5 * 1024 * 1024)
                )
            ) {
                return boost::make_shared<LoggingSubsystem>(fileName, rotationSize);
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
