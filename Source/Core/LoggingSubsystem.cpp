/*
 *  LoggingSubsystem.cpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/time.hpp>
#include <Core/LoggingSubsystem.hpp>

Cosmic::Core::LoggingSubsystem::LoggingSubsystem(const std::string& fileName, int rotationSize) {
    using namespace boost;
    using namespace boost::log;

    //add global and thread specific attributes
    core::get()->add_global_attribute("TimeStamp", attributes::local_clock());
    core::get()->add_global_attribute("Scope", attributes::named_scope());

    //create sink backend
    shared_ptr<TextFileBackend> backend = make_shared<TextFileBackend>(
        keywords::file_name = fileName,
        keywords::rotation_size = rotationSize
    );

    //create sink frontend and set record formatter
    sink = make_shared<SynchronousSink>(backend);
    sink->set_formatter(
        expressions::stream
            << expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
            << expressions::if_(expressions::has_attr("Scope")) [
                 expressions::stream
                     << expressions::format_named_scope("Scope", keywords::format = "%n", keywords::depth = 1) << " "
            ]
            << " (" << Common::severity << ") "
            << expressions::smessage
    );

    //finally add sink so we could start logging some crazy shit...
    core::get()->add_sink(sink);
}

Cosmic::Core::LoggingSubsystem::~LoggingSubsystem() {
    using namespace boost::log;

    //remove our sink from logging core, Boost.Log should handle the rest
    core::get()->remove_sink(sink);
}

bool Cosmic::Core::LoggingSubsystem::isInitialized() const {
    return sink.use_count() > 0;
}
