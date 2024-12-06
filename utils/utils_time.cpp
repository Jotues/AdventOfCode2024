#include "utils_time.hh"
#include <stdio.h>
#include <iostream>

TaskTime::TaskTime()
{
    start = high_resolution_clock::now();
}

void TaskTime::endTask()
{
    end = high_resolution_clock::now();
}

void TaskTime::printTaskTimeMs()
{
    auto duration = duration_cast<microseconds>(end - start);
    printf("Time taken = %ld [us]\n", duration.count());
}

void TaskTime::printTaskTimeAll()
{
    auto duration = duration_cast<milliseconds>(end - start).count();
    auto miliseconds = duration % 1000;
    duration /= 1000;
    auto seconds = duration % 60;
    duration /= 60;
    auto minutes = duration % 60;
    duration /= 60;
    auto hours = duration;
    std::cout<<"Time taken pretty: " << hours << "h " << minutes << "m " << seconds << "s " << miliseconds << "ms\n";
}

void TaskTime::endTaskAndPrintTime()
{
   endTask();
   printTaskTimeMs();
   printTaskTimeAll();
}