#include <iostream>
#include <vector>
#include "Vector.h"

template <typename Container>
int skaiciuotiPerskirstymus(unsigned int sz)
{
    Container v;
    int perskirstymai = 0;
    for (unsigned int i = 1; i <= sz; i++)
    {
        if (v.capacity() == v.size())
            perskirstymai++;
        v.push_back(i);
    }
    return perskirstymai;
}

int main()
{
    unsigned int sz = 100000000;
    std::cout << "std::vector perskirstymai: "
              << skaiciuotiPerskirstymus<std::vector<int>>(sz) << "\n";
    std::cout << "Vector perskirstymai:      "
              << skaiciuotiPerskirstymus<Vector<int>>(sz) << "\n";
    return 0;
}