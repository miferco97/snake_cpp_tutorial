#pragma once
#include <opencv2/opencv.hpp>
#include "shape.hpp"

class Square: public Shape 
{
private:
    float thickness_ = -1;
    float size_ = 10;
public:
    
    Square()
        : Shape()
        {
            shape_type_ = shape_types::SQUARE;
        };
    
    Square(cv::Point2f center, cv::Vec3f color=cv::Vec3f(255,255,255))
        : Shape(center, color)
        {
            shape_type_ = shape_types::SQUARE;
        };

    Square(cv::Point2f center, cv::Vec3f color=cv::Vec3f(255,255,255), float size=10)
        : Shape(center, color), size_(size)
        {
            shape_type_ = shape_types::SQUARE;
        };
        
    void draw(cv::Mat &img) override{
        cv::rectangle(img, center_ - cv::Point2f(size_, size_), center_ + cv::Point2f(size_, size_), color_, thickness_);
    };

    void set_thickness(float thickness){
        thickness_ = thickness;
    };

    bool checkCollision(const cv::Point2f &point) override{
        return (point.x >= center_.x - size_ && point.x <= center_.x + size_ &&
                 point.y >= center_.y - size_ && point.y <= center_.y + size_);
    };
    

};