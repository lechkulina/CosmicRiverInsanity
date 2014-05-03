/*
 * AbstractShape.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef ABSTRACTSHAPE_HPP_
#define ABSTRACTSHAPE_HPP_

namespace Cosmic {

namespace Physics {

    class AbstractShape {
        public:
            virtual ~AbstractShape() {}

            virtual float getDensity() const =0;
            virtual float getMass() const =0;
            virtual float getInertia() const =0;
    };

}

}

#endif /* ABSTRACTSHAPE_HPP_ */
