/*
 * Vector2D.hpp
 *
 * Created on: 2 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include <cmath>

namespace Cosmic {

namespace Physics {

    template<class T>
    class Vector2D {
        public:
            T x, y;

            Vector2D();

            template<class A>
            Vector2D(const A& x, const A& y);

            template<class A>
            Vector2D(Vector2D<A>& s);

            Vector2D<T> operator+(const Vector2D<T>& rhs) const;
            const Vector2D<T>& operator+=(const Vector2D<T>& rhs);
            Vector2D<T> operator-(const Vector2D<T>& rhs) const;
            const Vector2D<T>& operator-=(const Vector2D<T>& rhs);
            Vector2D<T> operator*(const T& rhs) const;
            const Vector2D<T>& operator*=(const T& rhs);
            Vector2D<T> operator/(const T& rhs) const;
            const Vector2D<T>& operator/=(const T& rhs);

            T squaredLength() const;
            T length() const;
            T dot(const Vector2D<T>& rhs) const;
            T cross(const Vector2D<T>& rhs) const;

            Vector2D<T>& zero();
            Vector2D<T>& normalize();
    };

    template<class T>
    Vector2D<T>::Vector2D(): x(0), y(0) {}

    template<class T>
    template<class A>
    Vector2D<T>::Vector2D(const A& x, const A& y) : x(x), y(y) {}

    template<class T>
    template<class A>
    Vector2D<T>::Vector2D(Vector2D<A>& s): x(s.x), y(s.y) {}

    template<class T>
    Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& rhs) const {
        return Vector2D<T>(x + rhs.x, y + rhs.y);
    }

    template<class T>
    const Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<class T>
    Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& rhs) const {
        return Vector2D<T>(x - rhs.x, y - rhs.y);
    }

    template<class T>
    const Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<class T>
    Vector2D<T> Vector2D<T>::operator*(const T& rhs) const {
        return Vector2D<T>(x * rhs, y * rhs);
    }

    template<class T>
    const Vector2D<T>& Vector2D<T>::operator*=(const T& rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    template<class T>
    Vector2D<T> Vector2D<T>::operator/(const T& rhs) const {
        return Vector2D<T>(x / rhs, y / rhs);
    }

    template<class T>
    const Vector2D<T>& Vector2D<T>::operator/=(const T& rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    template<class T>
    T Vector2D<T>::squaredLength() const {
        return x * x + y * y;
    }

    template<class T>
    T Vector2D<T>::length() const {
        return sqrt(x * x + y * y);
    }

    template<class T>
    T Vector2D<T>::dot(const Vector2D<T>& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    template<class T>
    T Vector2D<T>::cross(const Vector2D<T>& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    template<class T>
    Vector2D<T>& Vector2D<T>::zero() {
        x = y = 0;
        return *this;
    }

    template<class T>
    Vector2D<T>& Vector2D<T>::normalize() {
        T length = this->length();
        if (length > 0) {
            x /= length;
            y /= length;
        }
        return *this;
    }
}

}

#endif /* VECTOR2D_HPP_ */
