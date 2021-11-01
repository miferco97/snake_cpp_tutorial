#pragma once
#include <functional>
#include <chrono>

class TimedFunction {
private:
    std::function<void()> function;
    std::chrono::milliseconds interval;
    std::chrono::time_point<std::chrono::system_clock> last_call;
     
public:
    TimedFunction(std::function<void()> function, std::chrono::milliseconds interval)
        : function(function), interval(interval), last_call(std::chrono::system_clock::now()) {};
    void call(){
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_call).count() >= interval.count()){
            function();
            last_call = std::chrono::system_clock::now();
        }
    };
};

