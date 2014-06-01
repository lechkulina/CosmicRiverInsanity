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

    }

}

}

#endif /* KEYWORDS_HPP_ */
