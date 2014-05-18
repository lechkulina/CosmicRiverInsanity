/*
 * Common.hpp
 *
 * Created on: 3 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef COSMIC_PHYSICS_COMMON_HPP_
#define COSMIC_PHYSICS_COMMON_HPP_

namespace Cosmic {

namespace Physics {

    const float PI  = 3.141592653589793;

    template<class T>
    inline T degrees(const T& radians) {
        return (radians * 180) / PI;
    }

    template<class T>
    inline T radians(const T& degrees) {
        return (PI * degrees) / 180;
    }

}

}

#endif /* COSMIC_PHYSICS_COMMON_HPP_ */
