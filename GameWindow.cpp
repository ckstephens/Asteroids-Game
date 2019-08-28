#include "GameWindow.h"

using namespace std;

const int GameWindow::max_asteroids = 3;
const int GameWindow::spawn_interval = 45;
const double GameWindow::asteroid_speed = 7.0;

GameWindow::GameWindow(int w, int h) : Fl_Window(w, h),
cycles_survived(1), asteroids_hit(0),
ship(new Spaceship(this, Vec2(this->w()/2, this->h()/2), Vec2(0, 0))) {
	color(32);
	end();
	show();
	Fl::add_timeout(0.033, timer_cb, this);
}

void GameWindow::timer_cb(void* ptr) {  //timer callback
	GameWindow* g = static_cast<GameWindow*>(ptr);
	g->refreshGame();
	Fl::repeat_timeout(0.033, timer_cb, ptr);
}

int GameWindow::handle(int event) {
	switch(event) {

	case FL_KEYDOWN:

		switch (Fl::event_key()) {
		case FL_Up:
			ship->setAccelerating(true);
			return 1;
		case FL_Right:
			ship->setRotatingRight(true);
			return 1;
		case FL_Left:
			ship->setRotatingLeft(true);
			return 1;
		case 32:
			ship->setShooting(true);
			return 1;
		}
		return 1;

	case FL_KEYUP:

		switch (Fl::event_key()) {
		case FL_Up:
			ship->setAccelerating(false);
			return 1;
		case FL_Right:
			ship->setRotatingRight(false);
			return 1;
		case FL_Left:
			ship->setRotatingLeft(false);
			return 1;
		case 32:
			ship->setShooting(false);
			return 1;
		}
		return 1;

	default :
		return Fl_Widget::handle(event);
	}
}

void GameWindow::updatePositions() {  //update all positions
	ship->updatePos();
	for (unsigned int i = 0; i < asteroids.size(); ++i)
		asteroids.at(i)->updatePos();
	for (unsigned int i = 0; i < bullets.size(); ++i)
		bullets.at(i)->updatePos();
}

int refresh_ticks = 0;  //for asteroid spawn rate
void GameWindow::refreshGame() {
	refresh_ticks++;
	//spawn asteroid if enough time has passed
	if (asteroids.size() < max_asteroids && refresh_ticks > spawn_interval) {
		spawnAsteroid();
		refresh_ticks = 0;
	}

	updatePositions();
	checkEndGame();
	checkBullets();
	redraw();
}

void GameWindow::spawnAsteroid() {  //spawn one asteroid
	begin();
	asteroids.push_back(new Asteroid(this, Vec2(10,10 ),
		Vec2::fromAngleDeg((rand() % 360) + 1) * asteroid_speed));
	end();
}

//spawn one bullet
void GameWindow::addBullet(Vec2 pos, Vec2 velocity) {
	begin();
	bullets.push_back(new Bullet(this, pos, velocity));
	end();
}

void GameWindow::checkBullets() {
	for (unsigned int i = 0; i < bullets.size(); ++i) {

		//delete bullet if out of range
		if (bullets.at(i)->checkOutOfBounds()) {
			Fl::delete_widget(bullets.at(i));
			bullets.erase(bullets.begin() + i);
		}
		else {  //delete bullet/asteroid if they collide
			for (unsigned int n = 0; n < asteroids.size(); ++n) { 
				if (bullets.at(i)->checkCollision(asteroids.at(n))) {
					Fl::delete_widget(asteroids.at(n));
					Fl::delete_widget(bullets.at(i));
					asteroids.erase(asteroids.begin() + n);
					bullets.erase(bullets.begin() + i);
					asteroids_hit++;
				}
			}
		}
	}
}

void GameWindow::checkEndGame() {  //check for asteroid/ship collision
	for (unsigned int i = 0; i < asteroids.size(); ++i)
		if (ship->checkCollision(asteroids.at(i))) {
			Fl::delete_widget(this);
			cout << "Seconds survived: " << cycles_survived / 30.0
				<< endl << "Asteroids hit: " << asteroids_hit << endl;
			cout << "Press Enter to exit..." << endl;
			cin.ignore();
		}
	cycles_survived++;
}