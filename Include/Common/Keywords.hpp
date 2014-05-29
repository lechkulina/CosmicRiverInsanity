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

    }

}

}

#endif /* KEYWORDS_HPP_ */
