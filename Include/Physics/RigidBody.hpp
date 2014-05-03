/*
 * RigidBody.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include <Physics/Vector2D.hpp>
#include <Physics/AbstractShape.hpp>

namespace Cosmic {

namespace Physics {

    class RigidBody {
        public:
            explicit RigidBody(const AbstractShape& shape);

            void applyForce(const Vector2D<float>& force, const Vector2D<float>& applicationPoint,
                            bool isRelativeToBody = false);
            void update(int deltaTime);
            void reset();

            const Vector2D<float>& getPosition() const;
            float getOrientation() const;

        private:
            const AbstractShape& shape;
            Vector2D<float> position;
            Vector2D<float> linearVelocity;
            Vector2D<float> force;
            float orientation;
            float angularVelocity;
            float torque;
    };

}

}

#endif /* RIGIDBODY_HPP_ */
