#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>

/*
class Node {
public:
    Node * next_sequential;
    Node * next_random;
    int * val;
};

class List {
public:
    List(Node * n, int size) {

    }
    getNextSeq() {

    }
    getNextRend() {

    }
    void addNode(node) {

    }


private:
    Node * head;
    Node * current;

};*/

double calcTime(std::clock_t start, std::clock_t stop) {
    return (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
}

int * mix(int *a, int size) {
    int first;
    int second;
    for(int i = 0; i < size * 4; i++) {
        first = rand() % size;
        second = rand() % size;
        std::swap(a[first], a[second]);
    }

    return a;
}


void cacheTest(size_t size) {
    int * a = new int[size];
    for(unsigned i = 0; i < size; i ++) {
        a[i] = i;
    }

    std::vector<int> *data = new std::vector<int>;
    for(unsigned i = 0; i < size; i++) {
        data->push_back(i);
    }

    long long sum = 0;

    std::clock_t start = clock();
    for(unsigned i = 0; i < size; i++) {
        sum += data->at(a[i]);
    }
    std::clock_t stop = clock();

    std::cout << sum << std::endl;
    std::cout << calcTime(start, stop) << " ms" << std::endl;

    mix(a,size);
    sum = 0;

    start = clock();
    for(unsigned i = 0; i < size; i++) {
        sum += data->at(a[i]);
    }
    stop = clock();

    std::cout << sum <<std::endl;
    std::cout << calcTime(start, stop) << " ms" << std::endl;

    delete[] a;
    delete data;
}



int main()
{

    const size_t kb = 1024;
    const size_t mb = 1024 * kb;

    const size_t size =  1 * mb / sizeof(int);

    cacheTest(size);

    return 0;
}

