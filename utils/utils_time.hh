#pragma once

#include <chrono>

using namespace std::chrono;

class TaskTime
{
    public:
        TaskTime();
        void endTask();
        void printTaskTimeMs();
        void printTaskTimeAll();
        void endTaskAndPrintTime();

    private:
        time_point<high_resolution_clock> start;
        time_point<high_resolution_clock> end;

};