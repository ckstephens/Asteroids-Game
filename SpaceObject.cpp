#include "SpaceObject.h"
#include "GameWindow.h"

using namespace std;

SpaceObject::SpaceObject(GameWindow* game, Vec2 pos, Vec2 velocity, double radius)
	: Fl_Widget(1, 1, 0, 0), game(game), pos(pos),
	velocity(velocity), collision_radius(radius) {}

void SpaceObject::updatePos() {  //update position
	(pos %= Vec2(game->w(),game->h())) += velocity;
}

Vec2 SpaceObject::getPos() const {
	return this->pos;
}

bool SpaceObject::checkCollision(SpaceObject* obj) {  //check for collision
	return Vec2::dist(this->pos, obj->pos)
		- (this->collision_radius + obj->collision_radius) < 0.05;
}