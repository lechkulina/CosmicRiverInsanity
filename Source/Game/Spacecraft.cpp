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

Cosmic::Game::Spacecraft::Spacecraft(Core::AbstractCacheSharedPtr assetsCache) :
    logger(
        boost::log::keywords::severity = Common::Severity::Trace,
        boost::log::keywords::channel = Common::Channel::Game),
    shape(20.0f, 3.0f),
    body(shape),
    leftEngineThrust(0.0f),
    rightEngineThrust(0.0f) {
    BOOST_LOG_FUNCTION();
    Core::AbstractAssetSharedPtr a = assetsCache->get("spacecraft-green");
    //fetch assets for this spacecraft
    texture = assetsCache->fetch<Core::Texture>("spacecraft-green");
    if (!texture) {
        BOOST_LOG_SEV(logger, Common::Severity::Error)
            << "Failed to find texture for spacecraft.";
        return;
    }
}

void Cosmic::Game::Spacecraft::setLeftEngineThrust(float thrust) {
    leftEngineThrust = thrust;
}

void Cosmic::Game::Spacecraft::setRightEngineThrust(float thrust) {
    rightEngineThrust = thrust;
}

void Cosmic::Game::Spacecraft::update(int deltaTime) {
    body.applyForce(Physics::Vector2D<float>(0.0f, leftEngineThrust), Physics::Vector2D<float>(-20, -20), true);
    body.applyForce(Physics::Vector2D<float>(0.0f, rightEngineThrust), Physics::Vector2D<float>(20, -20), true);
    body.update(deltaTime);
}

void Cosmic::Game::Spacecraft::render(Core::VideoContextSharedPtr videoContext) {
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
    Physics::Vector2D<float> finalForce = rotation * Physics::Vector2D<float>(0.0f, leftEngineThrust);

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
    Physics::Vector2D<float> finalForce = rotation * Physics::Vector2D<float>(0.0f, rightEngineThrust);

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
