/*
 * Game.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL.h>
#include <boost/shared_ptr.hpp>
#include <Common/Logging.hpp>
#include <Core/AbstractSubsystem.hpp>

#include <Core/ComposedSubsystem.hpp>

#include <Core/LoggingSubsystem.hpp>
#include <Core/VideoSubsystem.hpp>
#include <Core/ImageSubsystem.hpp>
#include <Core/AudioSubsystem.hpp>

#include <Core/VideoContext.hpp>
#include <Core/AsyncLoader.hpp>
#include <Core/TexturesCache.hpp>

//!!! TEST
#include <Core/TextureFileRequest.hpp>
#include <Core/Texture.hpp>
#include <Core/Music.hpp>
#include <Game/Spacecraft.hpp>
//!!! TEST

namespace Cosmic {

namespace Core {

    enum class GameState : int {
        Startup,
        Menu,
        Running,
        Paused,
        Shutdown
    };

    class Game : public AbstractSubsystem {
        public:
            Game();
            virtual ~Game();

            virtual bool isInitialized() const;
            int execute();

        private:
            Common::Logger logger;
            GameState gameState;
            boost::shared_ptr<LoggingSubsystem> loggingSubsystem;
            boost::shared_ptr<VideoSubsystem> videoSubsystem;
            boost::shared_ptr<ImageSubsystem> imageSubsystem;
            boost::shared_ptr<AudioSubsystem> audioSubsystem;

            ComposedSubsystem composedSubsystem;
            boost::shared_ptr<VideoContext> videoContext;
            boost::shared_ptr<AsyncLoader> asyncLoader;
            boost::shared_ptr<TexturesCache> texturesCache;

            //!!! TEST
            boost::shared_ptr<Texture> texture;
            boost::shared_ptr<Music> music;
            boost::shared_ptr<Cosmic::Game::Spacecraft> spacecraft;
            //!!! TEST

            void handleEvent(const SDL_Event& event);
            void updateFrame(float deltaTime);
            void renderFrame();
            void resetFrame();
    };

}

}

#endif /* GAME_HPP_ */
