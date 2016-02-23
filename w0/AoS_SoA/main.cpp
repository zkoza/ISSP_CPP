#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>


struct X
{
    float x[3];
    float v[3];
    float kolor[4]; // nieużywane, ale celowo zajmuje miejsce
};


std::chrono::duration<double> AoS(int N)
{
    float dt = 0.1;

    std::vector<X> tab (N);

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++)
    {
        tab[i].x[0] += tab[i].v[0] * dt;
        tab[i].x[1] += tab[i].v[1] * dt;
        tab[i].x[2] += tab[i].v[2] * dt;
    }
    return std::chrono::system_clock::now() - start;
}

std::chrono::duration<double> SoA(int N)
{
    float dt = 0.1;
    std::vector<float> x(N);
    std::vector<float> y(N);
    std::vector<float> z(N);
    std::vector<float> vx(N);
    std::vector<float> vy(N);
    std::vector<float> vz(N);


    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++)
        x[i] += vx[i] * dt;
    for (int i = 0; i < N; i++)
        y[i] += vy[i] * dt;
    for (int i = 0; i < N; i++)
        z[i] += vz[i] * dt;
    return std::chrono::system_clock::now() - start;
}

int main()
{
    const int N = 20000000;

    std::cout << "Testing N = " << N << " (" << sizeof(X)*N/1e6 << " MB)\n";

    std::chrono::duration<double> t_aos = AoS(N);
    std::cout << "finished computation #1 (Array of Strustures) after "
              << t_aos.count() << " s\n";
    std::chrono::duration<double> t_soa = SoA(N);
    std::cout << "finished computation #2 (Structure of Arrays) after "
              << t_soa.count() << " s\n";
}

