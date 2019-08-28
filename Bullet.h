#pragma once
#include "SpaceObject.h"

class Bullet : public SpaceObject {
private:

public:
    Bullet(GameWindow* game, Vec2 pos, Vec2 velocity);

    void updatePos();

    bool checkOutOfBounds();
    
    void draw();
};