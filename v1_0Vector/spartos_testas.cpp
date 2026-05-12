#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include "vector.h"

using namespace std::chrono;

template <typename Container>
double matuoti(unsigned int sz)
{
    auto start = high_resolution_clock::now();
    Container v;
    for (unsigned int i = 1; i <= sz; i++)
        v.push_back(i);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

int main()
{
    std::vector<unsigned int> dydžiai = {
        10000, 100000, 1000000, 10000000, 100000000};

    std::cout << std::left;
    std::cout << "Elementu sk.   std::vector    Vector\n";
    std::cout << "--------------------------------------------\n";

    for (auto sz : dydžiai)
    {
        double t1 = matuoti<std::vector<int>>(sz);
        double t2 = matuoti<Vector<int>>(sz);
        std::cout << std::setw(15) << sz
                  << std::setw(15) << t1
                  << std::setw(15) << t2 << "\n";
    }
    return 0;
}