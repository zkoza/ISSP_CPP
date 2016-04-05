#include <iostream>
#include "wektor.h"                  // włączenie interfejsu klasy

// Poniższą implementację można i trzeba zoptymalizować,
// żeby niepotrzebnie nie wywoływać pary operatorów new/delete
Wektor & Wektor::operator= (Wektor const& wek)
{
    std::cout << __FUNCTION__ << " [copy]\n"; // diagnostyka

    if (this == &wek)                // czy kopiujemy obiekt na samego siebie?
        return *this;

    delete [] _ptab;                 // zwolnienie pamięci
    _rozmiar = wek._rozmiar;         // skopiowanie rozmiaru
    _ptab = new int [_rozmiar];      // zarezerwowanie nowej pamięci

    for (size_t i = 0; i < _rozmiar; i++)  // skopiowanie danych
        _ptab[i] = wek._ptab[i];
    return *this;                    // zwrócenie referencji "do siebie"
}


Wektor::Wektor(size_t n, int value)
: _rozmiar(n),
  _ptab(new int[n])
{
    std::cout << "ctor [n]\n"; // diagnostyka

    for (int i = 0; i < (int)_rozmiar; i++)
        _ptab[i] = value;
}


Wektor::Wektor(Wektor const& w)
    :  _rozmiar (w._rozmiar),
       _ptab(0)
{
    std::cout << "ctor [copy]\n";

    _ptab = new int [_rozmiar];
    for (size_t i = 0; i < _rozmiar; i++)  // skopiowanie danych
        _ptab[i] = w._ptab[i];
}


Wektor & operator+= (Wektor & lhs, Wektor const& rhs)
{
    std::cout << __FUNCTION__ << "\n";

    if (lhs.size() != rhs.size())
        throw std::string(__FUNCTION__) + ": sizes don't match";

    for (int i = 0; i < (int)lhs.size(); i++)
        lhs[i] += rhs[i];

    return lhs;
}


Wektor operator+(Wektor lhs, Wektor const& rhs)
{
    if (lhs.size() != rhs.size())
        throw std::string(__FUNCTION__) + ": sizes don't match";

    lhs += rhs;
    return lhs;
}


void add3(Wektor & target, Wektor const& v1, Wektor const& v2, Wektor const& v3)
{
    if (target.size() != v1.size() || v1.size() != v2.size() || v2.size() != v3.size())
        throw std::string(__FUNCTION__) + ": sizes don't match";

    for (int i = 0; i < (int)target.size(); i++)
    {
        target[i] = v1[i] + v2[i] + v3[i];
    }
}


#if __cplusplus >= 201103L

Wektor &  Wektor::operator= (Wektor && wek)
{
    std::cout << __FUNCTION__ << " [move]\n";
    if (this == &wek)                // czy kopiujemy obiekt na samego siebie?
        return *this;

    delete [] _ptab;           // zwolnienie pamięci
    _rozmiar = wek._rozmiar;   // skopiowanie rozmiaru
    _ptab = wek._ptab;         // "przeniesienie" pamięci
    wek._ptab = nullptr;       // wyzerowanie oryginału
    wek._rozmiar = 0;          // wyzerowanie oryginału
    return *this;
}


Wektor::Wektor(Wektor && w)
    : _rozmiar(w._rozmiar),
      _ptab (w._ptab)
{
    std::cout << "ctor [move]\n";

    w._rozmiar = 0;
    w._ptab = nullptr;
}


#endif



