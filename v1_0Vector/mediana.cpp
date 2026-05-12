#include "mediana.h"
#include <algorithm>

double mediana(std::vector<int> nd)
{
    if (nd.empty())
        return 0.0;
    std::sort(nd.begin(), nd.end());
    int n = nd.size();
    if (n % 2 == 0)
        return (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
    return nd[n / 2];
}

double vidurkis(std::vector<int> nd)
{
    if (nd.empty())
        return 0.0;
    int sum = 0;
    for (int x : nd)
        sum += x;
    return sum / nd.size();
}