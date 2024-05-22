/**
 ____    ____    ____    __________________    ____    ____    ____
||I ||  ||c ||  ||e ||  ||                ||  ||M ||  ||a ||  ||n ||
||__||  ||__||  ||__||  ||________________||  ||__||  ||__||  ||__||
|/__\|  |/__\|  |/__\|  |/________________\|  |/__\|  |/__\|  |/__\|

*/

#include <iostream>
#include <chrono>
#include <vector>
#include <assert.h>

#define maxn 200005
#define maxlog 20
#define INF 1000000010
#define LINF 1000000000000000005
#define endl '\n'
#define pb(x) push_back(x)
#define X first
#define Y second
#define control cout<<"passed"<<endl;

#pragma GCC optimize("O3" , "Ofast" , "unroll-loops" , "fast-math")
#pragma GCC target("avx2")

using namespace std;


typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;
typedef pair <ll , ll> pll;
typedef pair <int , ll> pil;
typedef pair <ll , int> pli;
typedef long double pd;


std::chrono::high_resolution_clock::time_point startT, currT;
constexpr double TIME_MULT = 1;

double timePassed()
{
    using namespace std::chrono;
    currT = high_resolution_clock::now();
    double time = duration_cast<duration<double>>(currT - startT).count();
    return time * TIME_MULT;
}



template <typename T>
vector <T> find_rec(vector <T> v)
{
    int n = v.size();
    vector <T> curr = {-1};
    vector <T> old = {1};
    T diff = 0 , prev = v[0];
    T num;

    for(int i = 0; i < n; i++)
    {
        assert(curr[0] == -1);

        diff++;
        num = 0;
        for(int j = 0; j < (int)curr.size(); j++)
            num += (curr[j] * v[i - j]);
        if(num == 0)
            continue;

        vector <T> save = curr;
        T _ratio = num / prev;
        curr.resize(max(diff + (int)(old.size()) , (int)(curr.size())));

        for(int i = 0; i < (int)old.size(); i++)
            curr[i + diff] -= (_ratio * old[i]);

        if(save.size() < old.size() + diff)
        {
            prev = num;
            old = save;
            diff = 0;
        }
    }

    curr.erase(curr.begin());
    assert(n >= (2 * (int)(curr.size()) + 5));
    return curr;
}



void read()
{

}

void solve()
{

}



int main()
{

/**#ifdef ONLINE_JUDGE /// promeni
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif*/

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    startT = std::chrono::high_resolution_clock::now();


    read();
    solve();


    return 0;
}
