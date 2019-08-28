#pragma once
#include <FL/Fl_Window.H>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"
#include "Spaceship.h"

class GameWindow : public Fl_Window {
private:
    // Objects in window
    std::vector<Asteroid*> asteroids;
    std::vector<Bullet*> bullets;
    Spaceship* ship;

    // Asteroid-spawning variables
    static const int max_asteroids;
    static const int spawn_interval;
    static const double asteroid_speed;

    // Score-keeping variables
    int cycles_survived;
    int asteroids_hit;
    
    // callback function for timer
    static void timer_cb(void* ptr);

public:
    GameWindow(int w, int h);

    void spawnAsteroid();

    void addBullet(Vec2 pos, Vec2 velocity);

    void refreshGame();

    void updatePositions();

    void checkBullets();

    void checkEndGame();

    int handle(int event);
};