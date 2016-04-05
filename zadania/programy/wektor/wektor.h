#pragma once

#include <cstdlib>     // <-- żeby kompilator rozpoznawał typ size_t

class Wektor
{
private:
    size_t _rozmiar;
    int *  _ptab;

public:
    Wektor(size_t n, int value = 0);
    Wektor(Wektor const& w);
#if __cplusplus >= 201103L
    Wektor(Wektor && w);
#endif
    ~Wektor()                       { delete [] _ptab; }

    size_t size() const             { return _rozmiar; }
    int & operator [](int n)        { return _ptab[n]; }
    int   operator [](int n) const  { return _ptab[n]; }

    Wektor & operator= (Wektor const& wek);  // <-- deklaracja metody

#if __cplusplus >= 201103L
    Wektor &  operator= (Wektor && wek);  // <-- deklaracja metody
#endif
};


Wektor & operator+= (Wektor & lhs, Wektor const& rhs);
Wektor   operator+  (Wektor lhs,   Wektor const& rhs);

void add3(Wektor & target, Wektor const& v1, Wektor const& v2, Wektor const& v3);


