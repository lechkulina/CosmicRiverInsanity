/*
 *  LoggingSubsystem.cpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/manipulators.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/time.hpp>
#include <Core/LoggingSubsystem.hpp>

Cosmic::Core::LoggingSubsystem::LoggingSubsystem() :
    initialized(false) {
}

Cosmic::Core::LoggingSubsystem::~LoggingSubsystem() {
    uninitialize();
}

void Cosmic::Core::LoggingSubsystem::initialize() {
    namespace log = boost::log;
    namespace sinks = boost::log::sinks;
    namespace attributes = boost::log::attributes;
    namespace keywords = boost::log::keywords;
    namespace expressions = boost::log::expressions;

    //add global and thread specific attributes
    boost::shared_ptr<log::core> core = log::core::get();
    core->add_global_attribute("TimeStamp", attributes::local_clock());
    core->add_global_attribute("Scope", attributes::named_scope());

    //create sink backend
    boost::shared_ptr<sinks::text_file_backend> backend =
            boost::make_shared<sinks::text_file_backend>(
        keywords::file_name = "game%3N.log",
        keywords::rotation_size = 5 * 1024 * 1024
    );

    //create sink frontend
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_file_backend> > sink =
            boost::make_shared<sinks::synchronous_sink<sinks::text_file_backend> >(backend);
    sink->set_formatter(
        expressions::stream
            << expressions::if_(expressions::has_attr("TimeStamp")) [
                 expressions::stream
                     << expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
                     << " "
            ]
            << expressions::if_(expressions::has_attr("Scope")) [
                 expressions::stream
                     << expressions::format_named_scope(
                         "Scope",
                         keywords::format = "%n",
                         keywords::depth = 1)
                     << " "
            ]
            << expressions::if_ (expressions::has_attr("Severity")) [
                  expressions::stream
                      << " (" << Common::severity << ")"
                      << " "
               ]
            << expressions::smessage
    );

    //finally add sink so we could start logging some crazy shit...
    core->add_sink(sink);

    initialized = true;
}

void Cosmic::Core::LoggingSubsystem::uninitialize() {
    //do nothing, Boost.Log should handle this
}

bool Cosmic::Core::LoggingSubsystem::isInitialized() const {
    return initialized;
}
