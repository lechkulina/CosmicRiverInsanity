/*
 *  SubsystemsManager.cpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Core/SubsystemsManager.hpp>
#include <Core/LoggingSubsystem.hpp>

Cosmic::Core::SubsystemsManager::SubsystemsManager() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Subsystem
    ) {
    //push the most essential subsystems here
    pendingSubsystems.push_back(boost::make_shared<LoggingSubsystem>());
}

Cosmic::Core::SubsystemsManager::~SubsystemsManager() {

}

void Cosmic::Core::SubsystemsManager::request(boost::shared_ptr<AbstractSubsystem> subsystem) {
    pendingSubsystems.push_back(subsystem);
}

bool Cosmic::Core::SubsystemsManager::hasPending() const {
    return !pendingSubsystems.empty();
}

void Cosmic::Core::SubsystemsManager::initialize() {
    for (SubsystemsIterator iter = pendingSubsystems.begin(); iter != pendingSubsystems.end(); ++iter) {
        boost::shared_ptr<AbstractSubsystem> subsystem = *iter;
        subsystem->initialize();
    }
}

void Cosmic::Core::SubsystemsManager::uninitialize() {
    for (SubsystemsIterator iter = pendingSubsystems.begin(); iter != pendingSubsystems.end(); ++iter) {
        boost::shared_ptr<AbstractSubsystem> subsystem = *iter;
        subsystem->uninitialize();
    }
}

bool Cosmic::Core::SubsystemsManager::isInitialized() const {
    //TODO make this more civilized
    return true;
}
