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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <boost/thread.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Common/SignalsQueue.hpp>
#include <Core/AbstractLoader.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class AsyncLoader;
    typedef boost::shared_ptr<AsyncLoader> AsyncLoaderSharedPtr;
    typedef boost::weak_ptr<AsyncLoader> AsyncLoaderWeakPtr;

    class AsyncLoader : public AbstractLoader {
        public:
            AsyncLoader(Common::SignalsQueue* signalsQueue = nullptr);
            virtual ~AsyncLoader();

            virtual bool pushRequest(AbstractRequestSharedPtr request);
            virtual bool hasRequests() const;

            virtual void start();
            virtual void stop();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (AsyncLoaderSharedPtr), static make, Keywords::Tags,
                (optional
                    (signalsQueue, (Common::SignalsQueue*), nullptr)
                )
            ) {
                return boost::make_shared<AsyncLoader>(signalsQueue);
            }

        private:
            typedef std::list<AbstractRequestSharedPtr> Requests;

            Common::Logger logger;
            Common::SignalsQueue* const signalsQueue;
            bool isRunning;
            Requests requests;
            boost::thread thread;
            mutable boost::mutex mutex;
            boost::condition_variable condition;

            void executeRequests();
            void finished(AbstractAssetSharedPtr asset);
    };

}

}

#endif /* ASYNCLOADER_HPP_ */
