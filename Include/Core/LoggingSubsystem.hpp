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

    namespace Private {

        class LoggingSubsystem : public AbstractSubsystem {
            public:
                LoggingSubsystem(const std::string& fileName, int rotationSize);
                virtual ~LoggingSubsystem();

                virtual bool isInitialized() const;

            protected:
                template<class ArgumentsPack>
                explicit LoggingSubsystem(const ArgumentsPack& arguments) :
                    LoggingSubsystem(
                        arguments[Keywords::fileName],
                        arguments[Keywords::rotationSize | (5 * 1024 * 1024)]
                    ) {
                }

            private:
                typedef boost::log::core Core;
                typedef boost::log::sinks::text_file_backend TextFileBackend;
                typedef boost::log::sinks::synchronous_sink<TextFileBackend> SynchronousSink;

                boost::shared_ptr<Core> core;
                boost::shared_ptr<SynchronousSink> sink;
        };

    }

    class LoggingSubsystem : public Private::LoggingSubsystem {
        public:
            BOOST_PARAMETER_CONSTRUCTOR(
                LoggingSubsystem, (Private::LoggingSubsystem), Keywords::Tags,
                (required
                    (fileName, (std::string))
                )
                (optional
                    (rotationSize, (int))
                )
            )
    };

}

}

#endif /* LOGGINGSUBSYSTEM_HPP_ */
