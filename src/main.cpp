#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "circle.hpp"
#include "game_window.hpp"
#include "snake.hpp"


#define WINDOW_NAME "Snake"
#define WIDTH 630
#define HEIGHT 490

int main() {
    
    GameWindow window(WINDOW_NAME, WIDTH, HEIGHT);
    window.start();
    window.run();
    
    return 0;
}