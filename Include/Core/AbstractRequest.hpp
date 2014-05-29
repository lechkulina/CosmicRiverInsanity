/*
 *  AbstractRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTREQUEST_HPP_
#define ABSTRACTREQUEST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/signals2.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    class AbstractRequest;
    typedef boost::shared_ptr<AbstractRequest> AbstractRequestSharedPtr;
    typedef boost::weak_ptr<AbstractRequest> AbstractRequestWeakPtr;

    //! Base class for all assets requests
    class AbstractRequest {
        protected:
            typedef boost::signals2::signal<void (AbstractAssetSharedPtr)> FinishedSignal;

            FinishedSignal finishedSignal;

        public:
            typedef FinishedSignal::slot_type FinishedSlot;

            AbstractRequest() = default;
            AbstractRequest(const AbstractRequest&) = delete;
            AbstractRequest& operator=(const AbstractRequest&) = delete;

            virtual ~AbstractRequest();

            virtual boost::signals2::connection connectToFinished(const FinishedSlot& finishedSlot);
            virtual void disconnectFromFinished(const FinishedSlot& finishedSlot);

            virtual void execute() =0;
    };

}

}

#endif /* ABSTRACTREQUEST_HPP_ */
