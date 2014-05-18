/*
 * AbstractAsset.hpp
 *
 * Created on: 17 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTASSET_HPP_
#define ABSTRACTASSET_HPP_

#include <Common/Common.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>

namespace Cosmic {

namespace Core {

    class AbstractAsset {
            typedef boost::signals2::signal<void (const AbstractAsset&)> OnLoadSignal;
            typedef boost::signals2::signal<void (const AbstractAsset&)> OnUnloadSignal;

        public:
            Common::SignalAdapter<OnLoadSignal> onLoad;
            Common::SignalAdapter<OnUnloadSignal> onUnload;

            AbstractAsset();
            virtual ~AbstractAsset();

            virtual bool isLoaded() const =0;
            virtual const boost::filesystem::path& getPath() const =0;

        protected:
            OnLoadSignal onLoadSignal;
            OnUnloadSignal onUnloadSignal;
    };

}

}

#endif /* ABSTRACTASSET_HPP_ */
