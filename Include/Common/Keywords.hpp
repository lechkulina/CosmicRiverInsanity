/*
 *  Keywords.hpp
 *
 *  Created on: 29 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef KEYWORDS_HPP_
#define KEYWORDS_HPP_

#include <boost/parameter.hpp>

namespace Cosmic {

namespace Core {

    namespace Keywords {

        BOOST_PARAMETER_NAME((name, Tags) name)
        BOOST_PARAMETER_NAME((path, Tags) path)
        BOOST_PARAMETER_NAME((signalsQueue, Tags) signalsQueue)
        BOOST_PARAMETER_NAME((ignoreInvalid, Tags) ignoreInvalid)
        BOOST_PARAMETER_NAME((ignoreDuplicates, Tags) ignoreDuplicates)
        BOOST_PARAMETER_NAME((frequency, Tags) frequency)
        BOOST_PARAMETER_NAME((format, Tags) format)
        BOOST_PARAMETER_NAME((channels, Tags) channels)
        BOOST_PARAMETER_NAME((chunkSize, Tags) chunkSize)
        BOOST_PARAMETER_NAME((rotationSize, Tags) rotationSize)
        BOOST_PARAMETER_NAME((videoContext, Tags) videoContext)
        BOOST_PARAMETER_NAME((windowTitle, Tags) windowTitle)
        BOOST_PARAMETER_NAME((windowGeometry, Tags) windowGeometry)
        BOOST_PARAMETER_NAME((disableScreenSaver, Tags) disableScreenSaver)
        BOOST_PARAMETER_NAME((hideCursor, Tags) hideCursor)

    }

}

}

#endif /* KEYWORDS_HPP_ */
