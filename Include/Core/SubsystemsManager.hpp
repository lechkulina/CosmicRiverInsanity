/*
 *  SubsystemsManager.hpp
 *
 *  Created on: 29 kwi 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef SUBSYSTEMSMANAGER_HPP_
#define SUBSYSTEMSMANAGER_HPP_

#include <list>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class SubsystemsManager : public AbstractSubsystem {
        public:
            SubsystemsManager();
            virtual ~SubsystemsManager();

            void request(boost::shared_ptr<AbstractSubsystem> subsystem);
            bool hasPending() const;

            virtual void initialize();
            virtual void uninitialize();

            virtual bool isInitialized() const;

        private:
            typedef std::list<boost::shared_ptr<AbstractSubsystem> > SubsystemsList;
            typedef SubsystemsList::iterator SubsystemsIterator;

            Common::Logger logger;
            SubsystemsList pendingSubsystems;
    };
}

}


#endif /* SUBSYSTEMSMANAGER_HPP_ */
