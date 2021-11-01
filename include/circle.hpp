#pragma once
#include <opencv2/opencv.hpp>
#include "shape.hpp"

class Circle: public Shape 
{
private:
    float radious_ = 100;
    float thickness_ = -1;
    
public:
    Circle()
        : Shape()
        {
            shape_type_ = shape_types::CIRCLE;
        };
    
    Circle(cv::Point2f center, float radious, cv::Vec3f color)
        : Shape(center, color)
        {
            radious_ = radious;
            shape_type_ = shape_types::CIRCLE;
        };

    void draw(cv::Mat &img) override{
        cv::circle(img, center_, radious_, color_, -1);
        cv::circle(img, center_, radious_, cv::Scalar(0,0,0), 1);
    };

    void set_radious(float radious){
        radious_ = radious;
    };

    void set_thickness(float thickness){
        thickness_ = thickness;
    };

    bool checkCollision(const cv::Point2f &point) override{
        float distance = cv::norm(center_ - point);
        return distance <= radious_ + 5;
    };

};