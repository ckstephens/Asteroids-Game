#pragma once
#include <vector>
#include "SpaceObject.h"

class Asteroid : public SpaceObject {
private:

public:
    Asteroid(GameWindow* game, Vec2 pos, Vec2 velocity);

    void draw();
};