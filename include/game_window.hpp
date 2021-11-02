#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include <opencv2/opencv.hpp>
#include "shape.hpp"
#include "circle.hpp"
#include "timed_function.hpp"
#include "snake.hpp"
#include "star.hpp"

#define CIRCLE_SIZE 10

class GameWindow {

private:
    std::string window_name_;
    float screen_width_;
    float screen_height_;
    bool running_ = true;

    int points_ = 0;
    cv::Scalar background_color_;
    
    Snake snake_;
    cv::Point2f snake_direction_ = {1, 0};
    
    unsigned int id_count_ = 1;
    std::vector<std::pair<unsigned int,Shape*>> shapes_id_ptr_vec_;
    std::vector<TimedFunction*> timed_functions_;

public:
    GameWindow(std::string window_name, float screen_width, float screen_height)
        : window_name_(window_name), screen_width_(screen_width), screen_height_(screen_height) 
    {
        background_color_ = cv::Scalar(137, 247, 214); //BGR
        shapes_id_ptr_vec_.reserve(1000);
        std::srand(std::time(nullptr));
        snake_ = Snake();
        snake_.extend(5);
        setup();
    };

    ~GameWindow(){
        for (auto& pair_shape : shapes_id_ptr_vec_) {
            delete pair_shape.second;
        }
        for (auto& timed_function : timed_functions_){
            delete timed_function;
        }
        cv::destroyWindow(window_name_);
    };

    void setup(){
        timed_functions_.emplace_back(new TimedFunction( std::bind(&GameWindow::circle_spawn, this), std::chrono::milliseconds(2000)));        
        timed_functions_.emplace_back(new TimedFunction( std::bind(&GameWindow::star_spawn, this), std::chrono::milliseconds(10000)));        
    };

    void start(){
        circle_spawn();
    };

    void run(){
        while (running_) {
            render_frame();
            static float freq = 10;
            freq = freq + 0.01;
            int delay = 1000/freq;
            int key = cv::waitKey(delay);
            handle_key_event(key);
        }
    };

private:

  int checkCollision(){
        for (auto shape_pair : shapes_id_ptr_vec_){
            if (shape_pair.second->checkCollision(snake_.getHeadPosition())){
                return shape_pair.first;
            }
        }
        return -1;
    };

    void print_points(cv::Mat& frame){
        std::string points_str = std::string("Points: ") + std::to_string(points_);
        cv::putText(frame, points_str, cv::Point2f(10,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1, cv::LINE_AA);
    }

    void render_frame(){
        
        cv::Mat frame(screen_height_, screen_width_, CV_8UC3, background_color_);

        for (auto& timed_function : timed_functions_){
            timed_function->call();
        }

        for (auto& pair_shape : shapes_id_ptr_vec_) {
            pair_shape.second->draw(frame);
        }

        snake_.setDirection(snake_direction_);
        
        snake_.move(screen_width_, screen_height_);
        snake_.draw(frame);
        if (snake_.checkAutoCollision()){
            gameOver();
        }
        int collision_id = checkCollision();
        if (collision_id != -1){
            auto iter = std::find_if(shapes_id_ptr_vec_.begin(), shapes_id_ptr_vec_.end(), [collision_id](const std::pair<unsigned int, Shape*>& shape_pair){
                return shape_pair.first == collision_id;
            });

            if (iter != shapes_id_ptr_vec_.end()){
                if ( (*iter).second->get_shape_type() == shape_types::CIRCLE){
                    shapes_id_ptr_vec_.erase(iter);
                    points_++;
                    snake_.extend(1);
                }
                else if((*iter).second->get_shape_type() == shape_types::STAR)
                {
                    shapes_id_ptr_vec_.erase(iter);
                    points_ = points_ + 5;
                    snake_.extend(5);
                }
            }
        }
        
        print_points(frame);
        cv::imshow(window_name_, frame);
    };

    void circle_spawn(){

        int random_x = (rand() % (((int)screen_width_)/20)) * 20;
        int random_y = (rand() % ((int)screen_height_/20)) * 20;

        shapes_id_ptr_vec_.emplace_back(std::pair<unsigned int,Shape*>(id_count_,
            new Circle(cv::Point(random_x,random_y), CIRCLE_SIZE, cv::Vec3f(0, 0, 255))));
        
        id_count_++;
    };

    void star_spawn(){

        int random_x = (rand() % (((int)screen_width_)/20)) * 20;
        int random_y = (rand() % ((int)screen_height_/20)) * 20;

        shapes_id_ptr_vec_.emplace_back(std::pair<unsigned int,Shape*>(id_count_,
            new Star(cv::Point(random_x,random_y))
        ));
        
        id_count_++;
    };

    void gameOver(){
        std::cout << "Game Over" << std::endl;
        std::cout << "Points: " << points_ << std::endl;
        
        cv::Mat image = cv::Mat(screen_height_, screen_width_, CV_8UC3, background_color_);
        std::string game_over_str = std::string("Game Over, Points : ") + std::to_string(points_);

        cv::putText(image, game_over_str, 
        cv::Point2f(screen_width_/4 - 20 , screen_height_/2), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,0), 1, cv::LINE_AA);

        cv::imshow(window_name_, image);
        cv::waitKey(0);
        running_ = false;
    };


    void handle_key_event(int key){
        switch (key){
            case 81:
                {// std::cout << "ARROW LEFT" << std::endl;
                if (snake_direction_ != cv::Point2f(1,0)){
                    snake_direction_ = cv::Point2f(-1,0);}
                }
            break;
            case 82:
                {// std::cout << "ARROW UP" << std::endl;
                    if (snake_direction_ != cv::Point2f(0,1)){
                        snake_direction_ = cv::Point2f(0,-1);
                    }
                }
            break;
            case 83:
                {// std::cout << "ARROW RIGHT" << std::endl;
                if (snake_direction_ != cv::Point2f(-1,0)){
                    snake_direction_ = cv::Point2f(1,0);}
                }
                break;
            case 84:
                {// std::cout << "ARROW DOWN" << std::endl;
                if (snake_direction_ != cv::Point2f(0,-1)){
                    snake_direction_ = cv::Point2f(0,1);}
                }
                break;

            // escape key
            case 27:
                {
                    std::cout << "ESC key is pressed by user" << std::endl;
                    running_ = false;
                }
                break;
            default:{
                if (key > 0){
                    std::cout << "key: " << key << std::endl;
                }
            }     
            break;
        }
    };
  
}; //Snake

