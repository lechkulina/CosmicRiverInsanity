/*
 * CircleShape.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef CIRCLESHAPE_HPP_
#define CIRCLESHAPE_HPP_

#include <Physics/AbstractShape.hpp>

namespace Cosmic {

namespace Physics {

    class CircleShape : public AbstractShape {
        public:
            CircleShape();
            CircleShape(float radius, float density);

            virtual float getDensity() const;
            virtual float getMass() const;
            virtual float getInertia() const;

            void setRadious(float radious);
            void setDensity(float density);

        private:
            float radius;
            float density;
            float mass;
            float inertia;

            void update();
    };

}

}

#endif /* CIRCLESHAPE_HPP_ */
