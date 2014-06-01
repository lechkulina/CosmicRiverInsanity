/*
 *  AbstractLoader.hpp
 *
 *  Created on: 19 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTLOADER_HPP_
#define ABSTRACTLOADER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/signals2.hpp>
#include <Core/AbstractAsset.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class AbstractLoader;
    typedef boost::shared_ptr<AbstractLoader> AbstractLoaderSharedPtr;
    typedef boost::weak_ptr<AbstractLoader> AbstractLoaderWeakPtr;

    //! Base class for all assets loaders
    class AbstractLoader {
        protected:
            typedef boost::signals2::signal<void (AbstractAssetSharedPtr)> FinishedSignal;
            typedef boost::signals2::signal<void (float)> ProgressChangedSignal;

            FinishedSignal finishedSignal;
            ProgressChangedSignal progressChangedSignal;

        public:
            typedef FinishedSignal::slot_type FinishedSlot;
            typedef ProgressChangedSignal::slot_type ProgressChangedSlot;

            AbstractLoader() = default;
            AbstractLoader(const AbstractLoader&) = delete;
            AbstractLoader& operator=(const AbstractLoader&) = delete;

            virtual ~AbstractLoader();

            virtual boost::signals2::connection connectToFinished(const FinishedSlot& finishedSlot);
            virtual void disconnectFromFinished(const FinishedSlot& finishedSlot);
            virtual boost::signals2::connection connectToProgressChanged(const ProgressChangedSlot& progressChangedSlot);
            virtual void disconnectFromProgressChanged(const ProgressChangedSlot& progressChangedSlot);

            virtual bool pushRequest(AbstractRequestSharedPtr request) =0;
            virtual bool hasRequests() const =0;
            virtual void start() =0;
            virtual void stop() =0;
    };

}

}

#endif /* ABSTRACTLOADER_HPP_ */
