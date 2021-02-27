#pragma once

#include <math.h>
#include <stdint.h>

#pragma region Vector2D

template <class T>
class Vector2 {
public:
    T x;
    T y;

    Vector2();
    Vector2(T valX, T valY);
    Vector2(const Vector2& vec);
    Vector2(T val);
    ~Vector2() {}

    Vector2 operator+(const Vector2& right) const;
    Vector2& operator+=(const Vector2& right);
    Vector2 operator-(const Vector2& right) const;
    Vector2& operator-=(const Vector2& right);
    Vector2 operator*(T value) const;
    Vector2& operator*=(T value);

    Vector2& operator*(const Vector2& right) const;

    bool operator==(const Vector2& right) const;
    bool operator!=(const Vector2& right) const;

    // TODO:
    // Square
    // Magnitude
    // Distance
    // Min and Max
    // Dot Proudct
    // Normalise


    operator Vector2<float>() const;
    operator Vector2<double>() const;
};

template <class T>
Vector2<T>::Vector2()
{
    x = (T)0;
    y = (T)0;
}
template <class T>
Vector2<T>::Vector2(T x, T y)
{
    this->x = x;
    this->y = y;
}
template <class T>
Vector2<T>::Vector2(const Vector2& other)
{
    x = (T)other.x;
    y = (T)other.y;
}
template <class T>
Vector2<T>::Vector2(T value)
{
    x = value;
    y = value;
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2& right) const
{
    return { x + right.x, y + right.y };
}
template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2& right) const
{
    return { x - right.x, y - right.y };
}
template <class T>
Vector2<T> Vector2<T>::operator*(T value) const
{
    return { x * value, y * value };
}
template <class T>
Vector2<T>& Vector2<T>::operator*(const Vector2& right) const
{
    x* right.x + y * right.y;
    return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& right)
{
    return *this = *this + right;
}
template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& right)
{
    return *this = *this - right;
}
template <class T>
Vector2<T>& Vector2<T>::operator*=(T value) {
    return *this = *this * value;
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T>& right) const
{
    return x == right.x && y == right.y;
}
template <class T>
bool Vector2<T>::operator!=(const Vector2<T>& right) const
{
    return !(*this == right);
}

template<class T>
inline Vector2<T>::operator Vector2<double>() const
{
    return { static_cast<double>(this->x), static_cast<double>(this->y) };
}

template<class T>
inline Vector2<T>::operator Vector2<float>() const
{
    return { static_cast<float>(this->x), static_cast<float>(this->y) };
}

typedef Vector2<float> vec2f;
typedef Vector2<double> vec2d;

#pragma endregion