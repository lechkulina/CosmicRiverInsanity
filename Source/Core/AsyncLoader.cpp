/*
 *  AsyncLoader.cpp
 *
 *  Created on: 19 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <boost/bind.hpp>
#include <Core/AsyncLoader.hpp>

Cosmic::Core::AsyncLoader::AsyncLoader() :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Resources) {

}

Cosmic::Core::AsyncLoader::~AsyncLoader() {

}

bool Cosmic::Core::AsyncLoader::pushRequest(boost::shared_ptr<AbstractRequest> request) {
    using namespace boost;
    BOOST_LOG_FUNCTION();

    request->onResponseReady.connect(bind(&AsyncLoader::responseReady, this, _1, _2));
    request->onResponseFailed.connect(bind(&AsyncLoader::responseFailed, this, _1));
    pendingRequests.push_back(request);

    return true;
}

bool Cosmic::Core::AsyncLoader::hasPendingRequests() const {
    return !pendingRequests.empty();
}

void Cosmic::Core::AsyncLoader::execute() {
    BOOST_LOG_FUNCTION();

    BOOST_LOG(logger) << "There are " << pendingRequests.size() << " pending requests.";
    while(!pendingRequests.empty()) {
        boost::shared_ptr<AbstractRequest> nextRequest = pendingRequests.front();
        pendingRequests.pop_front();
        nextRequest->execute();
    }
}

void Cosmic::Core::AsyncLoader::responseReady(const AbstractRequest& request, boost::shared_ptr<AbstractAsset> asset) {
    BOOST_LOG_FUNCTION();
    BOOST_LOG(logger) << __FUNCTION__;
}

void Cosmic::Core::AsyncLoader::responseFailed(const AbstractRequest& request) {
    BOOST_LOG_FUNCTION();
    BOOST_LOG(logger) << __FUNCTION__;
}
