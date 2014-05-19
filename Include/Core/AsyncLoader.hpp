/*
 *  AsyncLoader.hpp
 *
 *  Created on: 18 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef ASYNCLOADER_HPP_
#define ASYNCLOADER_HPP_

#include <list>
#include <Common/Logging.hpp>
#include <Core/AbstractLoader.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class AsyncLoader : public AbstractLoader {
        public:
            AsyncLoader();
            virtual ~AsyncLoader();

            virtual bool pushRequest(boost::shared_ptr<AbstractRequest> request);
            virtual bool hasPendingRequests() const;
            virtual void execute();

        private:
            typedef std::list<boost::shared_ptr<AbstractRequest> > Requests;

            Common::Logger logger;
            Requests pendingRequests;

            void responseReady(const AbstractRequest& request, boost::shared_ptr<AbstractAsset> asset);
            void responseFailed(const AbstractRequest& request);
    };

}

}

#endif /* ASYNCLOADER_HPP_ */
