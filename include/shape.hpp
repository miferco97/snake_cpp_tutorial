#pragma once
#include <opencv2/opencv.hpp>
#include <string>

enum shape_types {EMPTY, CIRCLE, SQUARE, TRIANGLE, STAR};

class Shape
{   
protected:
    shape_types shape_type_;
    cv::Point2f center_;
    cv::Vec3f color_;

public:
    Shape(){};
    Shape(cv::Point2f center, cv::Vec3f color = cv::Vec3f(255,255,255)){
        center_ = center;
        color_ = color;
    };

    shape_types get_shape_type(){return shape_type_;};
    void setColor(cv::Vec3f color){
        color_ = color;
    };
    void setColor(float r, float g, float b){
        color_ = cv::Vec3f(r, g, b);
    };

    void setCenter(cv::Point2f center){
        center_ = center;
    };

    void setCenter(float x, float y){
        center_ = cv::Point2f(x, y);
    };

    cv::Point2f getCenter(){
        return center_;
    };

    virtual bool checkCollision(const cv::Point2f &) = 0 ;

    virtual void draw(cv::Mat &img) = 0;

};