#include <bits/stdc++.h>
using namespace std;
 
#ifndef template
#ifndef define
 
#define ll long long
#define pb push_back
#define nl cout << '\n';
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
template<typename ...Args>
void read(Args&... args) {
    (cin >> ... >> args);
}
#endif
 
const long long inf = 1e15;
const long long mod = 2023;
const int def = 1e3+1;
 
template<typename T>
struct WeightedGraph{
    vector<vector<pair<int, T>>> edg;
    int n;
 
    WeightedGraph(int n) : n(n){
        edg = vector<vector<pair<int, T>>>(n, vector<pair<int, T>>());
    }
    void add(int u, int v, T w){
        edg[u].push_back({v, w});
    }
    void bi_add(int u, int v, T w){
        edg[u].push_back({v, w});
        edg[v].push_back({u, w});
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

//lib
template<typename T>
struct Dijkstra{
    WeightedGraph<T> &G;
    vector<long long> dp; 
 
    struct Node{
        Node(long long dis, long long u) : dis(dis), u(u){} 
        long long dis, u;
    };
 
    struct Comapre{
        bool operator()(Node a, Node b){
            return a.dis > b.dis;
        }
    };
 
    priority_queue<Node, vector<Node>, Comapre> pq;
    void push(long long dis, long long &val, Node node){
        if (dis < val){
            val = dis;
            pq.push(node);
        }
    }
 
    Dijkstra(WeightedGraph<T> &G, Node start) : G(G){
        dp = vec(G.n, inf);
        dp[start.u] = 0;
 
        pq.push(start);
        while (pq.size()){
            auto [dis, u] = pq.top(); pq.pop();
            if (dis > dp[u])
                continue;
            for (auto [v, w] : G.edg[u])
                push(dis + w, dp[v], {dis + w, v});
        }
    }
};
//lib
 
void solve(){
    int n, m;
    cin >> n >> m;
 
    WeightedGraph<long long> G(n);
    for (int i = 0; i < m; i++){
        long long u, v, w;
        read(u, v, w);
 
        G.add(--u, --v, w);
    }
 
    Dijkstra<long long> dijkstra(G, {0, 0});
    for (int i = 0; i < n; i++)
        print(dijkstra.dp[i]);
}
 
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