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
const ld eps = 1e-6;

struct edge{
    int v;
    ll cost, capacity;
    edge* rv; 
    edge(int v, ll cost, ll capacity) : v(v), cost(cost), capacity(capacity){}
};
 
struct MCMF{
    vector<vector<edge*>> edg;
    vector<pair<int, edge*>> par;
    vector<ll> dis;
 
    MCMF(int n){
        edg = vector<vector<edge*>>(n);
    }
    void add_edge(int u, int v, ll capacity, ll cost){
        edge* e = new edge(v, cost, capacity);
        edge* re = new edge(u, -cost, 0);
 
        e->rv = re;
        re->rv = e;
 
        edg[u].push_back(e);
        edg[v].push_back(re);
    }
    void spfa(int start){
        int n = edg.size();
        auto inq = vec(n, 0);   
        dis = vec(n, inf);
        par = vector<pair<int, edge*>>(n, {-1, nullptr});
 
        queue<int> q;
        q.push(start);
        dis[start] = 0;
        
        while (q.size()){
            int u = q.front(); q.pop();
            inq[u] = 0;
 
            for (auto e : edg[u]){
                if (e->capacity > 0 && dis[e->v] > dis[u] + e->cost){
                    dis[e->v] = dis[u] + e->cost;
                    par[e->v] = {u, e};
 
                    if (!inq[e->v]){
                        inq[e->v] = 1;
                        q.push(e->v);
                    }
                }
            }
        }
    }   
    pl get(int start, int end, ll max_flow = inf){
        ll flow = 0, cost = 0;
        while (flow < max_flow){
            spfa(start);
            if (dis[end] == inf) break;
 
            ll f = max_flow - flow;
            int u = end;
 
            while (u != start){
                f = min(f, par[u].y->capacity);
                u = par[u].x;
            }
 
            flow += f;
            cost += f * dis[end];
 
            u = end;
            while (u != start){
                par[u].y->capacity -= f;
                par[u].y->rv->capacity += f;
                u = par[u].x;
            }
        }   
        if (flow == max_flow || max_flow == inf)
            return {flow, cost};
        else
            return {-1, -1}; 
    }
};


void solve(){
    int n;
    read(n);

    auto a = vec(n, 0);
    auto b = a;

    read(a, b);

}           

/*
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