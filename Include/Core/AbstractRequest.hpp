/*
 *  AbstractRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTREQUEST_HPP_
#define ABSTRACTREQUEST_HPP_

#include <Common/SignalAdapter.hpp>
#include <Core/AbstractAsset.hpp>

namespace Cosmic {

namespace Core {

    //! Base class for all assets requests
    class AbstractRequest {
        public:
            typedef Common::SignalAdapter<void (const AbstractRequest&, boost::shared_ptr<AbstractAsset>)> OnResponseReady;
            typedef Common::SignalAdapter<void (const AbstractRequest&)> OnResponseFailed;

            OnResponseReady onResponseReady;
            OnResponseFailed onResponseFailed;

            explicit AbstractRequest(const std::string& assetName);
            AbstractRequest(const AbstractRequest&) = delete;
            AbstractRequest& operator=(const AbstractRequest&) = delete;

            virtual ~AbstractRequest();

            const std::string& getAssetName() const;
            virtual void execute() =0;

        protected:
            OnResponseReady::Signal responseReady;
            OnResponseFailed::Signal responseFailed;

        private:
            std::string assetName;
    };

}

}

#endif /* ABSTRACTREQUEST_HPP_ */
