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

Cosmic::Core::AsyncLoader::AsyncLoader(Common::SignalsQueue* signalsQueue /*= nullptr*/,
                                        bool ignoreInvalid /*= false*/,
                                        bool ignoreDuplicates /*= true*/) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources),
    signalsQueue(signalsQueue),
    ignoreInvalid(ignoreInvalid),
    ignoreDuplicates(ignoreDuplicates),
    isRunning(false) {
}

Cosmic::Core::AsyncLoader::~AsyncLoader() {
    stop();
}

bool Cosmic::Core::AsyncLoader::pushRequest(AbstractRequestSharedPtr request) {
    BOOST_LOG_FUNCTION();

    if (!request) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Empty request was passed to the loader - ignoring it.";
        return false;
    }

    //we have to ensure that only valid requests are stored in pending requests queue
    const std::string& name = request->getName();
    if (ignoreInvalid && !request->isValid()) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Request for asset " << name << " is not valid - ignoring it.";
        return false;
    }

    //check for duplicates
    boost::lock_guard<boost::mutex> guard(mutex);
    if (ignoreDuplicates) {
        for (AbstractRequestSharedPtr currentRequest : requests) {
            if (currentRequest->getName() == name) {
                BOOST_LOG_SEV(logger, Common::Severity::Debug)
                    << "Request for asset " << name << " found in pending requests queue - ignoring it.";
                return false;
            }
        }
    }

    //push this request to our pending requests queue
    BOOST_LOG_SEV(logger, Common::Severity::Debug)
        << "Pushing request for asset " << name << " to the pending requests queue.";
    request->connectToFinished(boost::bind(&AsyncLoader::finished, this, _1));
    requests.push_back(request);
    condition.notify_all();

    return true;
}

bool Cosmic::Core::AsyncLoader::hasRequests() const {
    boost::lock_guard<boost::mutex> guard(mutex);
    return !requests.empty();
}

void Cosmic::Core::AsyncLoader::start() {
    BOOST_LOG_FUNCTION();

    //check if requests thread has already been started
    boost::lock_guard<boost::mutex> guard(mutex);
    if (isRunning) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Requests thread has already been started - skipping.";
        return;
    }

    BOOST_LOG(logger) << "Starting requests thread.";
    isRunning = true;
    thread = boost::thread(boost::bind(&AsyncLoader::executeRequests, this));
}

void Cosmic::Core::AsyncLoader::stop() {
    BOOST_LOG_FUNCTION();

    //check if requests thread has already been stopped
    boost::unique_lock<boost::mutex> lock(mutex);
    if (!isRunning) {
        BOOST_LOG_SEV(logger, Common::Severity::Debug)
            << "Requests thread has already been stopped - skipping.";
        return;
    }

    //request stopping requests thread - we assuming here that after sending notification
    //it will check the isRunning flag
    BOOST_LOG(logger) << "Stopping requests thread.";
    isRunning = false;
    condition.notify_all();
    lock.unlock();
    thread.join();
}

void Cosmic::Core::AsyncLoader::executeRequests() {
    BOOST_LOG_FUNCTION();

    boost::this_thread::disable_interruption interruption;
    boost::unique_lock<boost::mutex> lock(mutex);

    while(true) {
        //check if we were requested to stopped this thread
        if (!isRunning) {
            BOOST_LOG(logger) << "Stopping requests thread.";
            break;
        }

        //check if there are some pending requests
        if (requests.empty()) {
            BOOST_LOG(logger) << "Pending requests queue is empty - waiting for some new requests.";
            condition.wait(lock);
            continue;
        }

        //fetch and execute the first one - we are working in FIFO order here
        AbstractRequestSharedPtr request = requests.front();
        requests.pop_front();
        BOOST_LOG(logger) << "Executing request for asset " << request->getName() << ".";
        request->execute();
    }
}

void Cosmic::Core::AsyncLoader::finished(AbstractAssetSharedPtr asset) {
    BOOST_LOG_FUNCTION();

    //we are always emitting signals here - it is cache and/or other object responsibility
    //to check if it was successful or not
    BOOST_LOG(logger) << "Request for asset " << asset->getName() << " finished.";
    if (signalsQueue) {
        signalsQueue->push(boost::bind(boost::ref(finishedSignal), asset));
    } else {
        finishedSignal(asset);
    }
}
