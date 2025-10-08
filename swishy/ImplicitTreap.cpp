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
    ll prior, cnt, sum, add, val;
    node *l, *r;

    node() = default;
    node(ll val) : prior(rand()), cnt(1), sum(val), add(0), val(val), l(nullptr), r(nullptr){}
    node(int prior, ll val) : prior(prior), cnt(1), sum(val), val(val), add(0), l(nullptr), r(nullptr){}
};

typedef node* pnode;
struct ImplicitTreap{
public:
    pnode root;
    ImplicitTreap(){
        root = new node(-1, 0);
    }
    void insert(int i, ll val){
        pnode t1, t2;
        split(root, i + 1, 0, t1, t2);
        merge(t1, t1, new node(val));
        merge(root, t1, t2);
    }
    void erase(int i){
        _erase(root, i + 1, 0);
    }
    ll query(int l, int r){
        pnode t1, t2, t3;
        split(root, r + 2, 0, t2, t3);
        split(t2, l + 1, 0, t1, t2);

        ll res = t2->sum;
        merge(root, t1, t2);
        merge(root, root, t3);

        return res;
    }
    void update(int l, int r, ll val){
        pnode t1, t2, t3;
        split(root, r + 2, 0, t2, t3);
        split(t2, l + 1, 0, t1, t2);

        t2->add += val;
        merge(root, t1, t2);
        merge(root, root, t3);
    }
    void split(pnode t, int key, int add, pnode &l, pnode &r){
        if (!t){
            l = r = nullptr;
            return;
        }
        push(t);
        int impl_key = add + _cnt(t->l);
        if (key <= impl_key)
            split(t->l, key, add, l, t->l), r = t;
        else
            split(t->r, key, add + _cnt(t->l) + 1, t->r, r), l = t;
        upd(t);
    }
    
    void merge(pnode &t, pnode l, pnode r){
        push(l); push(r);
        if (!l || !r)
            t = l? l : r; 
        else if (l->prior > r->prior)
            merge(r->l, l, r->l), t = r;
        else
            merge(l->r, l->r, r), t = l;
        upd(t);
    }
private:
    void _erase(pnode &t, int key, int add){
        push(t);
        int impl_key = add + _cnt(t->l);
        if (impl_key == key){
            pnode it = t;
            merge(t, t->l, t->r);
            delete it;
        }
        else if (key < impl_key)
            _erase(t->l, key, add);
        else
            _erase(t->r, key, add + _cnt(t->l) + 1);
        upd(t);
    }
    void push(pnode t){
        if (!t) return;
        t->sum += t->add * (ll)_cnt(t);
        t->val += t->add;
        if (t->l) t->l->add += t->add;
        if (t->r) t->r->add += t->add;

        t->add = 0;
    }
    int _cnt(pnode t){
        if (!t) return 0;
        return t->cnt;
    }
    ll _sum(pnode t){
        if (!t) return 0;
        push(t);
        return t->sum;
    }
    void upd(pnode t){
        if (!t) return;
        t->sum = t->val + _sum(t->l) + _sum(t->r);
        t->cnt = _cnt(t->l) + _cnt(t->r) + 1;
    }
}; 
//lib

void solve(){
    ImplicitTreap t;
    int sz = 0;
    while (1){
        int k; read(k);
        if (k == 0) return;
        if (k == 1){
            int i, val;
            read(i, val); sz++;
            t.insert(i, val);
        }
        else if (k == 2){
            int i; read(i); sz--;
            t.erase(i);
        }
        else if (k == 3){
            int l, r, val;
            read(l, r, val);
            t.update(l, r, val);
        }
        else if (k == 4){
            int l, r;
            read(l, r);
            print(t.query(l, r));
            nl;
        }
        for (int i = 0; i < sz; i++)
            print(t.query(i, i));
        cout << endl;
    }
}   

/*
1 0 2
1 0 3
1 1 4
1 1 3
2 0
2 2
2 1
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