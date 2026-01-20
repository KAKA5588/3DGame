#pragma once
#include <cmath>

struct Vec3
{
    float x;
    float y;
    float z;

    // ƒRƒ“ƒXƒgƒ‰ƒNƒ^
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // ‰ÁZ
    Vec3 operator+(const Vec3& v) const
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    // Œ¸Z
    Vec3 operator-(const Vec3& v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    // ƒXƒJƒ‰[æZ
    Vec3 operator*(float s) const
    {
        return Vec3(x * s, y * s, z * s);
    }

    // ‰ÁZ‘ã“ü
    Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // ’·‚³
    float Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // ³‹K‰»
    Vec3 Normalized() const
    {
        float len = Length();
        if (len == 0.0f) return Vec3();
        return Vec3(x / len, y / len, z / len);
    }

    // “àÏ
    static float Dot(const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    // ŠOÏ
    static Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
};
