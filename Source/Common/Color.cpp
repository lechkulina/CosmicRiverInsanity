/*
 * Color.cpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Common/Color.hpp>

const Cosmic::Common::Color Cosmic::Common::Color::Black(0, 0, 0);
const Cosmic::Common::Color Cosmic::Common::Color::White(255, 255, 255);

Cosmic::Common::Color::Color() :
    red(0),
    green(0),
    blue(0),
    alpha(0) {
}

Cosmic::Common::Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha /*= 255*/) :
    red(red),
    green(green),
    blue(blue),
    alpha(alpha) {
}
