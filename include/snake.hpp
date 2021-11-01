#pragma once
#include <vector>
#include <array>

#include "shape.hpp"
#include "square.hpp"

class Snake: public Shape
{
private: 
    std::vector<Square> body;
    cv::Point2f direction_ = {1,0}; // [0] x [1] y
    float size_ = 10;
    cv::Point2f origin_position_ = {0,0};

public:
    Snake()
        : Shape()
    {
        body.emplace_back(origin_position_,cv::Vec3f(0,0,0),size_*1.1);
    };
    ~Snake(){};

    void setDirection(int x, int y){
        direction_.x = x;
        direction_.y = y;
    };

    void setDirection(const cv::Point2f& dir){
        direction_ = dir;
        
    };

    cv::Point2f getHeadPosition(){
        return body[0].getCenter();
    };

    void draw(cv::Mat& img){
        for(auto& square: body){
            square.draw(img);
        }
    };

    void move(int img_width = 720, int img_height = 640){
        for(int i = body.size()-1; i > 0; i--){
            body[i].setCenter(body[i-1].getCenter());
        }
        cv::Point2f new_center = body[0].getCenter() + direction_ * (size_*2);

        if (new_center.x < 0)
            new_center.x += img_width;
        if (new_center.y < 0)
            new_center.y += img_height;        

        new_center.x = (int) new_center.x % img_width;
        new_center.y = (int) new_center.y % img_height;

        body[0].setCenter(new_center);
    };

    bool checkAutoCollision(){
        for(int i = 1; i < body.size(); i++){
            if(body[i].checkCollision(getHeadPosition())){
                return true;
            }
        }
        return false;
    };

    bool checkCollision(const cv::Point2f &point) override{
        return false;
    };

    void extend(int n_extend){
        for(int i = 0; i < n_extend; i++){
            if (body.size()%2 ==0){
                body.push_back(Square(body[body.size()-1].getCenter(),cv::Vec3f(247,151,209),size_));
            }
            else{
                body.push_back(Square(body[body.size()-1].getCenter(),cv::Vec3f(7,147,253),size_));
            }
        }
    };
    

};

