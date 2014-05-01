/*
 * ComposedSubsystem.hpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef COMPOSEDSUBSYSTEM_HPP_
#define COMPOSEDSUBSYSTEM_HPP_

#include <list>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

namespace Cosmic {

namespace Core {

    class ComposedSubsystem : public AbstractSubsystem {
        public:
            ComposedSubsystem();
            virtual ~ComposedSubsystem();

            bool compose(boost::shared_ptr<AbstractSubsystem> subsystem);
            virtual bool isInitialized() const;

        private:
            typedef std::list<boost::shared_ptr<AbstractSubsystem> > SubsystemsList;
            typedef SubsystemsList::iterator SubsystemsIterator;
            typedef SubsystemsList::const_iterator SubsystemsConstIterator;

            Common::Logger logger;
            SubsystemsList subsystems;
    };

}

}

#endif /* COMPOSEDSUBSYSTEM_HPP_ */
