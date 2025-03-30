/**
 ____    ____    ____    __________________    ____    ____    ____
||I ||  ||c ||  ||e ||  ||                ||  ||M ||  ||a ||  ||n ||
||__||  ||__||  ||__||  ||________________||  ||__||  ||__||  ||__||
|/__\|  |/__\|  |/__\|  |/________________\|  |/__\|  |/__\|  |/__\|

*/

#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

#define PB push_back
#define X first
#define Y second
#define eps (double)(1e-9)


typedef unsigned long long ull;
typedef std::pair <int, int> pii;
typedef long long ll;
typedef std::pair <ll, ll> pll;
typedef std::pair <int, ll> pil;
typedef std::pair <ll, int> pli;
typedef long double ld;



int n, m;
std::vector <std::vector <double> > a;

void read()
{
    std::cin >> n >> m;

    a.resize(n);
    for(int i = 0; i < n; i++)
    {
        a[i].resize(m);
        for(int j = 0; j < m; j++)
            std::cin >> a[i][j];
    }
}



/**
cases
0 - no solutions
1 - one solution
2 - infinitely many solutions
*/

std::pair <int, std::vector <double> > solve(std::vector <std::vector <double> >& a)
{
    std::pair <int, std::vector <double> > ans;
    ans.Y.resize(m - 1);

    int i = 0, j = -1;

    std::vector <int> mem;
    mem.resize(m);
    for(int k = 0; k < m; k++)
        mem[k] = -1;

    while(i < n && j < m - 1)
    {
        j++;
        int maxx = i;
        for(int k = i; k < n; k++)
            if(abs(a[k][j]) > abs(a[maxx][j]))
                maxx = k;

        if(abs(a[maxx][j]) < eps)
            continue;


        for(int k = j; k < m; k++)
            std::swap(a[i][k], a[maxx][k]);
        mem[j] = i;

        for(int k = 0; k < n; k++)
        {
            if(k == i)
                continue;

            double coef = a[k][j] / a[i][j];
            for(int z = j; z < m; z++)
                a[k][z] -= coef * a[i][z];
        }

        i++;
    }

    for(int i = 0; i < m - 1; i++)
        ans.Y[i] = 0;

    for(int i = 0; i < m - 1; i++)
        if(mem[i] != -1)
            ans.Y[i] = a[mem[i]][m - 1] / a[mem[i]][i];

    for(int i = 0; i < n; i++)
    {
        double till = 0;

        for(int j = 0; j < m - 1; j++)
            till += ans.Y[j] * a[i][j];

        if(abs(till - a[i][m - 1]) > eps)
            return {0, {}};
    }

    ans.X = 1;
    for(int i = 0; i < m - 1; i++)
        if(mem[i] == -1)
            ans.X = 2;
    return ans;
}


void combine()
{
    read();
    std::pair <int, std::vector <double> > ans = solve(a);

    if(ans.X == 0)
    {
        std::cout << "No solutions!" << "\n";
        exit(0);
    }

    if(ans.X == 1)
        std::cout << "There is only one solution" << "\n";
    else
        std::cout << "There are infinitely many solutions here is one of them" << "\n";

    for(int i = 0; i < m - 1; i++)
        std::cout << ans.Y[i] << " ";
    std::cout << "\n";
}



int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    combine();

    return 0;
}
