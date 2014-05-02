/*
 * VideoContext.hpp
 *
 * Created on: 1 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef VIDEOCONTEXT_HPP_
#define VIDEOCONTEXT_HPP_

#include <SDL.h>
#include <Common/Logging.hpp>
#include <Common/Color.hpp>
#include <Core/AbstractContext.hpp>

namespace Cosmic {

namespace Core {

    class VideoContext : public AbstractContext {
        public:
            VideoContext();
            virtual ~VideoContext();

            virtual bool isReady() const;

            virtual void setDrawColor(const Common::Color& color = Common::Color::Black);
            virtual void clear();
            virtual void present();

            operator SDL_Renderer*();

        private:
            Common::Logger logger;
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_RendererInfo rendererInfo;
    };

}

}

#endif /* VIDEOCONTEXT_HPP_ */
