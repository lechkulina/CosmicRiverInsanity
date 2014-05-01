/*
 * Logging.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/manipulators.hpp>

namespace Cosmic {

namespace Common {

    enum class Severity : int {
        Trace,
        Debug,
        Warning,
        Error,
        Critical
    };

    enum class Channel : int {
        Game,
        Subsystem,
        Context
    };

    BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", Severity)
    BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", Channel)

    typedef boost::log::sources::severity_channel_logger<Severity, Channel> Logger;

    template<class CharT>
    boost::log::basic_formatting_ostream<CharT>&
    operator<<(boost::log::basic_formatting_ostream<CharT>& stream,
               const boost::log::to_log_manip<Severity, tag::severity>& manip) {
        switch(manip.get()) {
            case Severity::Trace:
                return stream << "Trace";
            case Severity::Debug:
                return stream << "Debug";
            case Severity::Warning:
                return stream << "Warning";
            case Severity::Error:
                return stream << "Error";
            case Severity::Critical:
                return stream << "Critical";
        }
        return stream << "Unknown";
    }

    template<class CharT>
    boost::log::basic_formatting_ostream<CharT>&
    operator<<(boost::log::basic_formatting_ostream<CharT>& stream,
               const boost::log::to_log_manip<Channel, tag::channel>& manip) {
        switch(manip.get()) {
            case Channel::Game:
                return stream << "Game";
            case Channel::Subsystem:
                return stream << "Subsystem";
            case Channel::Context:
                return stream << "Context";
        }
        return stream << "Unknown";
    }
}

}

#endif /* LOGGING_HPP_ */
