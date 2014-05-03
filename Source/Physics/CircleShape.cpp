/*
 * CircleShape.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <cmath>
#include <Physics/Common.hpp>
#include <Physics/CircleShape.hpp>

Cosmic::Physics::CircleShape::CircleShape() :
    radius(0.0f),
    density(0.0f),
    mass(0.0f),
    inertia(0.0f) {
}

Cosmic::Physics::CircleShape::CircleShape(float radius, float density) :
    radius(radius),
    density(density),
    mass(0.0f),
    inertia(0.0f) {
    update();
}

float Cosmic::Physics::CircleShape::getDensity() const {
    return density;
}

float Cosmic::Physics::CircleShape::getMass() const {
    return mass;
}

float Cosmic::Physics::CircleShape::getInertia() const {
    return inertia;
}

void Cosmic::Physics::CircleShape::setRadious(float radious) {
    this->radius = radius;
    update();
}

void Cosmic::Physics::CircleShape::setDensity(float density) {
    this->density = density;
    update();
}

void Cosmic::Physics::CircleShape::update() {
    const float squaredRadious = radius * radius;
    mass = squaredRadious * PI * density;
    inertia = (mass * squaredRadious) / 2;
}
