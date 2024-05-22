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

struct segment_tree
{
    struct node
    {
        int l, r;
        T data;
        node()
        {
            l = r = -1;
            data = 0;
        }
        node(T _data, int _l = -1, int _r = -1)
        {
            l = _l;
            r = _r;
            data = _data;
        }
    };

    vector <node> a;
    int l, r;

    segment_tree()
    {
        l = r = -1;
        a.emplace_back();
    }

    void make_l(int node)
    {
        a[node].l = a.size();
        a.emplace_back();
    }

    void make_r(int node)
    {
        a[node].r = a.size();
        a.emplace_back();
    }

    void calc(int node)
    {
        T datal, datar;

        if(a[node].l == -1)
            datal = 0;
        else
            datal = a[a[node].l].data;

        if(a[node].r == -1)
            datar = 0;
        else
            datar = a[a[node].r].data;

        a[node].data = datal + datar;
    }

    void update(int node, int l, int r, int qp, T qval)
    {
        if(l == r)
        {
            a[node].data = qval;
            return;
        }

        int mid = (l + r) / 2;

        if(qp <= mid)
        {
            if(a[node].l == -1)
                make_l(node);
            update(a[node].l, l, mid, qp, qval);
        }
        else
        {
            if(a[node].r == -1)
                make_r(node);
            update(a[node].r, mid + 1, r, qp, qval);
        }
        calc(node);
    }

    T query(int node, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql)
            return 0;
        if(l >= ql && r <= qr)
            return a[node].data;
        if(a[node].data == 0)
            return 0;

        int mid = (l + r) / 2;
        T ans = 0;

        if(a[node].l == -1)
            make_l(node);
        ans += query(a[node].l, l, mid, ql, qr);

        if(a[node].r == -1)
            make_r(node);
        ans += query(a[node].r, mid + 1, r, ql, qr);

        return ans;
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
