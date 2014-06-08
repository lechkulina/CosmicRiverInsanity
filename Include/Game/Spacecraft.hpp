/*
 * Spacecraft.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef SPACECRAFT_HPP_
#define SPACECRAFT_HPP_

#include <Common/Logging.hpp>
#include <Core/AbstractCache.hpp>
#include <Core/VideoContext.hpp>
#include <Core/Texture.hpp>
#include <Physics/RigidBody.hpp>
#include <Physics/CircleShape.hpp>

namespace Cosmic {

namespace Game {

    class Spacecraft {
        public:
            Spacecraft(Core::AbstractCacheSharedPtr assetsCache);

            void setLeftEngineThrust(float thrust);
            void setRightEngineThrust(float thrust);

            void update(int deltaTime);
            void render(Core::VideoContextSharedPtr videoContext);
            void reset();

        private:
            Common::Logger logger;
            Core::TextureSharedPtr texture;
            Physics::CircleShape shape;
            Physics::RigidBody body;
            float leftEngineThrust;
            float rightEngineThrust;
    };

}

}

#endif /* SPACECRAFT_HPP_ */
