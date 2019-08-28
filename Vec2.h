#pragma once
#include <cmath>

struct Vec2 {
    double x, y;
    Vec2()
        : x(0.0), y(0.0) {}
    Vec2(double x, double y)
        : x(x), y(y) {}
    Vec2(int x, int y)
        : x(static_cast<double>(x)), y(static_cast<double>(y)) {}
    Vec2(const Vec2& v)
        : x(v.x), y(v.y) {}
    Vec2& operator=(const Vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    Vec2& operator+=(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vec2 operator+(const Vec2& v) {
        Vec2 vsum = *this;
        return vsum += v;
    }
	Vec2 operator-(const Vec2& v) {
		Vec2 vdif = *this;
		return{ vdif.x - v.x, vdif.y - v.y };
	}
    Vec2& operator%=(const Vec2& v) {
        while (x >= v.x || x < 0) {
            if (x >= v.x)
                x -= v.x;
            else
                x += v.x;
        }
        while (y >= v.y || y < 0) {
            if (y >= v.y)
                y -= v.y;
            else
                y += v.y;
        }
        return *this;
    }
    Vec2 operator%(const Vec2& v) {
        Vec2 vmod = *this;
        return vmod %= v;
    }
    Vec2& operator*=(double d) {
        x *= d;
        y *= d;
        return *this;
    }
    Vec2 operator*(double d) {
        Vec2 vscaled = *this;
        return vscaled *= d;
    }
    double magnitude() {
        return sqrt(x * x + y * y);
    }
    void makeUnitLength() {
        double length = sqrt(x * x + y * y);
        *this *= (1.0 / length);
    }
    static double dist(const Vec2& a, const Vec2& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }
    static Vec2 fromAngleDeg(double degrees) {
        double radians = 3.14 * (degrees / 180.0);
        return Vec2(cos(radians), -sin(radians));
    }
    static Vec2 fromAngleRad(double radians) {
        return Vec2(cos(radians), -sin(radians));
    }

	Vec2 getUnitVec() {
		double length = sqrt(x * x + y * y);
		return *this * (1.0 / length);
	}
};
