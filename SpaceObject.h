#pragma once
#define WIN32
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/x.H>
#include "Vec2.h"
#include <iostream>

class GameWindow;

class SpaceObject : public Fl_Widget {
protected:
    Vec2 pos;
    Vec2 velocity;
    double collision_radius;
    GameWindow* game;

public:
    SpaceObject(GameWindow* game, Vec2 pos, Vec2 velocity, double radius);

    Vec2 getPos() const;
    
    virtual void updatePos();
    
    bool checkCollision(SpaceObject* obj);

    virtual void draw() = 0;
};