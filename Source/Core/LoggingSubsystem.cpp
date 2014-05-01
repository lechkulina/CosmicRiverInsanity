/*
 *  LoggingSubsystem.cpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <boost/make_shared.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/time.hpp>
#include <Core/LoggingSubsystem.hpp>

Cosmic::Core::LoggingSubsystem::LoggingSubsystem() :
    core(boost::log::core::get()) {

    //add global and thread specific attributes
    core->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
    core->add_global_attribute("Scope", boost::log::attributes::named_scope());

    //create sink backend
    boost::shared_ptr<TextFileBackend> backend = boost::make_shared<TextFileBackend>(
        boost::log::keywords::file_name = "game%3N.log",
        boost::log::keywords::rotation_size = 5 * 1024 * 1024
    );

    //create sink frontend and set record formatter
    sink = boost::make_shared<SynchronousSink>(backend);
    sink->set_formatter(
        boost::log::expressions::stream
            << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
            << boost::log::expressions::if_(boost::log::expressions::has_attr("Scope")) [
                 boost::log::expressions::stream
                     << boost::log::expressions::format_named_scope(
                         "Scope",
                         boost::log::keywords::format = "%n",
                         boost::log::keywords::depth = 1)
                     << " "
            ]
            << " (" << Common::severity << ") "
            << boost::log::expressions::smessage
    );

    //finally add sink so we could start logging some crazy shit...
    core->add_sink(sink);
}

Cosmic::Core::LoggingSubsystem::~LoggingSubsystem() {
    //remove our sink from logging core, Boost.Log should handle the rest
    core->remove_sink(sink);
}

bool Cosmic::Core::LoggingSubsystem::isInitialized() const {
    return sink;
}
