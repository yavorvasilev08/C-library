/**
 ____    ____    ____    __________________    ____    ____    ____
||I ||  ||c ||  ||e ||  ||                ||  ||M ||  ||a ||  ||n ||
||__||  ||__||  ||__||  ||________________||  ||__||  ||__||  ||__||
|/__\|  |/__\|  |/__\|  |/________________\|  |/__\|  |/__\|  |/__\|

*/

#include <iostream>
#include <chrono>
#include <vector>
#include <queue>

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

struct max_flow
{
    struct edge
    {
        int from, to;
        T c, flow;
        edge() {};
        edge(int _from, int _to, T _c, T _flow = 0)
        {
            from = _from;
            to = _to;
            c = _c;
            flow = _flow;
        }
    };

    int n;
    vector <int> used;
    vector <int> to;
    vector <vector <int>> v;
    vector <edge> e;

    void init(int sz)
    {
        n = sz;
        used.resize(n + 1);
        to.resize(n + 1);
        v.resize(n + 1);
        e.clear();
    }

    int bre;

    void add_edge(int from, int to, T capacity)
    {
        v[from].push_back(bre);
        v[to].push_back(bre + 1);

        e.push_back({from, to, capacity});
        e.push_back({to, from, 0});

        bre += 2;
    }

    queue <int> q;

    bool bfs(int start, int endd)
    {
        for(int i = 0; i <= n; i++)
            used[i] = -1;
        used[start] = 0;
        q.push(start);

        int node;
        while(q.size() > 0)
        {
            node = q.front();
            q.pop();

            for(int idx : v[node])
                if(used[e[idx].to] == -1 && e[idx].c > e[idx].flow)
                {
                    q.push(e[idx].to);
                    used[e[idx].to] = used[node] + 1;
                }
        }

        if(used[endd] == -1)
            return false;
        else
            return true;
    }

    T fix_flow(int node, int endd, T fl)
    {
        if(node == endd || fl == 0)
            return fl;

        int idx, nb;
        for(int i = to[node]; i < v[node].size(); i++, to[node]++)
        {
            idx = v[node][i];
            nb = e[idx].to;

            if(used[nb] != used[node] + 1)
                continue;

            if(e[idx].c <= e[idx].flow)
                continue;

            T edg = fix_flow(nb, endd, min(fl, e[idx].c - e[idx].flow));
            if(edg == 0LL)
                continue;

            e[idx].flow += edg;
            e[idx ^ 1].flow -= edg;

            return edg;
        }
        return 0LL;
    }

    T find_flow(int start, int endd)
    {
        T ans = 0;

        while(bfs(start, endd) == true)
        {
            for(int i = 0; i <= n; i++)
                to[i] = 0;
            int curr;
            while((curr = fix_flow(start, endd, LINF)))
                ans += curr;
        }
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
