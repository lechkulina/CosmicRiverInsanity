/*
 * Spacecraft.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Game/Spacecraft.hpp>
#include <Physics/Common.hpp>
#include <Physics/Vector2D.hpp>
#include <Physics/Matrix2D.hpp>

Cosmic::Game::Spacecraft::Spacecraft(boost::shared_ptr<Core::Texture> texture) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Game),
    texture(texture),
    shape(20.0f, 3.0f),
    body(shape) {

}
float leftthrust = 0.0f;
float rightthrust = 0.0f;

void Cosmic::Game::Spacecraft::setLeftEngineThrust(float thrust) {
    leftthrust = thrust;
}

void Cosmic::Game::Spacecraft::setRightEngineThrust(float thrust) {
    rightthrust = thrust;
}

void Cosmic::Game::Spacecraft::update(int deltaTime) {
    body.applyForce(Physics::Vector2D<float>(0.0f, leftthrust), Physics::Vector2D<float>(-20, -20), true);
    body.applyForce(Physics::Vector2D<float>(0.0f, rightthrust), Physics::Vector2D<float>(20, -20), true);
    body.update(deltaTime);
}

void Cosmic::Game::Spacecraft::render(boost::shared_ptr<Core::VideoContext> videoContext) {
    const int x = body.getPosition().x - texture->getWidth() / 2 + 400;
    const int y = body.getPosition().y*-1 - texture->getHeight() / 2 + 300;
    const float orientation = Physics::degrees(body.getOrientation());
    texture->copyRotated(videoContext, x, y, orientation);



    //TODO REMOVE THIS - JUST FOR DEBUGGING !!!!!!!!!

    videoContext->setDrawColor(Common::Color(255, 0, 0));
    const Physics::Vector2D<float> position = body.getPosition();
    const Physics::Matrix2D<float> rotation = Physics::buildRotationMatrix(-body.getOrientation());
{
    Physics::Vector2D<float> finalPoint = position + (rotation * Physics::Vector2D<float>(-20, -20));
    Physics::Vector2D<float> finalForce = rotation * Physics::Vector2D<float>(0.0f, leftthrust);

    int x1 = finalPoint.x + 400;
    int y1 = finalPoint.y * -1 + 300;
    int x2 = x1 + finalForce.x * 1000;
    int y2 = y1 + finalForce.y * -1 * 1000;
    SDL_RenderDrawLine(*videoContext, x1, y1, x2, y2);
    SDL_RenderDrawLine(*videoContext, x1, y1, x2, y2);

    SDL_Rect rect = {x2-1, y2-1, 2, 2};
    SDL_RenderFillRect(*videoContext, &rect);
}

{
    Physics::Vector2D<float> finalPoint = position + (rotation * Physics::Vector2D<float>(20, -20));
    Physics::Vector2D<float> finalForce = rotation * Physics::Vector2D<float>(0.0f, rightthrust);

    int x1 = finalPoint.x + 400;
    int y1 = finalPoint.y * -1 + 300;
    int x2 = x1 + finalForce.x * 1000;
    int y2 = y1 + finalForce.y * -1 * 1000;
    SDL_RenderDrawLine(*videoContext, x1, y1, x2, y2);

    SDL_Rect rect = {x2-1, y2-1, 2, 2};
    SDL_RenderFillRect(*videoContext, &rect);
}

}

void Cosmic::Game::Spacecraft::reset() {
    body.reset();
}
