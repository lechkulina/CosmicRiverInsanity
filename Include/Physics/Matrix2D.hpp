/*
 * Matrix2D.hpp
 *
 * Created on: 3 maj 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef MATRIX2D_HPP_
#define MATRIX2D_HPP_

#include <cmath>
#include <Physics/Vector2D.hpp>

namespace Cosmic {

namespace Physics {

    template<class T>
    class Matrix2D {
        public:
            T m11, m12, m21, m22;

            Matrix2D();

            template<class A>
            Matrix2D(const A& m11, const A& m12,
                     const A& m21, const A& m22);

            template<class A>
            Matrix2D(Matrix2D<A>& matrix);

            template<class A>
            Matrix2D<T>& operator=(const Matrix2D<A>& rhs);

            Matrix2D<T> operator+(const Matrix2D<T>& rhs) const;
            const Matrix2D<T>& operator+=(const Matrix2D<T>& rhs);

            Matrix2D<T> operator-(const Matrix2D<T>& rhs) const;
            const Matrix2D<T>& operator-=(const Matrix2D<T>& rhs);

            Matrix2D<T> operator*(const T& rhs) const;
            const Matrix2D<T>& operator*=(const T& rhs);

            Matrix2D<T> operator/(const T& rhs) const;
            const Matrix2D<T>& operator/=(const T& rhs);

            Matrix2D<T> operator*(const Matrix2D<T>& rhs) const;
            Vector2D<T> operator*(const Vector2D<T>& rhs) const;

            T det() const;
    };

    template<class T>
    Matrix2D<T>::Matrix2D() :
        m11(0), m12(0),
        m21(0), m22(0) {
    }

    template<class T>
    template<class A>
    Matrix2D<T>::Matrix2D(const A& m11, const A& m12,
                          const A& m21, const A& m22) :
        m11(m11), m12(m12),
        m21(m21), m22(m22){
    }

    template<class T>
    template<class A>
    Matrix2D<T>::Matrix2D(Matrix2D<A>& matrix) :
        m11(matrix.m11), m12(matrix.m12),
        m21(matrix.m21), m22(matrix.m22){
    }

    template<class T>
    template<class A>
    Matrix2D<T>& Matrix2D<T>::operator=(const Matrix2D<A>& rhs) {
        m11 = rhs.m11;      m12 = rhs.m12;
        m21 = rhs.m21;      m22 = rhs.m22;
        return *this;
    }

    template<class T>
    Matrix2D<T> Matrix2D<T>::operator+(const Matrix2D<T>& rhs) const {
        return Matrix2D<T>(m11 + rhs.m11, m12 + rhs.m12,
                           m21 + rhs.m21, m22 + rhs.m22);
    }

    template<class T>
    const Matrix2D<T>& Matrix2D<T>::operator+=(const Matrix2D<T>& rhs) {
        m11 += rhs.m11;     m12 += rhs.m12;
        m21 += rhs.m21;     m22 += rhs.m22;
        return *this;
    }

    template<class T>
    Matrix2D<T> Matrix2D<T>::operator-(const Matrix2D<T>& rhs) const {
        return Matrix2D<T>(m11 - rhs.m11, m12 - rhs.m12,
                           m21 - rhs.m21, m22 - rhs.m22);
    }

    template<class T>
    const Matrix2D<T>& Matrix2D<T>::operator-=(const Matrix2D<T>& rhs) {
        m11 -= rhs.m11;     m12 -= rhs.m12;
        m21 -= rhs.m21;     m22 -= rhs.m22;
        return *this;
    }

    template<class T>
    Matrix2D<T> Matrix2D<T>::operator*(const T& rhs) const {
        return Matrix2D<T>(m11 * rhs, m12 * rhs,
                           m21 * rhs, m22 * rhs);
    }

    template<class T>
    const Matrix2D<T>& Matrix2D<T>::operator*=(const T& rhs) {
        m11 *= rhs;     m12 *= rhs;
        m21 *= rhs;     m22 *= rhs;
        return *this;
    }

    template<class T>
    Matrix2D<T> Matrix2D<T>::operator/(const T& rhs) const {
        return Matrix2D<T>(m11 / rhs, m12 / rhs,
                           m21 / rhs, m22 / rhs);
    }

    template<class T>
    const Matrix2D<T>& Matrix2D<T>::operator/=(const T& rhs) {
        m11 /= rhs;     m12 /= rhs;
        m21 /= rhs;     m22 /= rhs;
        return *this;
    }

    template<class T>
    Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& rhs) const {
        return Matrix2D<T>(m11 * rhs.m11 + m12 * rhs.m21, m11 * rhs.m12 + m12 * rhs.m22,
                           m21 * rhs.m11 + m22 * rhs.m21, m21 * rhs.m21 + m22 * rhs.m22);
    }

    template<class T>
    Vector2D<T> Matrix2D<T>::operator*(const Vector2D<T>& rhs) const {
        return Vector2D<T>(m11 * rhs.x + m12 * rhs.y,
                           m21 * rhs.x + m22 * rhs.y);
    }

    template<class T>
    T Matrix2D<T>::det() const {
        return m11 * m22 - m12 * m21;
    }

    template<class T>
    Matrix2D<T> buildIdentityMatrix() {
        return Matrix2D<T>(1, 0,
                           0, 1);
    }

    template<class T>
    Matrix2D<T> buildRotationMatrix(const T& radians) {
        return Matrix2D<T>(cos(radians), -sin(radians),
                           sin(radians), cos(radians));
    }

}

}

#endif /* MATRIX2D_HPP_ */
