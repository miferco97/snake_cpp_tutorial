#include "game_window.hpp"

#define WINDOW_NAME "Snake"
#define WIDTH 630
#define HEIGHT 490

int main() {
    
    GameWindow window(WINDOW_NAME, WIDTH, HEIGHT);
    window.start();
    window.run();
    
    return 0;
}