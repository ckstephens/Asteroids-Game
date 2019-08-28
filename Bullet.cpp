#include "Bullet.h"
#include "GameWindow.h"

using namespace std;

Bullet::Bullet(GameWindow* game, Vec2 pos, Vec2 velocity) : SpaceObject(game, pos, velocity, 0.0) {
	draw();
}

void Bullet::draw() {
	fl_color(255);
	fl_rectf(pos.x, pos.y, 4, 4);
}

void Bullet::updatePos() {
	pos += velocity;
}

bool Bullet::checkOutOfBounds() {
	return (pos.x > game->w() - 3.0 || pos.x < 3.0
		|| pos.y > game->h() - 3.0 || pos.y < 3.0);
}
