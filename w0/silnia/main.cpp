#include <iostream>

int silnia(int n)
{
    if (n == 0)
        return 1;
    else
        return n*silnia(n-1);
}

int main()
{
    for (int i = 0; i < 20; i++)
        std::cout << i << "! =\t" << silnia(i) << "\n";
 //  std::cout << silnia(70000) << "\n";
}
