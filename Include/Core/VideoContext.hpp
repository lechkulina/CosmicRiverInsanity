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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/parameter.hpp>
#include <Common/Logging.hpp>
#include <Common/Keywords.hpp>
#include <Common/Rectangle.hpp>
#include <Common/Color.hpp>
#include <Core/AbstractContext.hpp>

namespace Cosmic {

namespace Core {

    class VideoContext;
    typedef boost::shared_ptr<VideoContext> VideoContextSharedPtr;
    typedef boost::weak_ptr<VideoContext> VideoContextWeakPtr;

    class VideoContext : public AbstractContext {
        public:
            VideoContext(const std::string& windowTitle, const Common::Rectangle<Sint32>& windowGeometry);
            virtual ~VideoContext();

            virtual bool isReady() const;

            virtual void setDrawColor(const Common::Color& color = Common::Color::Black);
            virtual void clear();
            virtual void present();

            operator SDL_Renderer*();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (VideoContextSharedPtr), static make, Keywords::Tags,
                (optional
                    (windowTitle, (const std::string&), "")
                    (windowGeometry, (const Common::Rectangle<Sint32>&), Common::Rectangle<Sint32>(
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600
                    ))
                )
            ) {
                return boost::make_shared<VideoContext>(windowTitle, windowGeometry);
            }

        private:
            Common::Logger logger;
            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_RendererInfo rendererInfo;
    };

}

}

#endif /* VIDEOCONTEXT_HPP_ */
