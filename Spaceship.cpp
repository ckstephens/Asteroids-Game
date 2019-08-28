#include "Spaceship.h"
#include "GameWindow.h"

using namespace std;

const int Spaceship::shoot_interval = 10;
const double Spaceship::max_speed = 12.0;
const double Spaceship::accel_rate = 0.5;
const double Spaceship::deccel_rate = 0.6;
const double Spaceship::rotation_rate = 5;
const double Spaceship::bullet_speed = 15.0;

Spaceship::Spaceship(GameWindow* game, Vec2 pos, Vec2 velocity)
	: SpaceObject(game, pos, velocity, 15.0), orientation(90.0), accelerating(false),
	rotating_left(false), rotating_right(false), shooting(false) {
	draw();
}

void Spaceship::draw() {
	fl_color(255);

	fl_push_matrix();
	fl_translate(pos.x, pos.y);
	fl_rotate(orientation - 90.0);

	fl_begin_line();  //draw ship
	fl_vertex(-(25.0 / 2.0), 5.0);
	fl_vertex(0.0, -20.0);
	fl_vertex((25.0 / 2.0), 5.0);
	fl_vertex(10.0, 0.0);
	fl_vertex(-10.0, 0.0);
	if (accelerating == true) {  //draw tail if accel.
		fl_vertex(0.0, 7.5);
		fl_vertex(10.0, 0.0);
	}
	fl_end_line();
	fl_pop_matrix();
}

void Spaceship::accelerate() {
	if (accelerating == true && max_speed - velocity.magnitude() > 0.05)  //accel. until max speed
		velocity += Vec2::fromAngleDeg(orientation) * accel_rate;

	else if (accelerating == true)//lets you change direction if at max speed
		velocity += (Vec2::fromAngleDeg(orientation) - velocity.getUnitVec()) * accel_rate;
}

void Spaceship::rotateLeft() {
	if ((orientation += rotation_rate) > 360.0)  //wrap
		orientation -= 360.0;
}

void Spaceship::rotateRight() {
	if ((orientation -= rotation_rate) < 0.0)  //wrap
		orientation += 360.0;
}

void Spaceship::shoot() {  //shoot one bullet
	game->addBullet(pos, Vec2::fromAngleDeg(orientation) * bullet_speed);
}

int update_ticks = 0;  //for shooting rate
void Spaceship::updatePos() {
	update_ticks++;

	if (rotating_left == true)
		rotateLeft();
	if (rotating_right == true)
		rotateRight();

	accelerate();

	//slow down if not accelerating
	if (accelerating == false && velocity.magnitude() > 0.05)
		velocity += velocity.getUnitVec() * -1 * deccel_rate;

	//shoot if enough time passed
	if (shooting == true && update_ticks > shoot_interval) {
		shoot();
		update_ticks = 0;
	}

	(pos %= Vec2(game->w(), game->h())) += velocity;  //update pos
}

void Spaceship::setAccelerating(bool status) {
	accelerating = status;
}

void Spaceship::setRotatingLeft(bool status) {
	rotating_left = status;
}

void Spaceship::setRotatingRight(bool status) {
	rotating_right = status;
}

void Spaceship::setShooting(bool status) {
	shooting = status;
}