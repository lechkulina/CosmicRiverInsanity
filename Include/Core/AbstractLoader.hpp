/*
 *  AbstractLoader.hpp
 *
 *  Created on: 19 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTLOADER_HPP_
#define ABSTRACTLOADER_HPP_

#include <Common/SignalAdapter.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    //! Base class for all assets loaders
    class AbstractLoader {
        public:
            typedef Common::SignalAdapter<void (const AbstractLoader&, boost::shared_ptr<AbstractAsset>)> OnAssetReady;
            typedef Common::SignalAdapter<void (const AbstractLoader&, float)> OnProgressChanged;

            OnAssetReady onAssetReady;
            OnProgressChanged onProgressChanged;

            AbstractLoader();
            AbstractLoader(const AbstractLoader&) = delete;
            AbstractLoader& operator=(const AbstractLoader&) = delete;

            virtual ~AbstractLoader();

            virtual bool pushRequest(boost::shared_ptr<AbstractRequest> request) =0;
            virtual bool hasPendingRequests() const =0;
            virtual void execute() =0;

        protected:
            OnAssetReady::Signal assetReady;
            OnProgressChanged::Signal progressChanged;
    };

}

}

#endif /* ABSTRACTLOADER_HPP_ */
