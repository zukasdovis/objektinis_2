#include "tyrimai.h"
#include "generatorius.h"
#include "rusiavimas.h"
void tyrimai()
{
    cout << "Kuri tyrima norite atlikti: 1 ar 2?";
    int x;
    cin >> x;

    if (x == 1)
    {
        pirmasTyrimas();
    }
    else if (x == 2)
    {
        antrasTyrimas();
    }
    else
        cout << "Bloga isvestis";
}
void pirmasTyrimas()
{
    generuotiVisus();
}
void antrasTyrimas()
{
    cout << "Koks studentu failas(1000, 10000, 100000, 1000000, 10000000)?\n";
    int x;
    cin >> x;

    cout << "Kuris rusiavimo metodas? 1, 2 ar 3?\n";
    int y;
    cin >> y;
    switch (y)
    {
    case 1:
        failoRusiavimas1(x);
        break;
    case 2:
        failoRusiavimas2(x);
        break;
    case 3:
        failoRusiavimas3(x);
    }
}