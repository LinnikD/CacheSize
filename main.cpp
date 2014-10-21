#include <iostream>
#include <ctime>
#include <vector>

double calcTime(std::clock_t start, std::clock_t stop) {
    return (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
}

int main()
{

    std::clock_t start;

    start = std::clock();


    int n = 1000000000;
    while(n != 0) {
        --n;
    }


    return 0;
}

