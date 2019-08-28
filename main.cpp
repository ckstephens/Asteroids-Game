#include <Windows.h>            // Windows only
#include <ctime>
#include "GameWindow.h"
using namespace std;

int main() {
    srand(time(nullptr));

    GameWindow* game = new GameWindow(800, 600);
    return Fl::run();
}