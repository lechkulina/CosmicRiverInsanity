/*
 * RigidBody.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Physics/Common.hpp>
#include <Physics/RigidBody.hpp>
#include <Physics/Matrix2D.hpp>

Cosmic::Physics::RigidBody::RigidBody(const AbstractShape& shape) :
    shape(shape),
    position(0.0f, 0.0f),
    linearVelocity(0.0f, 0.0f),
    force(0.0f, 0.0f),
    orientation(0.0f),
    angularVelocity(0.0f),
    torque(0.0f) {
}

void Cosmic::Physics::RigidBody::applyForce(const Vector2D<float>& force, const Vector2D<float>& applicationPoint,
                                            bool isRelativeToBody /*= false*/) {
    //check if we have to rotate force vector and application point to match body angular position
    Vector2D<float> finalForce = force;
    Vector2D<float> finalApplicationPoint = applicationPoint;
    if (isRelativeToBody) {
        const Matrix2D<float> rotation = buildRotationMatrix(-orientation);
        finalApplicationPoint = rotation * applicationPoint;
        finalForce = rotation * force;
    }

    //add this force to the total force that is affecting our rigid body
    this->force += finalForce;

    //add torque generated by this force
    torque += finalApplicationPoint.cross(finalForce);
}

void Cosmic::Physics::RigidBody::update(int deltaTime) {
    //update linear and angular velocities
    linearVelocity += (force / shape.getMass()) * deltaTime;
    angularVelocity += (torque / shape.getInertia()) * deltaTime;

    //update position and orientation
    position += linearVelocity * deltaTime;
    orientation += angularVelocity * deltaTime;
}

void Cosmic::Physics::RigidBody::reset() {
    force.zero();
    torque = 0.0f;
}

const Cosmic::Physics::Vector2D<float>& Cosmic::Physics::RigidBody::getPosition() const {
    return position;
}

float Cosmic::Physics::RigidBody::getOrientation() const {
    return orientation;
}
