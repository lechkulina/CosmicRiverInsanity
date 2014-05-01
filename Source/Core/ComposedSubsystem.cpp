/*
 * ComposedSubsystem.cpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <cassert>
#include <Core/ComposedSubsystem.hpp>

Cosmic::Core::ComposedSubsystem::ComposedSubsystem() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem) {
}

Cosmic::Core::ComposedSubsystem::~ComposedSubsystem() {
    //we have to force the order in which we are destroying our subsystems
    for (SubsystemsIterator iter = subsystems.begin(); iter != subsystems.end(); ++iter) {
        boost::shared_ptr<AbstractSubsystem> subsystem = *iter;
        subsystem.reset();
    }
}

bool Cosmic::Core::ComposedSubsystem::compose(boost::shared_ptr<AbstractSubsystem> subsystem) {
    BOOST_LOG_FUNCTION();

    //check if the passed subsystem is valid first
    if (!subsystem) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "An empty subsystem passed to the composed subsystem.";
        return false;
    }

    //push this subsystem to the front, because of the order in which they will be deleted in our destructor
    subsystems.push_front(subsystem);
    return subsystem->isInitialized();
}

bool Cosmic::Core::ComposedSubsystem::isInitialized() const {
    //this is our reasonable default...
    if (subsystems.empty()) {
        return false;
    }

    for (SubsystemsConstIterator iter = subsystems.begin(); iter != subsystems.end(); ++iter) {
        boost::shared_ptr<AbstractSubsystem> subsystem = *iter;
        assert(subsystem && "compose method should guarantee that all stored pointers are valid");
        if (!subsystem->isInitialized()) {
            return false;
        }
    }

    return true;
}

