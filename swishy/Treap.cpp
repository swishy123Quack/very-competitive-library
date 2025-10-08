#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iomanip>
#include <queue>
#include <cassert>
#include <complex>
#include <cstring>
#include <memory>

using namespace std;

#ifndef template
#ifndef define
 
#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define pb push_back
#define nl cout << '\n';
#define x first
#define y second 
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
 
#endif
 
#ifndef print
void print(size_t x) {cout << x << ' ';}
void print(int x) {cout << x << ' ';}
void print(long long x) {cout << x << ' ';}
void print(float x) {cout << x << ' ';}
void print(long double x) {cout << x << ' ';}
void print(char x) {cout << x << ' ';}
void print(const char* x) {cout << x << ' ';}
void print(bool x) {cout << x << ' ';}
void print(string &x) {cout << x << ' ';}
 
template<typename T, typename V>
void print(pair<T, V> &p) {print(p.x); print(p.y);}
template<typename T>
void print(vector<T> v) {for (int i = 0; i < v.size(); i++) print(v[i]);}
template<typename T>
void print(vector<vector<T>> v) {
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v[i].size(); j++)
            print(v[i][j]);
        nl;
    }
}
template <typename T, typename... V>
void print(T t, V&&... v) {print(t); print(v...);}
 
#endif

#ifndef read
void read(int &x) {cin >> x;}
void read(long long &x) {cin >> x;}
void read(unsigned &x) {cin >> x;}
void read(unsigned long long &x) {cin >> x;}
void read(float &x) {cin >> x;}
void read(long double &x) {cin >> x;}
void read(char &x) {cin >> x;}
void read(string &x) {cin >> x;}
void read(bool &x) {cin >> x;}

template<typename T> 
void read(vector<T> &v) {
    for (int i = 0; i < v.size(); i++)
        read(v[i]);
}
template <typename T, typename... V>
void read(T &t, V&... v) {read(t); read(v...);}
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> bool maxi(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool mini(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
template<class... Args>
auto vec(size_t n, Args&&... args) {
    if constexpr(sizeof...(args) == 1)
        return vector(n, args...);
    else
        return vector(n, vec(args...));
}
#endif
 
const long long inf = 1e9;
const long long mod = 1e9+7;
const int def = 1e7+1;

//lib
struct node{
    int key, prior;
    node *l, *r;

    node() = default;
    node(int key) : key(key), prior(rand()), l(nullptr), r(nullptr){}
    node(int key, int prior) : key(key), prior(prior), l(nullptr), r(nullptr){}
};

typedef node* pnode;
struct Treap{
public:
    pnode root;
    Treap(){
        root = new node(-1, -1);
    }
    void insert(int key){
        _insert(root, new node(key));
    }
    void erase(int key){
        _erase(root, key);
    }
    void list(pnode t){
        if (!t) return;
        list(t->l);
        print(t->key);
        list(t->r);
    }
    void split(pnode t, int key, pnode &l, pnode &r){
        if (!t)
            l = r = nullptr;
        else if (key <= t->key)
            split(t->l, key, l, t->l), r = t;
        else
            split(t->r, key, t->r, r), l = t;
    }
    void merge(pnode &t, pnode l, pnode r){
        if (!l || !r)
            t = l? l : r; 
        else if (l->prior > r->prior)
            merge(r->l, l, r->l), t = r;
        else
            merge(l->r, l->r, r), t = l;
    }
private:
    void _insert(pnode &t, pnode val){
        if (!t)
            t = val;
        else if (val->prior > t->prior){
            if (val->key <= t->key)
                _insert(t->l, val);
            else
                _insert(t->r, val);
        }
        else
            split(t, val->key, val->l, val->r), t = val;
    }
    void _erase(pnode &t, int key){
        if (t->key == key){
            pnode it = t;
            merge(t, t->l, t->r);
            delete it;
        }
        else if (key <= t->key)
            _erase(t->l, key);
        else
            _erase(t->r, key);
    }
};  
//lib

void solve(){
    int q;
    read(q);

    Treap t;
    while (q--){
        int k; read(k);
        if (k == 1){
            int key; read(key);
            t.insert(key);
        }
        else
        {
            int key; read(key);
            t.erase(key);
        }
        t.list(t.root);
        nl;
    }
}   

/*
8
1 3
1 1
1 2
2 2
2 1
1 4
2 3 
2 4
*/

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    int t;
    t = 1;

    while (t--){
        solve();
        nl;
    }
}
