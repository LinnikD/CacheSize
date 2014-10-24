#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>



struct Node {
    Node * next_sequential;
    Node * next_random;
    long val[2];
};


double calcTime(std::clock_t start, std::clock_t stop) {
    return (stop - start) / (double)(CLOCKS_PER_SEC / 1000000);
}

int * mix(int *a, int size) {
    srand( time(0) );
    int first;
    int second;
    for(int i = 0; i < size * 4; i++) {
        first = rand() % size;
        second = rand() % size;
        std::swap(a[first], a[second]);
    }
    return a;
}

Node * initNodeArray(size_t size) {
    Node * arr = new Node[size];
    int * a = new int[size];
    for(unsigned i = 0; i < size; i++) {
        a[i] = i;
        arr[i].val[0] = a[i];
    }
    for(unsigned i = 0; i < size - 1; i++) {
        arr[i].next_sequential = &arr[i + 1];
    }

    a = mix(a, size);

    for(unsigned i = 0; i < size; i++) {
        arr[i].next_random = &arr[a[i]];
    }
    delete[] a;
    return arr;
}

double testSequence(Node * nodes, size_t size) {
    double sum = 0;
    std::clock_t start = clock();
    for(unsigned i = 0; i < size; i++) {
        sum += nodes->val[0];
        nodes = nodes->next_sequential;
    }
    std::clock_t stop = clock();
    return calcTime(start, stop);
}



double testRandom(Node * nodes, size_t size) {
    long long sum = 0;
    std::clock_t start = clock();
    for(unsigned i = 0; i < size; i++) {
        sum += nodes->val[0];
        nodes = nodes->next_random;
    }
    std::clock_t stop = clock();
    return calcTime(start, stop);

}




int main()
{
    const int repeats = 8;
    const int steps = 350;

    const size_t kb = 1024;
    const size_t mb = 1024 * kb;


    size_t init_size = 16 * kb / sizeof(Node);
    size_t small_init_size = 1 * kb / sizeof(Node);
    size_t size =  1 * kb / sizeof(Node);

    Node * nodes = initNodeArray(size);
    for(int j = 0; j < steps; j++) {

        double rand_sum = 0;
        double seq_sum = 0;

        for(int i = 0; i < repeats; i++) {
            nodes = initNodeArray(size);
            seq_sum += testSequence(nodes, size);
            rand_sum += testRandom(nodes, size);
        }

        std::cout.setf(std::ios::fixed);
        std::cout.precision( 3 );
        std::cout << size / sizeof(Node) << "kb :"
                  << seq_sum * 1000 /(size * (double)repeats) << "   ---   "
                  << rand_sum * 1000 /(size * (double)repeats)
                  << std::endl;
        if(size >= init_size * 3)
            size += init_size;
        else
            size += small_init_size;
    }

    delete[] nodes;

    return 0;
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


    std::cout << calcTime(start, stop) / (double)size * 1000.0 << " ms    ---    ";

    mix(a,size);
    sum = 0;

    start = clock();
    for(unsigned i = 0; i < size; i++) {
        sum += data->at(a[i]);
    }
    stop = clock();

    std::cout << calcTime(start, stop) / (double)size * 1000.0 << " ms" << std::endl;

    delete[] a;
    delete data;
}

