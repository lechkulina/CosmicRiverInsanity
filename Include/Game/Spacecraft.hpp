/*
 * Spacecraft.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef SPACECRAFT_HPP_
#define SPACECRAFT_HPP_

#include <boost/shared_ptr.hpp>
#include <Common/Logging.hpp>
#include <Core/VideoContext.hpp>
#include <Core/TextureAsset.hpp>
#include <Physics/RigidBody.hpp>
#include <Physics/CircleShape.hpp>

namespace Cosmic {

namespace Game {

    class Spacecraft {
        public:
            Spacecraft(boost::shared_ptr<Core::TextureAsset> textureAsset);

            void setLeftEngineThrust(float thrust);
            void setRightEngineThrust(float thrust);

            void update(int deltaTime);
            void render(boost::shared_ptr<Core::VideoContext> videoContext);
            void reset();

        private:
            Common::Logger logger;
            boost::shared_ptr<Core::TextureAsset> textureAsset;
            Physics::CircleShape shape;
            Physics::RigidBody body;
    };

}

}

#endif /* SPACECRAFT_HPP_ */
