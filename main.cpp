#include <iostream>
#include <ctime>



int main()
{

    std::clock_t    start;

    start = std::clock();
         // your test


    int n = 1000000000;
    while(n != 0) {
        //std::cout << "Hello World!" << std::endl;
        --n;
    }


    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    //std::cout << std::endl << stop - start << std::endl;

    return 0;
}

