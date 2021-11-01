#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "shape.hpp"

class Star: public Shape 
{
private:
    int thickness_ = -1;
    float size_ = 10;
public:
    
    Star()
        : Shape()
        {
            shape_type_ = shape_types::STAR;
        };
    
    Star(cv::Point2f center,  float size=10)
        : Shape(center, cv::Vec3f(0,255,222)), size_(size)
        {
            shape_type_ = shape_types::STAR;
        };
        
    void draw(cv::Mat &img) override{
        cv::Point2f center = center_;
        std::vector<cv::Point2i> points_vec;
        points_vec.reserve(10);
        for (int i = 0; i < 10; i++)
        {
            cv::Point2f point;
            point = center;
            float angle = i * 2 * CV_PI / 10;
            if (i % 2 == 0)
            {
                point.x += size_ * cos(angle);
                point.y += size_ * sin(angle);
            }
            else
            {    
                point.x += size_/2.5 * cos(angle);
                point.y += size_/2.5 * sin(angle);
            }
            points_vec.push_back(point);
        }
        cv::fillConvexPoly(img, points_vec, cv::Scalar(color_[0], color_[1], color_[2]),cv::LINE_AA,0);
        cv::polylines(img, points_vec, true, cv::Scalar(0,0,0), 1, cv::LINE_AA, 0);

    };

    void set_thickness(float thickness){
        thickness_ = thickness;
    };

    bool checkCollision(const cv::Point2f &point) override{
      
        float distance = cv::norm(center_ - point);
        return distance <= size_ + 5;

    };
    

};