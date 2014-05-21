/*
 *  AbstractRequest.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTREQUEST_HPP_
#define ABSTRACTREQUEST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
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

            AbstractRequest();
            AbstractRequest(const AbstractRequest&) = delete;
            AbstractRequest& operator=(const AbstractRequest&) = delete;

            virtual ~AbstractRequest();

            virtual const std::string& getAssetName() const =0;
            virtual const boost::filesystem::path& getAssetPath() const =0;
            virtual void execute() =0;

        protected:
            OnResponseReady::Signal responseReady;
            OnResponseFailed::Signal responseFailed;
    };

}

}

#endif /* ABSTRACTREQUEST_HPP_ */
