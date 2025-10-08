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
const ll inf = 5000;
const ll def = 3001 + 100;
const ll mod = 998244353;

struct Graph{
    vector<vector<int>> edg;
    int n;

    Graph(int n) : n(n){
        edg = vector<vector<int>>(n, vector<int>());
    }
    void add(int u, int v){
        edg[u].push_back(v);
    }
    void bi_add(int u, int v){
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
};

struct BiconnectedComponent{
	Graph &G;
    vector<vector<int>> comps;
    vector<int> stk, num, low, is_cutpoint;

    BiconnectedComponent(Graph &G) : G(G){
        stk = num = low = is_cutpoint = vector<int>(G.n, 0);
        int timer = 0;
        dfs(0, -1, timer);
    }

	void dfs(int node, int parent, int &timer){
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : G.edg[node]) {
			if (son == parent) { continue; }
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};
};

struct Tree{
    vector<vector<int>> edg;
    vector<int> par, depth;
    int n, root;
    
    Tree(){}
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

    LCA(){}
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

LCA info;
void solve(){
    int n, m, q;
    read(n, m, q);

    Graph G(n);
    for (int i = 0; i < m; i++){
        int u, v;
        read(u, v);

        u--; v--;
        G.bi_add(u, v);
    }
    BiconnectedComponent bi(G);
    Tree block_cut(2 * n, 0);

    int crr = 0;
    auto indx = vec(n, 0);

    for (int i = 0; i < n; i++){
        if (bi.is_cutpoint[i])
            indx[i] = crr++;
    }
    for (auto cmp : bi.comps){
        for (int u : cmp){
            if (!bi.is_cutpoint[u])
                indx[u] = crr;
            else{
                block_cut.add(crr, indx[u]);
                block_cut.add(indx[u], crr);
            }
        }
        crr++;
    }
    block_cut.remove_dup();
    block_cut.n = crr;
    info = LCA(block_cut);

    while (q--){
        int a, b, c;
        read(a, b, c);

        a--; b--; c--;
        if (c == a || c == b){
            print("NO"); nl;
            continue;
        }
        if (!bi.is_cutpoint[c]){
            print("YES"); nl;
            continue;
        }
        a = indx[a]; b = indx[b]; c = indx[c];
        if (a == b || b == c){
            print("YES"); nl;
            continue;
        }
        int lca = info.get(a, b);
        if (info.get(a, c) == c && info.get(c, lca) == lca){
            print("NO"); nl;
            continue;
        }
        if (info.get(b, c) == c && info.get(c, lca) == lca){
            print("NO"); nl;
            continue;
        }
        print("YES"); nl;   
    }
}  
 
/* 
1 2 3 4 5
 
2 3 3 
*/
 
int32_t main(){
    ios_base::sync_with_stdio(0);       
    cin.tie(0); cout.tie(0);    
 
    if (ifstream("input.txt").good()){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
 
    int t = 1;
    while (t--){
        solve();
        nl;
    }
    return 0;
}