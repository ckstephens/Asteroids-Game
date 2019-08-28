#include "Asteroid.h"

using namespace std;

Asteroid::Asteroid(GameWindow* game, Vec2 pos, Vec2 velocity) 
	: SpaceObject(game, pos, velocity, 30.0) {
	draw();
}

void Asteroid::draw() {
	fl_color(255);
	
	fl_push_matrix();
	fl_translate(pos.x - 39.0,pos.y - 30.0);
	fl_begin_line();
	fl_vertex(10, 10);
	fl_vertex(40, 20);
	fl_vertex(65, 15);
	fl_vertex(60, 40);
	fl_vertex(65, 60);
	fl_vertex(40, 55);
	fl_vertex(10, 60);
	fl_vertex(15, 35);
	fl_vertex(10, 10);
	fl_end_line();
	fl_pop_matrix();
}