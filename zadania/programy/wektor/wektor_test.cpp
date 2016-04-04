#include <iostream>
#include <ctime>
#include "wektor.h"

Wektor make_wektor(int n, bool test = true)
{
    Wektor wynik (n);
    for (int i = 0; i < n; i++)
        wynik[i] = i;
    Wektor wynik2 (n);
    if (test)
      return wynik;
    else
      return wynik2;
}

Wektor make_simple_wektor(int n)
{
    Wektor wynik (n);
    for (int i = 0; i < n; i++)
        wynik[i] = i;
    return wynik;
}


int suma(Wektor  w)
{
    int wynik = 0;
    for (int i = 0; i < (int)w.size(); i++)
        wynik += w[i];
    return wynik;
}
int main()
{
    const int N = 50000000;
    const char* mode = (__cplusplus >= 201103L) ? "C++11" : "c++98";

    std::cout << "compiler mode: " << mode << "\n";

    Wektor v(N);
    std::cout << "> vector size: " << v.size() << "\n";
    std::cout << "> testing operator[]:\n";
    std::cout << "v[3] = " << v[3] << "\n";
    v[3] = 8;
    std::cout << "v[3] = " << v[3] << "\n";
    std::cout << "> creating a const copy\n";
    const Wektor vc = v;
    std::cout << "> testing operator[] const:\n";
    std::cout << "vc[3] = " << vc[3] << "\n";

    std::cout << "> testing v = v\n";
    v = v;
    std::cout << "> testing make_wektor in a constructor\n";
    Wektor w = make_wektor(N);
    std::cout << "> testing make_wektor in operator=\n";
    v = make_wektor(N);
    std::cout << "> testing make_simple_wektor in a constructor\n";
    Wektor v2 = make_simple_wektor(N);
    std::cout << "> testing make_simple_wektor in operator=\n";
    v = make_simple_wektor(N);


    std::cout << "> creating a copy of a wektor\n";

    Wektor v3 = v;
     std::cout << "======== testing operator+ performance (" << mode << ") ========\n";
    clock_t t0 = clock();
    w  = v + v2 + v3 ;
    clock_t t1 = clock();
    std::cout << "> elapsed time (operator+): " << double(t1 - t0)/CLOCKS_PER_SEC << "\n";
    std::cout << "======== testing operator+= performance (" << mode << ") =======\n";
    t0 = clock();
    w = v;
    w += v2;
    w += v3;
    t1 = clock();
    std::cout << "> elapsed time (operator+=): " << double(t1 - t0)/CLOCKS_PER_SEC << "\n";
    t0 = clock();
    add3(w, v, v2, v3);
    std::cout << "======== testing C-style performance ========\n";
    t1 = clock();
    std::cout << "> elapsed time (C-style): " << double(t1 - t0)/CLOCKS_PER_SEC << "\n";

}

