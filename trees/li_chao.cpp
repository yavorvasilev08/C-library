/**
 ____    ____    ____    __________________    ____    ____    ____
||I ||  ||c ||  ||e ||  ||                ||  ||M ||  ||a ||  ||n ||
||__||  ||__||  ||__||  ||________________||  ||__||  ||__||  ||__||
|/__\|  |/__\|  |/__\|  |/________________\|  |/__\|  |/__\|  |/__\|

*/

#include <iostream>
#include <chrono>
#include <vector>

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
typedef pair <ll, ll> pll;
typedef pair <int, ll> pil;
typedef pair <ll, int> pli;
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

struct li_chao
{
    struct line
    {
        T k, m;
        line() {};
        line(T _k, T _m)
        {
            k = _k;
            m = _m;
        }
        T calc(T coef)
        {
            return k * coef + m;
        }
    };

    int n;
    vector <line> tree;
    vector <bool> used;
    vector <T> a;

    void init(int sz, vector <T>& v)
    {
        n = sz;
        a = v;
        tree.resize(n * 4);
        used.resize(n * 4);
    }

    void update(int node, int l, int r, line _new)
    {
        if(l > r)
            return;

        if(used[node] == false)
        {
            tree[node] = _new;
            used[node] = true;

            return;
        }

        if(tree[node].k == _new.k)
        {
            if(_new.k > tree[node].k)
                swap(_new, tree[node]);
            return;
        }

        if(l == r)
        {
            if(tree[node].calc(a[l]) < _new.calc(a[l]))
                swap(tree[node], _new);
            return;
        }

        ll mid = (l + r) / 2;

        if(tree[node].calc(a[l]) < _new.calc(a[l]))
            swap(_new, tree[node]);

        if(tree[node].calc(a[mid]) > _new.calc(a[mid]))
            update(node * 2 + 2, mid + 1, r, _new);
        else
        {
            swap(tree[node], _new);
            update(node * 2 + 1, l, mid, _new);
        }
    }


    T query(int node, int l, int r, T coef)
    {
        if(l > r)
            return 0;

        if(used[node] == false)
            return 0;

        if(l == r)
            return tree[node].calc(coef);

        ll mid = (l + r) / 2;
        T res = tree[node].calc(coef);

        if(coef <= a[mid])
            res = max(res, query(node * 2 + 1, l, mid, coef));
        else
            res = max(res, query(node * 2 + 2, mid + 1, r, coef));

        return res;
    }
};



void read()
{

}

void solve()
{

}


int main()
{

    /**#ifdef ONLINE_JUDGE /// promeni
        freopen("taxi.in", "r", stdin);
        freopen("taxi.out", "w", stdout);
    #endif*/

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    startT = std::chrono::high_resolution_clock::now();


    read();
    solve();

    return 0;
}
