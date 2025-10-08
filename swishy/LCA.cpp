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
 
const long long inf = 1e10;
const long long mod = 2023;
const int def = 1e6+1;

struct Tree{
    vector<vector<int>> edg;
    vector<int> par, depth;
    int n, root;
 
    Tree(int n, int root) : n(n), root(root){
        edg = vector<vector<int>>(n, vector<int>());
    }
    void add(int u, int v){
        edg[u].push_back(v);
        edg[v].push_back(u);
    }
    void clear(){
        for (int u = 0; u < n; u++)
            edg[u].clear();
    }
    void remove_dup(){
        for (int u = 0; u < n; u++){
            sort(edg[u].begin(), edg[u].end());
            edg[u].erase(unique(edg[u].begin(), edg[u].end()), edg[u].end());
        }
    }
    void get_info(){
        par = depth = vector<int>(n, 0);
        par[root] = -1;
        dfs(root, -1);
    }
    void dfs(int u, int pre){
        for (int v : edg[u]){
            if (v == pre) continue;
            par[v] = u; depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
};

struct LCA{
    vector<vector<int>> f;
    Tree T;
    int n, k;

    LCA(Tree &_T) : T(_T){
        n = T.n; k = log2(n) + 2;
        for (int i = 0; i < n; i++)
            f.push_back(vector<int>(k, -1));
        T.get_info();
        
        for (int i = 0; i < n; i++)
            f[i][0] = T.par[i];
        for (int j = 1; j < k; j++) for (int i = 0; i < n; i++){
            int p = f[i][j - 1];
            if (p != -1)
                f[i][j] = f[p][j - 1];
        }
    }

    int get(int u, int v){
        if (T.depth[u] < T.depth[v])
            swap(u, v);
        for (int i = k - 1; i >= 0; i--){
            if (f[u][i] != -1 && T.depth[f[u][i]] >= T.depth[v])
                u = f[u][i];
        }
        if (u == v) return u;
        for (int i = k - 1; i >= 0; i--){
            if (f[u][i] != -1 && f[u][i] != f[v][i])
                u = f[u][i], v = f[v][i];
        }
        return T.par[u];
    }
};

void solve(){
    int n, q;
    read(n, q);

    Tree T(n, 0);
    for (int i = 0; i < n - 1; i++){
        int u, v;
        read(u, v);
        T.add(--u, --v);
    }

    LCA lca(T);
    while (q--){
        int u, v;
        read(u, v);

        cout << lca.get(--u, --v) << endl; 
    }
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    ll t;
    t = 1;
 
    while (t--){
        solve();
    }
 
    return 0;   
}