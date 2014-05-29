/*
 *  AsyncLoader.cpp
 *
 *  Created on: 19 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <Core/AsyncLoader.hpp>

Cosmic::Core::AsyncLoader::AsyncLoader(Common::SignalsQueue& signalsQueue) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    signalsQueue(signalsQueue),
    isRunning(false) {
}

Cosmic::Core::AsyncLoader::~AsyncLoader() {
    stop();
}

bool Cosmic::Core::AsyncLoader::pushRequest(AbstractRequestSharedPtr request) {
    BOOST_LOG_FUNCTION();

    boost::lock_guard<boost::mutex> guard(mutex);

    //check for duplicates
    for (AbstractRequestSharedPtr currentRequest : requests) {
        if (currentRequest->getName() == request->getName()) {
            BOOST_LOG_SEV(logger, Common::Severity::Debug)
                << "Request for asset " << request->getName() << " from " << request->getPath()
                << " found in pending requests queue, ignoring it.";
            return false;
        }
    }

    //push this request to our pending requests queue
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Pushing request for asset " << request->getName() << " to the pending requests queue.";
    request->connectToFinished(boost::bind(&AsyncLoader::finished, this, _1));
    requests.push_back(request);
    condition.notify_all();

    return true;
}

bool Cosmic::Core::AsyncLoader::hasRequests() const {
    boost::lock_guard<boost::mutex> guard(mutex);
    return not requests.empty();
}

void Cosmic::Core::AsyncLoader::start() {
    BOOST_LOG_FUNCTION();

    boost::lock_guard<boost::mutex> guard(mutex);

    BOOST_LOG(logger) << "Starting requests thread.";
    isRunning = true;
    thread = boost::thread(boost::bind(&AsyncLoader::executeRequests, this));
}

void Cosmic::Core::AsyncLoader::stop() {
    BOOST_LOG_FUNCTION();

    boost::lock_guard<boost::mutex> guard(mutex);

    if (!isRunning) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Requests thread has already been stopped - skipping.";
        return;
    }

    BOOST_LOG(logger) << "Stopping requests thread.";
    isRunning = false;
}

void Cosmic::Core::AsyncLoader::executeRequests() {
    BOOST_LOG_FUNCTION();

    boost::this_thread::disable_interruption interruption;
    boost::unique_lock<boost::mutex> lock(mutex);

    while(isRunning) {
        //check if there are some pending requests
        if (requests.empty()) {
            BOOST_LOG(logger) << "Pending requests queue is empty - waiting for some new requests.";
            condition.wait(lock);
            continue;
        }

        //fetch the first one - we are working in FIFO order here
        AbstractRequestSharedPtr request = requests.front();
        requests.pop_front();

        //execute it
        BOOST_LOG(logger)
            << "Going to execute request for asset " << request->getName() << " from " << request->getPath();
        request->execute();
    }
}

void Cosmic::Core::AsyncLoader::finished(AbstractAssetSharedPtr asset) {
    BOOST_LOG_FUNCTION();

    if (asset->isLoaded()) {
        BOOST_LOG(logger) << "Asset " << asset->getName() << " from " << asset->getPath() << " is ready.";
    } else {
        BOOST_LOG(logger) << "Failed to load asset " << asset->getName() << " from " << asset->getPath() << ".";
    }
    signalsQueue.push(boost::bind(boost::ref(finishedSignal), asset));
}
