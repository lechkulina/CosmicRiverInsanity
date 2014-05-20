/*
 *  Rectangle.hpp
 *
 *  Created on: 21 maj 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

namespace Cosmic {

namespace Common {

    template<class T>
    class Rectangle {
        public:
            typedef T Value;

            T x;
            T y;
            T width;
            T height;

            Rectangle();

            template<class A>
            Rectangle(const A& x, const A& y, const A& width, const A& height);
    };

    template<class T>
    Rectangle<T>::Rectangle() :
        x(0),
        y(0),
        width(0),
        height(0) {
    }

    template<class T>
    template<class A>
    Rectangle<T>::Rectangle(const A& x, const A& y, const A& width, const A& height) :
        x(x),
        y(y),
        width(width),
        height(height) {
    }

}

}

#endif /* RECTANGLE_HPP_ */
