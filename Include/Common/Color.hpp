/*
 * Color.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SDL.h>

namespace Cosmic {

namespace Common {

    class Color {
        public:
            static const Color Black;
            static const Color White;

            Color();
            Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = SDL_ALPHA_OPAQUE);

            Uint8 red;
            Uint8 green;
            Uint8 blue;
            Uint8 alpha;
    };

}

}

#endif /* COLOR_HPP_ */
