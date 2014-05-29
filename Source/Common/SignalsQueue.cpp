/*
 *  SignalsQueue.cpp
 *
 *  Created on: 26 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#include <Common/SignalsQueue.hpp>

void Cosmic::Common::SignalsQueue::push(const Callback& callback) {
    boost::lock_guard<boost::mutex> guard(mutex);
    callbacks.push_back(callback);
}

bool Cosmic::Common::SignalsQueue::poll() {
    boost::lock_guard<boost::mutex> guard(mutex);
    if (callbacks.empty()) {
        return false;
    }
    while(not callbacks.empty()) {
        Callback& callback = callbacks.front();
        if (not callback.empty()) {
            callback();
        }
        callbacks.pop_front();
    }
    return true;
}
