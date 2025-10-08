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
#include <bitset>
#include <sstream>
#include <cmath>
#include <numeric>
#include <numbers>
#include <fstream>
 
using namespace std;
 
#ifndef template
#ifndef define
 
#pragma GCC target("popcnt")
 
#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define pi pair<int, int>
#define nl cout << '\n';
#define x first
#define y second 
#define cbit(x) __builtin_popcountll(x)
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
#define siz(x) (int)x.size()
#define all(x) (x).begin(), (x).end() 
 
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
 
using namespace std;
const ll inf = 1e17;
const ll def = 1e5+1;
const ll mod = 1e9+7;

struct LichaoTree{
    struct Line{
        ll a, b;
        Line() : a(0), b(-inf) {}
        Line(ll a, ll b): a(a), b(b) {}
        ll get(ll x){   
            return a * x + b;
        }
    };
public:
    vector<Line> st;
    int n;
    LichaoTree(int n) : n(n){
        st.resize(4 * n);
    }
    void add_line(Line line, int indx = 1, int l = 0, int r = -1){
        if (r == -1) r = n;
        int m = (l + r) / 2;
        bool left = line.get(l) > st[indx].get(l);
        bool mid = line.get(m) > st[indx].get(m);

        if (mid)
            swap(line, st[indx]);
        if (r - l == 1) return;
        else if (left != mid)
            add_line(line, 2 * indx, l, m);
        else
            add_line(line, 2 * indx + 1, m, r);
    }   
    ll query(ll x, int indx = 1, int l = 0, int r = -1){
        if (r == -1) r = n;
        if (r - l == 1) return st[indx].get(x);
        int mid = (l + r) / 2;
        if (x < mid)
            return max(st[indx].get(x), query(x, 2 * indx, l, mid));
        else
            return max(st[indx].get(x), query(x, 2 * indx + 1, mid, r));
    }
};

LichaoTree tree(def);
void solve(){
    int n;
    read(n);

    while (n--){
        int t; read(t);
        if (t == 1){
            ll a, b; read(a, b);
            tree.add_line(LichaoTree::Line(a, b));
        } 
        else{
            ll x; read(x);
            ll res = tree.query(x);
            print(res); nl;
        }
    }
}        

/*
1 2 2 3 4 5
*/

int32_t main(){
    ios_base::sync_with_stdio(0);       
    cin.tie(0); cout.tie(0);    
 
    if (ifstream("input.txt").good()){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
 
    int t = 1;
    // read(t);

    while (t--){
        solve();
        nl;
    }
    return 0;
}