#include <bits/stdc++.h>
using namespace std;
 
#ifndef template
#ifndef define
 
#define ll long long
#define nl cout << endl;
#define x first
#define y second 
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
 
#endif
 
#ifndef print
void print(int x) {cout << x << ' ';}
void print(long long x) {cout << x << ' ';}
void print(unsigned x) {cout << x << ' ';}
void print(unsigned long long x) {cout << x << ' ';}
void print(float x) {cout << x << ' ';}
void print(long double x) {cout << x << ' ';}
void print(char x) {cout << x << ' ';}
void print(const string &x) {cout << x << ' ';}
void print(bool x) {cout << x << ' ';}
 
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

//lib
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
//lib
 
template<typename T, class Combine = function<T(const T &, const T &)>>
struct SegmentTreeFast{
    vector<T> a;
    Combine cmb;
    T defv;
    int n;

    SegmentTreeFast(int n, T defv, const Comine &cmb) : n(n), defv(defv), cmb(cmb){
        a = vector<T>(2 * n, defv);
    }

    void update(int i, T v){
        for (a[i += n] = v; i > 1; i >>= 1)
            a[i >> 1] = cmb(a[i], a[i ^ 1]);
    }

    T get(int l, int r){
        r++;
        T res = defv;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) res = cmb(res, a[l++]);
            if (r&1) res = cmb(res, a[--r]);
        }

        return res;
    }
};
 
void solve(){
    
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