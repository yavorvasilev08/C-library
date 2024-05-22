/**
 ____    ____    ____    __________________    ____    ____    ____
||I ||  ||c ||  ||e ||  ||                ||  ||M ||  ||a ||  ||n ||
||__||  ||__||  ||__||  ||________________||  ||__||  ||__||  ||__||
|/__\|  |/__\|  |/__\|  |/________________\|  |/__\|  |/__\|  |/__\|

*/

#include <iostream>
#include <chrono>
#include <random>

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





mt19937_64 my_rand(time(NULL));

struct node
{
    int sz, x;
    int y;
    bool rev;

    node *par, *pp;
    node *l, *r;

    node()
    {
        sz = 0;
        y = 0;
        rev = 0;
        x = 0;

        par = nullptr;
        pp = nullptr;
        l = nullptr;
        r = nullptr;
    }

    node(int value)
    {
        sz = 1;
        rev = 0;
        y = my_rand();
        x = value;

        par = nullptr;
        pp = nullptr;
        l = nullptr;
        r = nullptr;
    }

};


int get_sz(node *root)
{
    if(root != nullptr)
        return root -> sz;
    else
        return 0;
}

void push(node* &root)
{
    if(root == nullptr)
        return;

    if(root -> rev == 1)
    {
        swap(root -> l, root -> r);

        if(root -> l != nullptr)
            root -> l -> rev ^= 1;

        if(root -> r != nullptr)
            root -> r -> rev ^= 1;

        root -> rev = 0;
    }
}

void pull(node* &root)
{
    if(root == nullptr)
        return;

    push(root -> l);
    push(root -> r);

    root -> par = nullptr;
    root -> sz = 1 + get_sz(root -> l) + get_sz(root -> r);

    if(root -> l != nullptr)
        root -> l -> par = root;

    if(root -> r != nullptr)
        root -> r -> par = root;

    if(root -> l != nullptr && root -> l -> pp != nullptr)
    {
        root -> pp = root -> l -> pp;
        root -> l -> pp = nullptr;
    }

    if(root -> r != nullptr && root -> r -> pp != nullptr)
    {
        root -> pp = root -> r -> pp;
        root -> r -> pp = nullptr;
    }
}







node *find_root(node *t)
{
    if(t == nullptr)
        return nullptr;

    while(t -> par != nullptr)
        t = t -> par;

    return t;
}


void _merge(node* &res, node *l, node *r)
{
    push(l);
    push(r);

    if(l == nullptr)
    {
        res = r;
        return;
    }

    if(r == nullptr)
    {
        res = l;
        return;
    }

    if(l -> y > r -> y)
    {
        _merge(l -> r, l -> r, r);
        res = l;
    }
    else
    {
        _merge(r -> l, l, r -> l);
        res = r;
    }

    pull(res);
}


void _split(node* res, node* &l, node* &r, int from, int delta)
{
    push(res);

    if(res == nullptr)
    {
        l = nullptr;
        r = nullptr;

        return;
    }

    int _next = delta + get_sz(res -> l);

    if(_next <= from)
    {
        _split(res -> r, res -> r, r, from, _next + 1);
        l = res;
    }
    else
    {
        _split(res -> l, l, res -> l, from, delta);
        r = res;
    }

    pull(res);
}


node *rem_r(node* root)
{
    node* pom = root;

    int p;
    if(pom -> rev == 1)
        p = get_sz(pom) - get_sz(pom -> l) - 1;
    else
        p = get_sz(pom -> l);

    while(pom -> par != nullptr)
    {
        if(pom -> par -> r == pom)
            p += get_sz(pom -> par -> l) + 1;

        if(pom -> par -> rev == 1)
            p = get_sz(pom -> par) - p - 1;

        pom = pom -> par;
    }

    node *_l, *_r;
    node *_pp = pom -> pp;

    pom -> pp = nullptr;
    _split(pom, _l, _r, p, 0);

    _l -> pp = _pp;
    if(_r != nullptr)
        _r -> pp = root;

    return _l;
}



node * rem_l(node* root)
{
    node *pom = root;

    int p;

    if(root -> rev == 1)
        p = pom -> sz - get_sz(pom -> l) - 1;
    else
        p = get_sz(pom -> l);

    while(pom -> par != nullptr)
    {
        if(pom -> par -> r == pom)
            p += get_sz(pom -> par -> l) + 1;

        if(pom -> par -> rev == 1)
            p = get_sz(pom -> par) - p - 1;

        pom = pom -> par;
    }

    node *_l, *_r;
    node *_pp = pom -> pp;

    pom -> pp = nullptr;
    _split(pom, _l, _r, p - 1, 0);

    if(_l != nullptr)
        _l -> pp = _pp;

    return _r;
}


node *_merget(node* l, node* r)
{
    l = find_root(l);
    r = find_root(r);

    r -> pp = nullptr;
    _merge(l, l, r);
    return l;
}


struct lct
{
    node* nodes[maxn];

    void initialize(int _n)
    {
        for(int i = 0; i <= _n; i++)
            nodes[i] = new node(i);
    }

    node* access(node* root)
    {
        root = rem_r(root);

        node *pom;
        while(root -> pp != nullptr)
        {
            pom = root -> pp;
            pom = rem_r(pom);

            root = _merget(pom, root);
        }

        return root;
    }

    void new_root(node *root)
    {
        root = access(root);
        root -> rev ^= 1;

        push(root);
    }

    void link(node *a, node *b)
    {
        new_root(a);
        access(b);

        _merget(b, a);
    }

    void cut(node *root)
    {
        access(root);
        rem_l(root);
    }

    int get_depth(node *root)
    {
        root = access(root);
        return get_sz(root);
    }

    node *get_root(node *root)
    {
        root = access(root);
        push(root);

        while(root -> l != nullptr)
        {
            root = root -> l;
            push(root);
        }

        access(root);
        return root;
    }

    node *get_lca(node *a, node *b)
    {
        if(a == b)
            return a;

        if(get_depth(a) > get_depth(b))
            swap(a, b);

        access(b);
        access(a);

        return find_root(b) -> pp;
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
