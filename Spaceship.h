#pragma once
#include <vector>
#include "SpaceObject.h"

class Spaceship : public SpaceObject {
private:
    double orientation;
    bool accelerating, rotating_left, rotating_right, shooting;

	static const int shoot_interval;
    static const double max_speed;
    static const double accel_rate;
    static const double deccel_rate;
    static const double rotation_rate;
    static const double bullet_speed;

public:
    Spaceship(GameWindow* game, Vec2 pos, Vec2 velocity);
    
    void updatePos();

    void setAccelerating(bool status);

    void setRotatingLeft(bool status);

    void setRotatingRight(bool status);

    void setShooting(bool status);
    
    void accelerate();
    
    void rotateLeft();
    
    void rotateRight();
    
    void shoot();

    void draw();
};